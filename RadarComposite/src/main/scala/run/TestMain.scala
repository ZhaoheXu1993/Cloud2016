package run

import com.jhlabs.map.proj.ProjectionFactory
import com.jwetherell.algorithms.data_structures.KdTree
import com.jwetherell.algorithms.data_structures.KdTree.XYZPoint
import input._
import config._
import org.apache.spark.SparkContext._
import org.apache.spark._
import org.apache.spark.storage.StorageLevel
import spark.{GateRDD, BeamRDD, GateElement, RadarRDD}


/**
 * Created by sugar on 4/25/15.
 */
object TestMain {

  def InitEnv() = {

  }

  val radarKdTree: KdTree[XYZPoint] = new KdTree[XYZPoint]()


  def reflectivityRun(args: Array[String], sc: SparkContext): Unit = {

    /* Step 1: Read beam from file
    Input = None
    Output = (file_path, file_content)
    */
    val radarRDD = RadarRDD.readFromFile(sc, SiteConf.ReflectivityInputUrl)
    radarRDD.persist(StorageLevel.MEMORY_AND_DISK)
    if(SiteConf.DEV_DEBUG)
      println(s"Total input records are ${radarRDD.count()}")

    /* Step 2: Get radar list from a simple reduce. Then update extent */
    val radarList = RadarRDD.getRadars(radarRDD.map(p => (p._1, p._2._2)))
    // TODO: Automatically set projection based on detection of radars
    Radar.setProjection(ProjectionFactory.fromPROJ4Specification(SiteConf.ProjOption))
    RadarRDD.setAutoExtent(radarList)
    if (SiteConf.DEV_DEBUG) {
      print(s"Mosaicking extent is (${SiteConf.SpatialExtend("X")._1}, ${SiteConf.SpatialExtend("Y")._1})")
      println(s" -> ${SiteConf.SpatialExtend("X")._2}, ${SiteConf.SpatialExtend("Y")._2}")
    }
    // Setup the KdTree for radars
    RadarRDD.createIndex(radarList.map(p => (Radar.getXY(p)._1, Radar.getXY(p)._2, Radar.getRadarHeight(p))))


    /* Step 3: Duplicate/Cutoff beamSet based on time
     Input is (timestamp, BeamRecord)
     TODO: It is very stupid to use time_index. Should use a datetime object directly!
     Output is (time_index, List[BeamRecord])
     */
    val indexedBeamRDD = radarRDD.flatMap(RadarRDD.groupBeamSetByTime).groupByKey()

    /* Step 4: Convert files into beamSet object
    Input is (file_path, file_content)
    Output is (timestamp, BeamRecord)
    */
    val beamRDD = indexedBeamRDD.flatMap(BeamRDD.mapBeamSetToBeam)
    beamRDD.persist(StorageLevel.MEMORY_AND_DISK_SER)
    if (SiteConf.DEV_DEBUG) {
      println(s"Total beams are ${beamRDD.count()}")
    }

    // Step 5: Convert beam to gates:
    // Input is (int, beamRecord)
    // Output is ((t, x, y, z), (values....))
    val gatesRDD = beamRDD.flatMap(GateRDD.propagateBeamToTrueGate)
    // Step 6: Put gates in grids
    val gridRDD = gatesRDD.map(GateRDD.gridGate)

    /** **********************************************************************************************
      *                               REDUCE                                                         *
      ************************************************************************************************/

    // Step 6: I guess this step is very slow. But let us have a useable one first.
    // Group by time => (time_index, gateRDD)
    val timeSet = gridRDD.groupBy(p => p._1._1)
    val rawMosaic = timeSet.map(GateRDD.mosaicRawReflectivity)

  }

  def velocityRun(args: Array[String], sc: SparkContext): Unit = {

  }

  def main(args: Array[String]): Unit = {

    val conf = new SparkConf().setAppName("FromStartFlow").setMaster("local[1]")
    conf.set("spark.serializer", "org.apache.spark.serializer.KryoSerializer")
    conf.registerKryoClasses(Array(
      classOf[LegacyBeamRecord],
      classOf[SuperResolutionBeamRecord],
      classOf[LatLonPoint],
      classOf[VCPMode],
      classOf[Radar],
      classOf[GateElement]
    ))

    val sc = new SparkContext(conf)

    this.reflectivityRun(args, sc)

    val sc2 = new SparkContext(conf)

    this.velocityRun(args, sc2)

  }

}
