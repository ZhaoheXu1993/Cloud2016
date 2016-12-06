package spark

import input.{Radar, BeamRecord}
import config._

import scala.math
import scala.collection._
import scala.collection.mutable.ListBuffer

/**
 * Created by sugar on 4/25/15.
 */


object GateRDD {
  
  def mosaicRawReflectivity(gates: (Int, scala.Iterable[((Int, Int, Int, Int), GateElement)])) : (Int, Array[Array[Array[GateElement]]]) = {

    val rawMosaic = Array.ofDim[GateElement](1000, 1000, 1000)

    (gates._1, rawMosaic)
  }


  def gridGate(gate: (((Int, Double, Double, Double), GateElement))): ((Int, Int, Int, Int), GateElement) = {
    val i = ((gate._1._2 - SiteConf.SpatialExtend("X")._1) / SiteConf.SpatialResolution("X")).asInstanceOf[Int]
    val j = ((gate._1._3 - SiteConf.SpatialExtend("Y")._1) / SiteConf.SpatialResolution("Y")).asInstanceOf[Int]
    val k = ((gate._1._4 - SiteConf.SpatialExtend("Z")._1) / SiteConf.SpatialResolution("Z")).asInstanceOf[Int]
    val gx = (i + 0.5) * SiteConf.SpatialResolution("X") + SiteConf.SpatialExtend("X")._1
    val gy = (j + 0.5) * SiteConf.SpatialResolution("Y") + SiteConf.SpatialExtend("Y")._1
    val gz = (k + 0.5) * SiteConf.SpatialResolution("Z") + SiteConf.SpatialExtend("Z")._1
    val distanceGateToGridCenter = math.sqrt((gate._1._2 - gx) * (gate._1._2 - gx) + (gate._1._3 - gy) * (gate._1._3 - gy) + (gate._1._4 - gz) * (gate._1._4 - gz))
    gate._2.meta("DistanceToCenter") = distanceGateToGridCenter
    // NOTE: We don't really need to use "virtual beam", because we know the this grid is tagged with gate from what
    // radar. What we need is to see. We just need to know the angle distance from radar
    // TODO: I quite don't understand why PyART use domain center to calcuate "virtual beam" size. But we could port it to see how it works

    // Return
    ((gate._1._1, i, j, k), gate._2)
  }

  def propagateBeamToTrueGate(beam: (Int, BeamRecord)) : Seq[((Int, Double, Double, Double), GateElement)] = {
    val result = new ListBuffer[((Int, Double, Double, Double), GateElement)]()

    val record = beam._2
    val radar = record.radar
    val x0 = radar.getXY._1
    val y0 = radar.getXY._2
    val elevation = math.toRadians(record.elevation)
    val angle = math.toRadians(90 - record.Azimuth)
    for(i <- 1 to record.getBinCount - 1) {
      val slant: Double = record.rangeToFirstGate + i * record.gateWidth
      if(slant > 0) {
        // Basic (x,y,z)
        val h = Radar.getRelativeBeamHeight(slant, elevation)
        val z = h + radar.getRadarHeight
        // if we set in SiteConf
        val distance = if (SiteConf.AdjustGroundDistance) math.sqrt(slant * slant - h * h) else slant * math.cos(elevation)
        val x1 = distance * math.cos(angle)
        val x = x0 + x1
        val y1 = distance * math.sin(angle)
        val y = y0 + y1
        // Only collect value that inside domain
        if(SiteConf.SpatialExtend("X")._2 + SiteConf.SpatialMargin > x  &&
          SiteConf.SpatialExtend("X")._1 - SiteConf.SpatialMargin < x &&
          SiteConf.SpatialExtend("Y")._2 + SiteConf.SpatialMargin > y &&
          SiteConf.SpatialExtend("Y")._1 - SiteConf.SpatialMargin < y) {
          // Useful information may reduce calculation later
          val meta = new mutable.HashMap[String, Any]
          meta("Radar") = radar.radarName
          meta("Vector") = (x1, y1, h)
          meta("Pos") = (x, y, z)
          meta("GroundDistance") = distance
          meta("Slant") = slant
          meta("DistWeight") = math.exp(-0.00005 * slant)
          meta("Time") = record.beamTime
          // Put it in result
          result += (((beam._1, x, y, z), new GateElement(record.binValues(i), meta)))
        }
      }
    }

    result.toSeq
  }


}
