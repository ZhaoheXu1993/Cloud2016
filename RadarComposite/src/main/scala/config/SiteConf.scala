package config

import com.github.nscala_time.time.Imports._
import scala.collection.mutable

/**
 * Created by miaoneng on 1/6/14.
 */

object SiteConf {

  val AdjustGroundDistance: Boolean = false


  val DEV_DEBUG = true

  // Change this if you have different version of ArcGIS Runtime installed
  val ArcGIS_Runtime_Version = "10_2_3"
  val ArcGIS_Runtime_Home = if (System.getenv(s"ARCGISRUNTIMESDKJAVA_${ArcGIS_Runtime_Version}") == null) {
    "/home/sugar/arcgis/runtime_sdk/java10.2.3"
  } else {
    System.getenv(s"ARCGISRUNTIMESDKJAVA_${ArcGIS_Runtime_Version}")
  }
  val ArcGIS_Runtime_Package = ""

  // Set initial folder contains all files.
  // TODO: Be able to retrieve radar from a map-reduce task. Not based on folder scan
  val ReflectivityInputUrl = "file:///Volumes/Shared/Projects/RadarMapper/src/test/resources/out2/*/*"
  // TODO: This need reflectivity pre-calculated. Because we need it for terminal velocity
  val VelocityInputUrl = null

  // Set this value to desired start date.
  // This should be the only thing that we could change in because we may need dynamically determine start time
  val StartTime: DateTime = new DateTime(2005, 7, 9, 0, 0, 0, DateTimeZone.UTC)
  val EndTime: DateTime = new DateTime(2005, 7, 10, 0, 0, 0, DateTimeZone.UTC)

  // Temporal Resolution in milliseconds
  val TemporalResolution = 5.minutes

  // Spatial extend in CS
  // Null means we need calculate radar extent automatically.
  val SpatialExtend = scala.collection.mutable.Map("X" -> null, "Y" -> null, "Z" -> (500.0, 14000.0))

  val SpatialMargin = 50000

  val RadarRadius = 230000.0 // This one is optinally to be 500000.0

  // Spatial resolution in CS
  val SpatialResolution = Map("X" -> 200, "Y" -> 200, "Z" -> 200)

  // Projection String, default is USA_Contiguous_LCC, use Proj4 format
  val ProjOption = Array[String]("+proj=lcc", "+datum=WGS84", "+ellps=WGS84", "+lat_0=39", "+lat_1=33", "+lat_2=45", "+lon_0=-80", "+no_defs")
}
