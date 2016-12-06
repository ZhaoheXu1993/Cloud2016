package spark

import com.jwetherell.algorithms.data_structures.KdTree
import com.jwetherell.algorithms.data_structures.KdTree.XYZPoint
import input._
import config._
import org.apache.spark._
import org.apache.spark.SparkContext._
import org.apache.spark.rdd._
import run.TestMain


import scala.collection.mutable.ListBuffer
import scala.collection.{Seq, mutable}

/**
 * Created by sugar on 4/25/15.
 */
object RadarRDD {

  // Put radars into a kd-tree so we could know the nearest radar simply
  def createIndex(radars: Array[(Double, Double, Double)]) = {
    radars.foreach(r => {
      val xyz = new XYZPoint(r._1, r._2, r._3)
      TestMain.radarKdTree.add(xyz)
    })
  }


  // List radars from inputs
  def getRadars(rdd: RDD[(String, mutable.HashMap[Long, BeamRecord])]) = {
    rdd.flatMap(p => p._2.map(q => q._2.getRadar.radarName)).distinct().collect()
  }


  // Convert file content to beamSet object.
  // Input is folder_path
  // Output is (file_path, beamSet object)
  def readFromFile(sc: SparkContext, inputUrl: String) = {

    def mapBeamSet(s: (String, String)) = {
      // TODO: Pass a parameter here to read reflectivity
      val dataDecoder = new JsonInput(ProductTypeEnum.Reflectivity)
      // Return (file_path, beamSet object)
      s._1 -> dataDecoder.Decode(s._2)
    }

    val fileRDD = sc.wholeTextFiles(inputUrl)
    fileRDD.map(mapBeamSet)

  }

  // Duplicate or cut beamSet based on output-time, resolution and VCP Mode (optional)
  // Input is (file_path, (beamSet time, beamSet))
  // Output is (time_index, beamSet)
  def groupBeamSetByTime(s: (String, (Long, mutable.HashMap[Long, BeamRecord]))): Seq[(Int, mutable.HashMap[Long, BeamRecord])] = {
    val result = new ListBuffer[(Int, mutable.HashMap[Long, BeamRecord])]

    val currentIndex = 0

    result.toSeq
  }


  def setAutoExtent(radarList: Array[String]) = {

    // We want as many radar as possible, so enclose with a radar ractangle
    if (SiteConf.SpatialExtend("X") == null) {
      //SiteConf.SpatialExtend("X") = (radarList.map(p => Radar.getXY(p)._1).min - SiteConf.RadarRadius, radarList.map(p => Radar.getXY(p)._2).min - SiteConf.RadarRadius)
      SiteConf.SpatialExtend("X") = (radarList.map(p => Radar.getXY(p)._1).min, radarList.map(p => Radar.getXY(p)._2).min)
    }
    if (SiteConf.SpatialExtend("Y") == null) {
      //SiteConf.SpatialExtend("Y") = (radarList.map(p => Radar.getXY(p)._1).max + SiteConf.RadarRadius, radarList.map(p => Radar.getXY(p)._2).max + SiteConf.RadarRadius)
      SiteConf.SpatialExtend("Y") = (radarList.map(p => Radar.getXY(p)._1).max, radarList.map(p => Radar.getXY(p)._2).max)
    }

  }

}
