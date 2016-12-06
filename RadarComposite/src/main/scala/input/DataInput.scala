package input

import scala.collection._

import org.apache.commons.logging.LogFactory


import input.ProductTypeEnum._
import java.util

abstract class DataInput extends IDataInput {

  var vcpValue: Int = 0

  // Map(Timestamp -> (ProductType -> BeamRecord))
  val BeamSet = new mutable.HashMap[Long, mutable.HashMap[String, BeamRecord]]
  val LOG = LogFactory.getLog(getClass)

}