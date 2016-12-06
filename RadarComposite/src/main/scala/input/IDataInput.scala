package input

import scala.collection._
import input.ProductTypeEnum._

/**
 * Created by sugar on 6/19/2014.
 */
trait IDataInput {

  def Decode(input_data: String): (Long, mutable.HashMap[Long, BeamRecord])

}
