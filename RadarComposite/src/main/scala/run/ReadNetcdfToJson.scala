package run

import java.io._
import java.nio.file.{Files, Paths}
import java.util
import java.util.zip.{GZIPInputStream, GZIPOutputStream}

import org.apache.commons.io._
import org.codehaus.jettison.json.{JSONArray, JSONObject}
import ucar.ma2.DataType
import ucar.nc2.{Attribute, Dimension, NetcdfFile, Variable}

import scala.collection.JavaConversions._

object ReadNetcdfToJson {

  def main(args: Array[String]) {
    if (args.length == 2) {
      // Loop all files in path 1 and save them in path 2
      val inPath = new File(args(0))
      val outPath = new File(args(1))
      FileUtils.forceMkdir(outPath)
      var i = 1
      for(f <- FileUtils.iterateFiles(inPath, Array("netcdf", "gz"), true))
      {
        val _in = f.getAbsolutePath
        val out = _in.replace(args(0), args(1)).replace(".netcdf", ".json")
        convert(_in, out)
        if (i % 100 == 0)
          print(".")
        if (i % 1000 == 0)
          println()
        i += 1
      }

    }
    else {
      System.out.println("Usage: ReadNetcdf <input> <output>")
      System.exit(-1)
    }

  }

  def convert(inFileName: String, outFileName: String) {

    if (!new File(inFileName).exists()) {
      throw new FileNotFoundException("Input file " + inFileName + "not exist")
    }

    //Extract gzipped file.
    val gzipInput = inFileName.endsWith(".gz")

    // srcFile = extracted-temp-file if gzipped else original-file
    val srcFile =
      if (gzipInput) {
        var tempFolder: String = System.getenv("TEMP")
        if (null == tempFolder) {
          tempFolder = "/tmp"
        }

        val tempNetcdf: String = new File(tempFolder, new File(inFileName.substring(0, inFileName.length - 3)).getName).getPath
        assert(tempNetcdf.endsWith(".netcdf"))

        val buffer: Array[Byte] = new Array[Byte](1024)
        val gzInStream: GZIPInputStream = new GZIPInputStream(new FileInputStream(inFileName))
        val outStream: FileOutputStream = new FileOutputStream(tempNetcdf)
        var len: Int = gzInStream.read(buffer)
        while (len > 0) {
          outStream.write(buffer, 0, len)
          len = gzInStream.read(buffer)
        }
        gzInStream.close()
        outStream.close()

        tempNetcdf
      } else {
        inFileName
      }

    //Open and read all netcdf information
    val netcdfFile: NetcdfFile = NetcdfFile.open(srcFile)
    val netcdf: JSONObject = new JSONObject()
    val list: util.List[Dimension] = netcdfFile.getDimensions
    val dimensionArray: JSONObject = new JSONObject()

    for (d <- list) {
      val jsonObject: JSONObject =  new JSONObject()
      //jsonObject.put("dimension_name", d.getName)
      jsonObject.put("dimension_length", d.getLength)
      dimensionArray.put(d.getName, jsonObject)
    }
    netcdf.put("dimensions", dimensionArray)

    val variables: util.List[Variable] = netcdfFile.getVariables
    val varArray = new JSONObject()

    for (v <- variables) {
      val jsonObject: JSONObject = new JSONObject()
      //jsonObject.put("var_name", v.getName.replace("-", "_"))
      jsonObject.put("var_type", v.getDataType)
      // Get dimensions for each variable
      val varDim = new JSONArray()
      v.getDimensions.foreach(p => {varDim.put(p.getName)})
      jsonObject.put("dimension_name", varDim)
      jsonObject.put("element_size", v.getElementSize)
      jsonObject.put("var_units", v.getUnitsString)
      varArray.put(v.getName.replace("-", "_"), jsonObject)
    }
    netcdf.put("variables", varArray)

    val attributes: util.List[Attribute] = netcdfFile.getGlobalAttributes
    val attrsObj: JSONObject = new JSONObject()

    for (attr <- attributes) {
      var numberValue: AnyRef = attr.getNumericValue
      if (numberValue == null) {
        numberValue = attr.getStringValue
      }
      assert(numberValue != null)
      attrsObj.put(attr.getName.replace("-", "_"), numberValue)
    }
    netcdf.put("global_attributes", attrsObj)
    val dataObj: JSONObject = new JSONObject()

    for (v <- variables) {
      val valueName: Variable = netcdfFile.findVariable(v.getName)
      if (valueName != null) {
        val values = new JSONArray()
        valueName.getDataType match {
          case DataType.FLOAT => valueName.read.copyTo1DJavaArray().asInstanceOf[Array[Float]].foreach(values.put(_))
          case DataType.SHORT => valueName.read.copyTo1DJavaArray().asInstanceOf[Array[Short]].foreach(values.put(_))
          case DataType.INT => valueName.read.copyTo1DJavaArray().asInstanceOf[Array[Int]].foreach(values.put(_))
          case _ => throw new InvalidClassException(s"Unmatched data type of ${valueName.getDataType.toString}")
        }

        dataObj.put(valueName.getName.replace("-", "_"), values)
      }
    }
    netcdf.put("data", dataObj)
    netcdfFile.close()

    val destFile =
      if (!outFileName.endsWith(".gz")) {
        outFileName + ".gz"
      } else {
        outFileName
      }

    //Write to outputs
    FileUtils.forceMkdir(new File(destFile).getParentFile)
    val f: FileOutputStream = new FileOutputStream(destFile)
    val writer: Writer = new OutputStreamWriter(new GZIPOutputStream(f), "UTF-8")
    writer.write(netcdf.toString)
    writer.close()
    f.close()
    //------------------- Finished netcdf to json conversion -------------------------

    //Delete temporary unzipped file.
    if (gzipInput) {
      try {
        Files.deleteIfExists(Paths.get(srcFile))
      }
      catch {
        case e: IOException =>
          e.printStackTrace()
      }
    }
  }
}


