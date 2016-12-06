package spark

import input.Radar

import scala.collection.mutable

/**
 * Created by sugar on 5/25/15.
 */

@SerialVersionUID(200)
case class GateElement(value: Double, meta: mutable.HashMap[String, Any]) extends Serializable {

}
