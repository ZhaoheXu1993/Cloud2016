package input

import java.awt.geom.Point2D
import scala.collection._

import com.jhlabs.map.proj.Projection

object Radar extends Serializable {

  val Radars = new mutable.HashMap[String, Array[Double]]

  def isProjected: Boolean = {
    Radars.nonEmpty && (!Radars("KAKQ")(2).isNaN)
  }

  private def InitRadarList(): Unit = {
    Radars.put("KABR", Array[Double](45.4560, -98.41300, Double.NaN, Double.NaN, 1302.0))
    Radars.put("KABX", Array[Double](35.1500, -106.8240, Double.NaN, Double.NaN, 5870.0))
    Radars.put("KAKQ", Array[Double](36.9840, -77.00700, Double.NaN, Double.NaN, 112.0))
    Radars.put("KAMA", Array[Double](35.2330, -101.7090, Double.NaN, Double.NaN, 3587.0))
    Radars.put("KAMX", Array[Double](25.6110, -80.41300, Double.NaN, Double.NaN, 14.0))
    Radars.put("KAPX", Array[Double](44.9070, -84.72000, Double.NaN, Double.NaN, 1464.0))
    Radars.put("KARX", Array[Double](43.8230, -91.19100, Double.NaN, Double.NaN, 1276.0))
    Radars.put("KATX", Array[Double](48.1940, -122.4960, Double.NaN, Double.NaN, 494.0))
    Radars.put("KBBX", Array[Double](39.4960, -121.6320, Double.NaN, Double.NaN, 173.0))
    Radars.put("KBGM", Array[Double](42.2000, -75.98500, Double.NaN, Double.NaN, 1606.0))
    Radars.put("KBHX", Array[Double](40.4980, -124.2920, Double.NaN, Double.NaN, 2402.0))
    Radars.put("KBIS", Array[Double](46.7710, -100.7610, Double.NaN, Double.NaN, 1658.0))
    Radars.put("KBIX", Array[Double](30.5240, -88.98500, Double.NaN, Double.NaN, 136.0))
    Radars.put("KBLX", Array[Double](45.8540, -108.6070, Double.NaN, Double.NaN, 3598.0))
    Radars.put("KBMX", Array[Double](33.1720, -86.77000, Double.NaN, Double.NaN, 645.0))
    Radars.put("KBOX", Array[Double](41.9560, -71.13700, Double.NaN, Double.NaN, 118.0))
    Radars.put("KBRO", Array[Double](25.9160, -97.41900, Double.NaN, Double.NaN, 23.0))
    Radars.put("KBUF", Array[Double](42.9490, -78.73700, Double.NaN, Double.NaN, 693.0))
    Radars.put("KBYX", Array[Double](24.5980, -81.70300, Double.NaN, Double.NaN, 8.0))
    Radars.put("KCAE", Array[Double](33.9490, -81.11800, Double.NaN, Double.NaN, 231.0))
    Radars.put("KCBW", Array[Double](46.0390, -67.80600, Double.NaN, Double.NaN, 746.0))
    Radars.put("KCBX", Array[Double](43.4910, -116.2360, Double.NaN, Double.NaN, 3061.0))
    Radars.put("KCCX", Array[Double](40.9230, -78.00400, Double.NaN, Double.NaN, 2405.0))
    Radars.put("KCLE", Array[Double](41.4130, -81.86000, Double.NaN, Double.NaN, 763.0))
    Radars.put("KCLX", Array[Double](32.6560, -81.04200, Double.NaN, Double.NaN, 97.0))
    Radars.put("KCRI", Array[Double](35.2380, -97.46000, Double.NaN, Double.NaN, 1295.0))
    Radars.put("KCRP", Array[Double](27.7840, -97.51100, Double.NaN, Double.NaN, 45.0))
    Radars.put("KCXX", Array[Double](44.5110, -73.16700, Double.NaN, Double.NaN, 317.0))
    Radars.put("KCYS", Array[Double](41.1520, -104.8060, Double.NaN, Double.NaN, 6128.0))
    Radars.put("KDAX", Array[Double](38.5010, -121.6780, Double.NaN, Double.NaN, 30.0))
    Radars.put("KDDC", Array[Double](37.7610, -99.96900, Double.NaN, Double.NaN, 2590.0))
    Radars.put("KDFX", Array[Double](29.2730, -100.2810, Double.NaN, Double.NaN, 1131.0))
    Radars.put("KDIX", Array[Double](39.9470, -74.41100, Double.NaN, Double.NaN, 149.0))
    Radars.put("KDLH", Array[Double](46.8370, -92.21000, Double.NaN, Double.NaN, 1428.0))
    Radars.put("KDMX", Array[Double](41.7310, -93.72300, Double.NaN, Double.NaN, 981.0))
    Radars.put("KDOX", Array[Double](38.8260, -75.44000, Double.NaN, Double.NaN, 50.0))
    Radars.put("KDTX", Array[Double](42.7000, -83.47200, Double.NaN, Double.NaN, 1072.0))
    Radars.put("KDVN", Array[Double](41.6120, -90.58100, Double.NaN, Double.NaN, 754.0))
    Radars.put("KDYX", Array[Double](32.5380, -99.25400, Double.NaN, Double.NaN, 1517.0))
    Radars.put("KEAX", Array[Double](38.8100, -94.26400, Double.NaN, Double.NaN, 995.0))
    Radars.put("KEMX", Array[Double](31.8940, -110.6300, Double.NaN, Double.NaN, 5202.0))
    Radars.put("KENX", Array[Double](42.5860, -74.06400, Double.NaN, Double.NaN, 1826.0))
    Radars.put("KEOX", Array[Double](31.4610, -85.45900, Double.NaN, Double.NaN, 434.0))
    Radars.put("KEPZ", Array[Double](31.8730, -106.6980, Double.NaN, Double.NaN, 4104.0))
    Radars.put("KESX", Array[Double](35.7010, -114.8910, Double.NaN, Double.NaN, 4867.0))
    Radars.put("KEVX", Array[Double](30.5640, -85.92100, Double.NaN, Double.NaN, 140.0))
    Radars.put("KEWX", Array[Double](29.7040, -98.02800, Double.NaN, Double.NaN, 633.0))
    Radars.put("KEYX", Array[Double](35.0980, -117.5610, Double.NaN, Double.NaN, 2757.0))
    Radars.put("KFCX", Array[Double](37.0240, -80.27400, Double.NaN, Double.NaN, 2868.0))
    Radars.put("KFDR", Array[Double](34.3620, -98.97600, Double.NaN, Double.NaN, 1267.0))
    Radars.put("KFDX", Array[Double](34.6350, -103.6300, Double.NaN, Double.NaN, 4650.0))
    Radars.put("KFFC", Array[Double](33.3640, -84.56600, Double.NaN, Double.NaN, 858.0))
    Radars.put("KFSD", Array[Double](43.5880, -96.72900, Double.NaN, Double.NaN, 1430.0))
    Radars.put("KFSX", Array[Double](34.5740, -111.1980, Double.NaN, Double.NaN, 7417.0))
    Radars.put("KFTG", Array[Double](39.7870, -104.5460, Double.NaN, Double.NaN, 5497.0))
    Radars.put("KFWS", Array[Double](32.5730, -97.30300, Double.NaN, Double.NaN, 683.0))
    Radars.put("KGGW", Array[Double](48.2060, -106.6250, Double.NaN, Double.NaN, 2276.0))
    Radars.put("KGJX", Array[Double](39.0620, -108.2140, Double.NaN, Double.NaN, 9992.0))
    Radars.put("KGLD", Array[Double](39.3670, -101.7000, Double.NaN, Double.NaN, 3651.0))
    Radars.put("KGRB", Array[Double](44.4980, -88.11100, Double.NaN, Double.NaN, 682.0))
    Radars.put("KGRK", Array[Double](30.7220, -97.38300, Double.NaN, Double.NaN, 538.0))
    Radars.put("KGRR", Array[Double](42.8940, -85.54500, Double.NaN, Double.NaN, 778.0))
    Radars.put("KGSP", Array[Double](34.8830, -82.22000, Double.NaN, Double.NaN, 940.0))
    Radars.put("KGWX", Array[Double](33.8970, -88.32900, Double.NaN, Double.NaN, 476.0))
    Radars.put("KGYX", Array[Double](43.8910, -70.25600, Double.NaN, Double.NaN, 409.0))
    Radars.put("KHDX", Array[Double](33.0760, -106.1230, Double.NaN, Double.NaN, 4222.0))
    Radars.put("KHGX", Array[Double](29.4720, -95.07900, Double.NaN, Double.NaN, 18.0))
    Radars.put("KHNX", Array[Double](36.3140, -119.6320, Double.NaN, Double.NaN, 243.0))
    Radars.put("KHPX", Array[Double](36.7370, -87.28500, Double.NaN, Double.NaN, 576.0))
    Radars.put("KHTX", Array[Double](34.9310, -86.08300, Double.NaN, Double.NaN, 1760.0))
    Radars.put("KICT", Array[Double](37.6550, -97.44300, Double.NaN, Double.NaN, 1335.0))
    Radars.put("KICX", Array[Double](37.5910, -112.8620, Double.NaN, Double.NaN, 10600.0))
    Radars.put("KILN", Array[Double](39.4200, -83.82200, Double.NaN, Double.NaN, 1056.0))
    Radars.put("KILX", Array[Double](40.1510, -89.33700, Double.NaN, Double.NaN, 582.0))
    Radars.put("KIND", Array[Double](39.7080, -86.28000, Double.NaN, Double.NaN, 790.0))
    Radars.put("KINX", Array[Double](36.1750, -95.56500, Double.NaN, Double.NaN, 668.0))
    Radars.put("KIWA", Array[Double](33.2890, -111.6700, Double.NaN, Double.NaN, 1353.0))
    Radars.put("KIWX", Array[Double](41.3590, -85.70000, Double.NaN, Double.NaN, 960.0))
    Radars.put("KDGX", Array[Double](32.2800, -89.98400, Double.NaN, Double.NaN, 609.0))
    Radars.put("KJAX", Array[Double](30.4850, -81.70200, Double.NaN, Double.NaN, 33.0))
    Radars.put("KJGX", Array[Double](32.6750, -83.35100, Double.NaN, Double.NaN, 521.0))
    Radars.put("KJKL", Array[Double](37.5910, -83.31300, Double.NaN, Double.NaN, 1364.0))
    Radars.put("KLBB", Array[Double](33.6540, -101.8140, Double.NaN, Double.NaN, 3259.0))
    Radars.put("KLCH", Array[Double](30.1250, -93.21600, Double.NaN, Double.NaN, 13.0))
    Radars.put("KLIX", Array[Double](30.3370, -89.82600, Double.NaN, Double.NaN, 24.0))
    Radars.put("KLNX", Array[Double](41.9580, -100.5760, Double.NaN, Double.NaN, 2970.0))
    Radars.put("KLOT", Array[Double](41.6050, -88.08500, Double.NaN, Double.NaN, 663.0))
    Radars.put("KLRX", Array[Double](40.7400, -116.8030, Double.NaN, Double.NaN, 6744.0))
    Radars.put("KLSX", Array[Double](38.6990, -90.68300, Double.NaN, Double.NaN, 608.0))
    Radars.put("KLTX", Array[Double](33.9890, -78.42900, Double.NaN, Double.NaN, 64.0))
    Radars.put("KLVX", Array[Double](37.9750, -85.94400, Double.NaN, Double.NaN, 719.0))
    Radars.put("KLWX", Array[Double](38.9750, -77.47800, Double.NaN, Double.NaN, 272.0))
    Radars.put("KLZK", Array[Double](34.8360, -92.26200, Double.NaN, Double.NaN, 568.0))
    Radars.put("KMAF", Array[Double](31.9430, -102.1890, Double.NaN, Double.NaN, 2868.0))
    Radars.put("KMAX", Array[Double](42.0810, -122.7170, Double.NaN, Double.NaN, 7513.0))
    Radars.put("KMBX", Array[Double](48.3930, -100.8650, Double.NaN, Double.NaN, 1493.0))
    Radars.put("KMHX", Array[Double](34.7760, -76.87600, Double.NaN, Double.NaN, 31.0))
    Radars.put("KMKX", Array[Double](42.9680, -88.55100, Double.NaN, Double.NaN, 958.0))
    Radars.put("KMLB", Array[Double](28.1130, -80.65400, Double.NaN, Double.NaN, 35.0))
    Radars.put("KMOB", Array[Double](30.6790, -88.24000, Double.NaN, Double.NaN, 208.0))
    Radars.put("KMPX", Array[Double](44.8490, -93.56600, Double.NaN, Double.NaN, 946.0))
    Radars.put("KMQT", Array[Double](46.5310, -87.54800, Double.NaN, Double.NaN, 1411.0))
    Radars.put("KMRX", Array[Double](36.1690, -83.40200, Double.NaN, Double.NaN, 1337.0))
    Radars.put("KMSX", Array[Double](47.0410, -113.9860, Double.NaN, Double.NaN, 7855.0))
    Radars.put("KMTX", Array[Double](41.2630, -112.4480, Double.NaN, Double.NaN, 0.0))
    Radars.put("KMUX", Array[Double](37.1550, -121.8980, Double.NaN, Double.NaN, 3469.0))
    Radars.put("KMVX", Array[Double](47.5280, -97.32600, Double.NaN, Double.NaN, 986.0))
    Radars.put("KMXX", Array[Double](32.5370, -85.79000, Double.NaN, Double.NaN, 400.0))
    Radars.put("KNKX", Array[Double](32.9190, -117.0420, Double.NaN, Double.NaN, 955.0))
    Radars.put("KNQA", Array[Double](35.3450, -89.87300, Double.NaN, Double.NaN, 282.0))
    Radars.put("KOAX", Array[Double](41.3200, -96.36700, Double.NaN, Double.NaN, 1148.0))
    Radars.put("KOHX", Array[Double](36.2470, -86.56300, Double.NaN, Double.NaN, 579.0))
    Radars.put("KOKX", Array[Double](40.8660, -72.86400, Double.NaN, Double.NaN, 85.0))
    Radars.put("KOTX", Array[Double](47.6800, -117.6270, Double.NaN, Double.NaN, 2384.0))
    Radars.put("KPAH", Array[Double](37.0680, -88.77200, Double.NaN, Double.NaN, 392.0))
    Radars.put("KPBZ", Array[Double](40.5320, -80.21800, Double.NaN, Double.NaN, 1185.0))
    Radars.put("KPDT", Array[Double](45.6910, -118.8530, Double.NaN, Double.NaN, 1515.0))
    Radars.put("KPOE", Array[Double](31.1560, -92.97600, Double.NaN, Double.NaN, 408.0))
    Radars.put("KPUX", Array[Double](38.4590, -104.1810, Double.NaN, Double.NaN, 5249.0))
    Radars.put("KRAX", Array[Double](35.6660, -78.49000, Double.NaN, Double.NaN, 348.0))
    Radars.put("KRGX", Array[Double](39.7540, -119.4620, Double.NaN, Double.NaN, 8299.0))
    Radars.put("KRIW", Array[Double](43.0660, -108.4770, Double.NaN, Double.NaN, 5568.0))
    Radars.put("KRLX", Array[Double](38.3110, -81.72300, Double.NaN, Double.NaN, 1080.0))
    Radars.put("KRMX", Array[Double](43.4680, -75.45800, Double.NaN, Double.NaN, 1516.0))
    Radars.put("KRTX", Array[Double](45.7150, -122.9650, Double.NaN, Double.NaN, 1572.0))
    Radars.put("KSFX", Array[Double](43.1060, -112.6860, Double.NaN, Double.NaN, 4474.0))
    Radars.put("KSGF", Array[Double](37.2350, -93.40100, Double.NaN, Double.NaN, 1278.0))
    Radars.put("KSHV", Array[Double](32.4510, -93.84100, Double.NaN, Double.NaN, 273.0))
    Radars.put("KSJT", Array[Double](31.3710, -100.4930, Double.NaN, Double.NaN, 1890.0))
    Radars.put("KSOX", Array[Double](33.8180, -117.6360, Double.NaN, Double.NaN, 3027.0))
    Radars.put("KSRX", Array[Double](35.2910, -94.36200, Double.NaN, Double.NaN, 640.0))
    Radars.put("KTBW", Array[Double](27.7060, -82.40200, Double.NaN, Double.NaN, 41.0))
    Radars.put("KTFX", Array[Double](47.4600, -111.3850, Double.NaN, Double.NaN, 3714.0))
    Radars.put("KTLH", Array[Double](30.3980, -84.32900, Double.NaN, Double.NaN, 63.0))
    Radars.put("KTLX", Array[Double](35.3330, -97.27800, Double.NaN, Double.NaN, 1213.0))
    Radars.put("KTWX", Array[Double](38.9970, -96.23300, Double.NaN, Double.NaN, 1367.0))
    Radars.put("KTYX", Array[Double](43.7560, -75.68000, Double.NaN, Double.NaN, 1846.0))
    Radars.put("KUDX", Array[Double](44.1250, -102.8300, Double.NaN, Double.NaN, 3016.0))
    Radars.put("KUEX", Array[Double](40.3210, -98.44200, Double.NaN, Double.NaN, 1976.0))
    Radars.put("KVAX", Array[Double](30.8900, -83.00200, Double.NaN, Double.NaN, 178.0))
    Radars.put("KVBX", Array[Double](34.8380, -120.3970, Double.NaN, Double.NaN, 1233.0))
    Radars.put("KVNX", Array[Double](36.7410, -98.12800, Double.NaN, Double.NaN, 1210.0))
    Radars.put("KVTX", Array[Double](34.4120, -119.1790, Double.NaN, Double.NaN, 2726.0))
    Radars.put("KVWX", Array[Double](38.2666, -87.71660, Double.NaN, Double.NaN, 392.0))
    Radars.put("KYUX", Array[Double](32.4950, -114.6570, Double.NaN, Double.NaN, 174.0))
    Radars.put("LPLA", Array[Double](38.7300, -27.32200, Double.NaN, Double.NaN, 3334.0))
    Radars.put("PABC", Array[Double](60.7920, -161.8760, Double.NaN, Double.NaN, 162.0))
    Radars.put("PACG", Array[Double](56.8530, -135.5290, Double.NaN, Double.NaN, 270.0))
    Radars.put("PAEC", Array[Double](64.5110, -165.2950, Double.NaN, Double.NaN, 54.0))
    Radars.put("PAHG", Array[Double](60.7260, -151.3510, Double.NaN, Double.NaN, 242.0))
    Radars.put("PAIH", Array[Double](59.4610, -146.3030, Double.NaN, Double.NaN, 67.0))
    Radars.put("PAKC", Array[Double](58.6790, -156.6290, Double.NaN, Double.NaN, 63.0))
    Radars.put("PAPD", Array[Double](65.0350, -147.5020, Double.NaN, Double.NaN, 2593.0))
    Radars.put("PGUA", Array[Double](13.4540, 144.80800, Double.NaN, Double.NaN, 264.0))
    Radars.put("PHKI", Array[Double](21.8940, -159.5520, Double.NaN, Double.NaN, 179.0))
    Radars.put("PHKM", Array[Double](20.1260, -155.7780, Double.NaN, Double.NaN, 3812.0))
    Radars.put("PHMO", Array[Double](21.1330, -157.1800, Double.NaN, Double.NaN, 1363.0))
    Radars.put("PHWA", Array[Double](19.0950, -155.5690, Double.NaN, Double.NaN, 1370.0))
    Radars.put("RKJK", Array[Double](35.9240, 126.62200, Double.NaN, Double.NaN, 78.0))
    Radars.put("RKSG", Array[Double](36.9560, 127.02100, Double.NaN, Double.NaN, 52.0))
    Radars.put("RODN", Array[Double](26.3020, 127.91000, Double.NaN, Double.NaN, 218.0))
    Radars.put("TJUA", Array[Double](18.1160, -66.07800, Double.NaN, Double.NaN, 2794.0))
    Radars.put("KJAN", Array[Double](32.3180, -90.08000, Double.NaN, Double.NaN, 297.0))
    Radars.put("KOUN", Array[Double](35.2360, -97.46235, Double.NaN, Double.NaN, 1214.0))
    Radars.put("KLGX", Array[Double](47.1158, -124.1069, Double.NaN, Double.NaN, 366.0))
  }

  def setProjection(projection: Projection): Unit = {
    if(this.isProjected) {
      println("ERROR: Already projected. Cannot change projection in one job.")
      return
    }
    if(projection != null) {
      val src = new Point2D.Double(0.0, 0.0)
      val dst = new Point2D.Double(0.0, 0.0)
      Radars.foreach(p => {
        val r = p._2
        src.x = r(1) // Lon is X
        src.y = r(0) // Lat is Y
        projection.transform(src, dst)
        r(2) = dst.x
        r(3) = dst.y
      })
    } else {
      Radars.foreach(p => {
        p._2(2) = p._2(1) // X = Lon
        p._2(3) = p._2(0) // Y = Lat
      })
    }
  }

  def getXY(radarName: String) = {
    val radar = Radars(radarName)
    (radar(2), radar(3))
  }

  def getLatLon(radarName: String) = {
    val radar = Radars(radarName)
    (radar(0), radar(1))
  }

  def getRadarHeight(radarName: String): Double =
    Radars(radarName)(4)

  def getAbsoluteBeamHeightFromRadar(radarName: String, slantRange: Double, elevation: Double): Double =
    getRelativeBeamHeight(elevation, slantRange) + getRadarHeight(radarName)

  def getRelativeBeamHeight(slantRange: Double, elevation: Double): Double =
    NexradEquation.getRelativeBeamHeight(elevation, slantRange)

  // Constructor
  InitRadarList()
}

@SerialVersionUID(100)
class Radar(val radarName: String) extends Serializable {

  def getRadarHeight = Radar.getRadarHeight(this.radarName)

  def getXY = Radar.getXY(this.radarName)

  def getLatLon = Radar.getLatLon(this.radarName)

  def getAbsoluteBeamHeightFromRadar(slantRange: Double, elevation: Double) =
    Radar.getAbsoluteBeamHeightFromRadar(this.radarName, slantRange, elevation)

}


