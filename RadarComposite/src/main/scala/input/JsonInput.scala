package input

import java.io.IOException

import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.module.scala.DefaultScalaModule
import input.ProductTypeEnum._

import scala.collection.JavaConversions._
import scala.collection._

/**
 * Created by sugar on 6/19/2014.
 */
class JsonInput extends DataInput {

  //Input data is a JSON string. It is NEITHER pointing an hdfs url NOR an archive itself.
  override def Decode(input_data: String): (Long, mutable.HashMap[Long, mutable.HashMap[String, BeamRecord]]) = {

    // Bind json string to POJOs
    val mapper = new ObjectMapper()
    mapper.registerModule(DefaultScalaModule)
    val inputJson = mapper.readValue[JsonInputFormat](input_data, classOf[JsonInputFormat])

    // If file content is different from result, return an empty result

    // YES, input data are the correct type!
    val vcpModeString: String = inputJson.global_attributes.vcp_value
    val radarName: String = inputJson.global_attributes.radarName_value

    // TODO: Try to avoid hard-coded dimensions for decoding RadialSet. We hard-coded variables' dimensions are (Azimuth,Gate)
    val elevation: Double = inputJson.global_attributes.Elevation
    val range: Double = inputJson.global_attributes.RangeToFirstGate
    val subType: Double = if (inputJson.global_attributes.SubType_value == null) elevation else inputJson.global_attributes.SubType_value.toDouble
    val dataType: String = inputJson.global_attributes.DataType
    val startTime: Long = inputJson.global_attributes.Time * 1000l
    val legacy: Boolean = inputJson.data.GateWidth(0) == 1000
    //Read dimension of (Azimuth, Gate), needed by decoding
    var sizeGate = 0
    var sizeAzimuth = 0
    for (p <- inputJson.dimensions.keys) {
      p match {
        case "Azimuth" => sizeAzimuth = inputJson.dimensions(p).dimension_length
        case "Gate" => sizeGate = inputJson.dimensions(p).dimension_length
        case _ =>
      }
    }
    val azimuth: Array[Double] = UtilClass.FloatArrayToDoubleArray(inputJson.data.Azimuth)
    val azimuthSp: Array[Double] = UtilClass.FloatArrayToDoubleArray(inputJson.data.AzimuthalSpacing)
    val VCP: VCPMode = new VCPMode(vcpModeString)
    val radar: Radar = new Radar(radarName)

    // Extract multiple radar variables into a dictionary of a set of BeamRecord
    val productNames = inputJson.global_attributes.TypeName.split(';')
    for (productName <- productNames) {

      val unitTime: Double =
        if (productName.toLowerCase.contains("reflect")) VCP.getAZRate(subType, Waveform.CS)
        else VCP.getAZRate(subType, Waveform.CD)

      // Validate inputs are correct
      // FIXME: More definition of product string?
      val dataVariable = productName match {
        case "Reflectivity" => inputJson.data.Reflectivity
        case "ReflectivityQC" => inputJson.data.ReflectivityQC
        case "AliasedVelocity" => inputJson.data.AliasedVelocity
        case "Velocity" => inputJson.data.Velocity
        case "SpectrumWidth" => inputJson.data.SpectrumWidth
        case _ => inputJson.data.UnknownVariable
      }

      if (dataType == "SparseRadialSet") {
        //Decode SparseRadialSet encoded by run-length algorithm
        val product: SparseRadialSetClass = new SparseRadialSetClass
        product.setPixelX(inputJson.data.pixel_x)
        product.setPixelY(inputJson.data.pixel_y)
        product.setPixelCount(inputJson.data.pixel_count)
        product.setSize(sizeAzimuth, sizeGate)
        product.setEncodedValues(dataVariable)
        if (product.decodeSet()) {
          for (i <- product.decodedValues.indices) {
            val p: Array[Double] = product.decodedValues(i)
            val currentTime: Long = startTime + ((azimuth(i) - azimuth(0)) * unitTime).asInstanceOf[Long]
            val beam: BeamRecord =
              if (legacy) new LegacyBeamRecord(currentTime, radar, VCP, elevation, azimuth(i), range)
              else new SuperResolutionBeamRecord(currentTime, radar, VCP, elevation, azimuth(i), range)
            beam.azimuthSpacing.add(azimuthSp(i))
            beam.binValues.addAll(p.toSeq)

            // Add current beam to BeamSet
            if (BeamSet.contains(currentTime)) {
              this.BeamSet(currentTime).put(productName, beam)
            } else {
              val _q = mutable.HashMap(productName -> beam)
              this.BeamSet.put(currentTime, _q)
            }
          }
        }
      } else {
        //Decode non-sparse values
        //Because we always copy variables into a 1D Array, so we need split them into beams.
        for (i <- 0 to sizeAzimuth - 1) {
          val currentTime: Long = startTime + ((azimuth(i) - azimuth(0)) * unitTime).asInstanceOf[Long]
          val beam: BeamRecord =
            if (legacy) new LegacyBeamRecord(currentTime, radar, VCP, elevation, azimuth(i), range)
            else new SuperResolutionBeamRecord(currentTime, radar, VCP, elevation, azimuth(i), range)
          beam.azimuthSpacing.add(azimuthSp(i))
          for (j <- 0 to sizeGate - 1) {
            // Convert 2D index to 1D index
            val index = i * sizeGate + j
            // For easier debugging
            val p = dataVariable(index)
            beam.binValues.add(p)
          }
          // Add current beam to BeamSet
          if (BeamSet.contains(currentTime)) {
            this.BeamSet(currentTime).put(productName, beam)
          } else {
            val _q = mutable.HashMap(productName -> beam)
            this.BeamSet.put(currentTime, _q)
          }
        }
      }
    }

    // Return
    (startTime, this.BeamSet)
  } // End function decode
}


