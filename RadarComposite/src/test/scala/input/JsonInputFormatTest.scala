package input

/**
 * Created by sugar on 7/5/14.
 */
import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.module.scala.DefaultScalaModule

import org.scalatest.junit.AssertionsForJUnit
import org.junit.Assert._
import org.junit.Test
import run.ReadNetcdfToJson

import scala.io.Source

class JsonInputFormatTest {

  @Test
  def TestMyself():Unit = {
    assertEquals("Test for Testings", 0, 0)
  }

  @Test
  def TestConversion(): Unit = {
    val args = Array(
      "/Volumes/Shared/Projects/RadarMapper/src/test/resources/in",
      "/Volumes/Shared/Projects/RadarMapper/src/test/resources/out")
    ReadNetcdfToJson.main(args)
  }

  @Test
  def TestReadBack(): Unit = {
    val mapper = new ObjectMapper()
    mapper.registerModule(DefaultScalaModule)
    for(i <- List("/out2/KAMX/20050709-000000.json", "/out2/KAMX/20050709-115945.json")) {
      val source = Source.fromURL(getClass.getResource(i))
      val lines = source.mkString
      val p = mapper.readValue[JsonInputFormat](lines, classOf[JsonInputFormat])
      assertNotNull(p.data.ReflectivityQC)
      assertNotNull(p.data.Azimuth)
      assertNotNull(p.data.BeamWidth)
      assertNotNull(p.data.GateWidth)
      assertNotNull(p.data.AzimuthalSpacing)
      assertNull(p.data.AliasedVelocity)
    }
  }


}
