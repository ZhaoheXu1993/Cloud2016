package input

import scala.collection._

/**
 * @author sugar
 */

abstract class BeamRecord(val beamTime: Long, val radar: Radar, val vcp: VCPMode, val elevation: Double, val Azimuth: Double,
                 val gateWidth: Double, val beamWidth: Double, val rangeToFirstGate: Double)
  extends IBeamRecord {

  val binValues  = new mutable.ArrayBuffer[Double](460)

  var binIndex: Int = 0

  val azimuthSpacing = new mutable.ArrayBuffer[Double](1)

  def getBinCount: Int = binValues.length

  def getBinValue(index: Int): Double = binValues(index)

  def getBeamTime: Long = this.beamTime

  def getRadar: Radar = this.radar

  def getVCPMode: VCPMode = this.vcp

  def getAzimuth: Double = this.Azimuth

  def getElevation: Double = this.elevation

  def getGateWidth: Double = this.gateWidth

}

@SerialVersionUID(500)
class LegacyBeamRecord(beamTime: Long, radar: Radar, vcp: VCPMode, elevation: Double, azimuth: Double, range: Double)
  extends BeamRecord(beamTime, radar, vcp, elevation, azimuth, 1000, 1.0, range) with Serializable {

  override val binValues = new mutable.ArrayBuffer[Double](500)

}

@SerialVersionUID(2000)
class SuperResolutionBeamRecord(beamTime: Long, radar: Radar, vcp: VCPMode, elevation: Double, azimuth: Double, range: Double)
  extends BeamRecord(beamTime, radar, vcp, elevation, azimuth, 250, 0.5, range) with Serializable {

  override val binValues = new mutable.ArrayBuffer[Double](2000)

}