package input

import scala.collection._
import input.Waveform._

class VCPMode {

  protected var AZRate: mutable.HashMap[Double, Double] = null
  protected var AZRate2: mutable.HashMap[Double, Double] = null
  private var ScanMode: String = null

  def this(scanMode: String) {
    this()
    this.ScanMode = scanMode
    this.ScanMode match {
      case "11"  => initVCP11()
      case "12"  => initVCP12()
      case "21"  => initVCP21()
      case "31"  => initVCP31()
      case "32"  => initVCP32()
      case "121" => initVCP121()
      case "211" => initVCP211()
      case "212" => initVCP212()
      case "221" => initVCP221()
      case _     => throw new IllegalArgumentException("Unknown VCP Codes.")
    }
  }

  def getTotalScanTime: Double = {
    360000 // Because in general VCP in precipitation mode is less than 6 min, this should be safe
  }

  def getAZRate(subType: Double, scan: Waveform): Double = {
    if (scan == Waveform.CS) AZRate(subType) else AZRate2(subType)
  }

  private def initVCP221() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 11.340000)
    m1.put(1.450000, 1000.0 / 11.340000)
    m1.put(2.400000, 1000.0 / 11.190000)
    m1.put(3.350000, 1000.0 / 11.190000)
    m1.put(4.300000, 1000.0 / 11.190000)
    m1.put(6.000000, 1000.0 / 11.190000)
    m1.put(9.900000, 1000.0 / 12.130000)
    m1.put(14.600000, 1000.0 / 12.130000)
    m1.put(19.500000, 1000.0 / 12.130000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 15.610000)
    m2.put(1.450000, 1000.0 / 15.610000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP212() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 21.150000)
    m1.put(0.900000, 1000.0 / 21.150000)
    m1.put(1.300000, 1000.0 / 21.150000)
    m1.put(1.800000, 1000.0 / 24.640000)
    m1.put(2.400000, 1000.0 / 26.400000)
    m1.put(3.100000, 1000.0 / 26.400000)
    m1.put(4.000000, 1000.0 / 26.400000)
    m1.put(5.100000, 1000.0 / 28.010000)
    m1.put(6.400000, 1000.0 / 28.010000)
    m1.put(8.000000, 1000.0 / 28.400000)
    m1.put(10.000000, 1000.0 / 28.880000)
    m1.put(12.500000, 1000.0 / 28.740000)
    m1.put(15.600000, 1000.0 / 28.740000)
    m1.put(19.500000, 1000.0 / 28.740000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 16.900000)
    m2.put(0.900000, 1000.0 / 16.900000)
    m2.put(1.300000, 1000.0 / 16.900000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP211() {
    val m1  = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 18.680000)
    m1.put(1.450000, 1000.0 / 19.840000)
    m1.put(2.400000, 1000.0 / 16.120000)
    m1.put(3.350000, 1000.0 / 17.900000)
    m1.put(4.350000, 1000.0 / 17.900000)
    m1.put(5.250000, 1000.0 / 17.460000)
    m1.put(6.200000, 1000.0 / 17.470000)
    m1.put(7.500000, 1000.0 / 25.170000)
    m1.put(8.700000, 1000.0 / 25.400000)
    m1.put(10.000000, 1000.0 / 25.420000)
    m1.put(12.000000, 1000.0 / 25.470000)
    m1.put(14.000000, 1000.0 / 25.510000)
    m1.put(16.700000, 1000.0 / 25.600000)
    m1.put(19.500000, 1000.0 / 25.700000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 19.750000)
    m2.put(1.450000, 1000.0 / 19.750000)
  }

  private def initVCP121() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 18.677000)
    m1.put(1.450000, 1000.0 / 19.842000)
    m1.put(2.400000, 1000.0 / 19.205000)
    m1.put(3.350000, 1000.0 / 21.600000)
    m1.put(4.300000, 1000.0 / 16.304000)
    m1.put(6.000000, 1000.0 / 20.204000)
    m1.put(9.900000, 1000.0 / 29.499000)
    m1.put(14.600000, 1000.0 / 29.795000)
    m1.put(19.500000, 1000.0 / 29.795000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 27.400000)
    m2.put(1.450000, 1000.0 / 27.400000)
    m2.put(2.400000, 1000.0 / 27.400000)
    m2.put(3.350000, 1000.0 / 27.400000)
    m2.put(4.300000, 1000.0 / 29.499000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP32() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 4.961000)
    m1.put(1.500000, 1000.0 / 4.961000)
    m1.put(2.500000, 1000.0 / 4.060000)
    m1.put(3.500000, 1000.0 / 4.061000)
    m1.put(4.500000, 1000.0 / 4.063000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 4.544000)
    m2.put(1.500000, 1000.0 / 4.544000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP31() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 5.039000)
    m1.put(1.500000, 1000.0 / 5.040000)
    m1.put(2.500000, 1000.0 / 5.041000)
    m1.put(3.500000, 1000.0 / 5.063000)
    m1.put(4.500000, 1000.0 / 5.065000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 5.039000)
    m2.put(1.500000, 1000.0 / 5.062000)
    m2.put(2.500000, 1000.0 / 5.062000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP21() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 11.339000)
    m1.put(1.450000, 1000.0 / 11.339000)
    m1.put(2.400000, 1000.0 / 11.180000)
    m1.put(3.350000, 1000.0 / 11.182000)
    m1.put(4.300000, 1000.0 / 11.185000)
    m1.put(6.000000, 1000.0 / 11.189000)
    m1.put(9.900000, 1000.0 / 14.260000)
    m1.put(14.600000, 1000.0 / 14.322000)
    m1.put(19.500000, 1000.0 / 14.415000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 11.360000)
    m2.put(1.450000, 1000.0 / 11.360000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP12() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 21.150000)
    m1.put(0.900000, 1000.0 / 21.150000)
    m1.put(1.300000, 1000.0 / 21.150000)
    m1.put(1.800000, 1000.0 / 26.640000)
    m1.put(2.400000, 1000.0 / 26.400000)
    m1.put(3.100000, 1000.0 / 26.400000)
    m1.put(4.000000, 1000.0 / 26.400000)
    m1.put(5.100000, 1000.0 / 28.010000)
    m1.put(6.400000, 1000.0 / 28.010000)
    m1.put(8.000000, 1000.0 / 28.400000)
    m1.put(10.000000, 1000.0 / 28.884000)
    m1.put(12.500000, 1000.0 / 28.741000)
    m1.put(15.600000, 1000.0 / 28.741000)
    m1.put(19.500000, 1000.0 / 28.741000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 25.000000)
    m2.put(0.900000, 1000.0 / 25.000000)
    m2.put(1.300000, 1000.0 / 25.000000)
    this.AZRate = m1
    this.AZRate2 = m2
  }

  private def initVCP11() {
    val m1 = new mutable.HashMap[Double, Double]
    m1.put(0.500000, 1000.0 / 18.675000)
    m1.put(1.450000, 1000.0 / 19.844000)
    m1.put(2.400000, 1000.0 / 16.166000)
    m1.put(3.350000, 1000.0 / 17.893000)
    m1.put(4.300000, 1000.0 / 17.898000)
    m1.put(5.250000, 1000.0 / 17.459000)
    m1.put(6.200000, 1000.0 / 17.466000)
    m1.put(7.500000, 1000.0 / 25.168000)
    m1.put(8.700000, 1000.0 / 25.398000)
    m1.put(10.000000, 1000.0 / 25.421000)
    m1.put(12.000000, 1000.0 / 25.464000)
    m1.put(14.000000, 1000.0 / 25.515000)
    m1.put(16.700000, 1000.0 / 25.596000)
    m1.put(19.500000, 1000.0 / 25.696000)
    val m2 = m1.clone()
    m2.put(0.500000, 1000.0 / 19.224000)
    m2.put(1.450000, 1000.0 / 19.225000)
    this.AZRate = m1
    this.AZRate2 = m2
  }


}