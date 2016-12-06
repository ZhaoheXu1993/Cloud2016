package math

import org.jtransforms.fft._

import org.junit.Assert._
import org.junit.Test


/**
 * Created by sugar on 15/6/25.
 */
class MathTest {

  @Test
  def TestFFTW(): Unit = {
    val radial = Array(1.0, 1.0, 1.0, -1.0, -1.0, -1.0, 0, 0, 0, 0, 0, 0)
    val fftw = new DoubleFFT_1D(6)
    fftw.realForwardFull(radial)
    radial.foreach(println(_))
  }

}
