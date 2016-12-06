package input

object ProductTypeEnum extends Enumeration {
  type ProductTypeEnum = Value
  val Reflectivity = Value
  val AliasedVelocity = Value
}

object Waveform extends Enumeration {
  type Waveform = Value
  val CS = Value
  val CD = Value
  val Other = Value
}