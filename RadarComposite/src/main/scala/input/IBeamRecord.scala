package input

/**
 * @author sugar
 *
 */
abstract trait IBeamRecord {

    def getBinCount: Int

    def getBinValue(index: Int): Double

    def getBeamTime: Long

    def getRadar: Radar

    def getVCPMode: VCPMode

    def getElevation: Double

    def getAzimuth: Double

    def getGateWidth: Double
}