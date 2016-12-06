package input

/**
 * Created by sugar on 7/5/14.
 */

import java.awt.geom.Point2D

import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.module.scala.DefaultScalaModule
import com.jhlabs.map.proj.ProjectionFactory
import config.SiteConf
import com.github.nscala_time.time.Imports._
import org.junit.Assert._
import org.junit.Test
import run.ReadNetcdfToJson
import spark.GateElement

import scala.collection.mutable
import scala.io.Source

class SimpleTest {

  @Test
  def TestMyself():Unit = {
    assertEquals("Test for Testings", 0, 0)
  }

  @Test
  def TestTimer():Unit = {
    val c = new DateTime(2005, 7, 9, 11, 59, 45, DateTimeZone.UTC)
    val end = SiteConf.EndTime.getMillis - SiteConf.StartTime.getMillis
    val now = c.getMillis - SiteConf.StartTime.getMillis
    val totalIndex: Long = end / SiteConf.TemporalResolution.millis
    val nowIndex: Long = now / SiteConf.TemporalResolution.millis
    println(totalIndex, nowIndex)
  }

  @Test
  def TestProjection(): Unit = {
    val params = Array[String](
      "+proj=lcc",
      "+lat_1=33.0",
      "+lat_2=45.0",
      "+lat_0=39.0",
      "+lon_0=-80.0",
      "+x_0=0.0",
      "+y_0=0.0",
      "+ellps=GRS80",
      "+datum=NAD83",
      "+units=m",
      "+no_defs")
    val proj = ProjectionFactory.fromPROJ4Specification(params)
    val src = new Point2D.Double(-80.0, 39.0)
    val dst = new Point2D.Double(0.0, 0.0)
    proj.transform(src, dst)
    assertEquals(dst.getX, 0.0, 0.001)
    assertEquals(dst.getY, 0.0, 0.001)
  }

  @Test
  def TestGateEqual():Unit = {
    val a = new mutable.HashMap[String, Any]
    val b = new mutable.HashMap[String, Any]
    a("1") = 1
    b("1") = 1
    val c = new GateElement(1.0, a)
    val d = new GateElement(1.0, b)
    assertEquals(c, d)

  }


}
