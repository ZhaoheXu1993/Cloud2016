package input

/**
 * Created by sugar on 7/5/14.
 */


/* variable description
"Azimuth":{"var_type":"float","dimension_name":["Azimuth"],"element_size":4,"var_units":"Degrees"}
 */
case class JsonInputVariable() {
  var element_size: Int = 0
  var var_type: String = null
  var dimension_name: Array[String] = null
  var var_units: Option[String] = null
}

/* dimension definition
"Azimuth": { "dimension_length": 367 }
 */
case class JsonInputDimension() {
  var dimension_length: Int = 0
}

/* global attributes
{
"Nyquist_Vel_unit": "MetersPerSecond",
"TypeName": "ReflectivityQC",
"radarName_value": "KAMX",
"vcp_unit": "dimensionless",
"SubType_value": "00.50",
"Latitude": 25.610599517822266,
"Time": 1120886945,
"SubType_unit": "dimensionless",
"Longitude": -80.41310119628906,
"MissingData": -99900,
"RangeToFirstGate": 0.1315757781267166,
"RangeFolded": -99901,
"Elevation": 0.5,
"Unit_unit": "dimensionless",
"RangeToFirstGateUnits": "Meters",
"Unit_value": "dBZ",
"vcp_value": "121",
"ElevationUnits": "Degrees",
"DataType": "SparseRadialSet",
"Height": 34,
"attributes": " Nyquist_Vel SubType Unit radarName vcp",
"radarName_unit": "dimensionless",
"FractionalTime": 0.5380000000004657,
"Nyquist_Vel_value": "0"
}
*/
case class JsonInputAttributes() {
  var Nyquist_Vel_unit: String = null
  var TypeName: String = null
  var radarName_value: String = null
  var vcp_unit: String = null
  var SubType_value: String = null
  var Latitude: Double = 0.0
  var Time: Long = 0
  var SubType_unit: String = null
  var Longitude: Double = 0.0
  var MissingData: Double = 0.0
  var RangeToFirstGate: Double = 0.0
  var RangeFolded: Double = 0.0
  var Elevation: Float = 0
  var Unit_unit: String = null
  var RangeToFirstGateUnits: String = null
  var Unit_value: String = null
  var vcp_value: String = null
  var ElevationUnits: String = null
  var DataType: String = null
  var Height: Float = 0
  var attributes: String = null
  var radarName_unit: String = null
  var FractionalTime: Double = 0.0
  var Nyquist_Vel_value: String = null
}


/* data section
   TODO: data example
 */
case class JsonInputVariableValue() {
  var pixel_x: Array[Int] = null
  var pixel_y: Array[Int] = null
  var pixel_count: Array[Int] = null
  var Azimuth: Array[Float] = null
  var Reflectivity: Array[Double] = null
  var ReflectivityQC: Array[Double] = null
  var AliasedVelocity: Array[Double] = null
  var Velocity: Array[Double] = null
  var SpectrumWidth: Array[Double] = null
  var UnknownVariable: Array[Double] = null
  var GateWidth: Array[Float] = null
  var AzimuthalSpacing: Array[Float] = null
  var BeamWidth: Array[Float] = null

}

/* complete record
   TODO: complete an example here
 */
case class JsonInputFormat() {
  var variables: Map[String, JsonInputVariable] = null
  var global_attributes: JsonInputAttributes = new JsonInputAttributes()
  var data: JsonInputVariableValue = new JsonInputVariableValue()
  var dimensions: Map[String, JsonInputDimension] = null
}
