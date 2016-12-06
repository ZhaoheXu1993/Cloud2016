package spark

import input.{ProductTypeEnum, JsonInput, BeamRecord}
import config._
import scala.collection._
import scala.collection.mutable.ListBuffer

/**
 * Created by sugar on 4/25/15.
 */
object BeamRDD {



  /*
  Given a time_index, convert all beam-set tagged this time_index to beams, assign them exact same key time_index
  Input is (time_index, (beamSet time, beamSet))
  Output is (time_index, beamRecord)
  */
  def mapBeamSetToBeam(s:(Int, Iterable[mutable.HashMap[Long, BeamRecord]])): Seq[(Int, BeamRecord)] = {
    val result = new ListBuffer[(Int, BeamRecord)]()
    for(beamSet <- s._2) {
      beamSet.foreach(p => {
        result += ((s._1, p._2))
      })
    }
    result.toSeq
  }



}
