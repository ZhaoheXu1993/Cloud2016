package alg.wind

import org.apache.commons.math3.complex._
import scala.math


import scala.collection.mutable

/**
 * Created by sugar on 15/6/24.
 */
object VAD {

  // Custom implementation
  def fftVAD(radial: Array[Double], azimuth: Array[Double], elevation: Double): Map[String, Double] = {
    //Make sure radial velocity is exactly 0->2pi
    //We even don't need a fourier transform because we could calcuate fourier coefficient easily from definition
    val a1 = 2.0 / radial.length * radial.zip(azimuth).map(p => p._1 * math.cos(p._2)).sum
    val b1 = 2.0 / radial.length * radial.zip(azimuth).map(p => p._1 * math.sin(p._2)).sum
    //val a2 = 2.0 / radial.length * radial.zip(azimuth).map(p => p._1 * math.cos(2*p._2)).sum
    //val b2 = 2.0 / radial.length * radial.zip(azimuth).map(p => p._1 * math.sin(2*p._2)).sum
    val shw = math.sqrt(a1*a1 + b1*b1) / math.cos(elevation)
    val dw = if(b1 < 0) math.Pi/2 - math.atan2(a1, b1) else math.Pi*3/2 - math.atan2(a1, b1)
    Map("speed" -> shw, "direction" -> dw)
  }

  // Adopt from official document
  def wsr88dVAD(radial: Array[Double], azimuth: Array[Double], elevation: Double): Map[String, Double] = {
    val nd: Double = radial.length
    val q5: Complex = azimuth.map(p => new Complex(2 * math.cos(p), -2 * math.sin(p))).reduce((p, q) => { p.add(q) }).multiply(0.5 / nd)
    val q4: Complex = azimuth.map(p => new Complex(math.cos(p), math.sin(p))).reduce((p, q) => { p.add(q) }).multiply(0.5 / nd)
    val q3: Complex = azimuth.zip(radial).map(p => new Complex(math.cos(p._1), -math.sin(p._1)).multiply(p._2)).reduce((p, q) => { p.add(q) }).multiply(1.0 / nd)
    val q2: Complex = q4.conjugate().subtract(q5.divide(q4.conjugate().multiply(2))).divide(q4.subtract(new Complex(1, 0).divide(q4.conjugate().multiply(4))))
    val q1: Complex = new Complex(radial.sum / nd, 0).subtract(q3.divide(q4.conjugate().multiply(2))).divide(q4.subtract(new Complex(1, 0).divide(q4.conjugate().multiply(4))))
    // Compute Fourier Coefficient #1
    val _cf: Complex = q1.subtract(q2.multiply(q1.conjugate())).divide(1 - q2.abs() * q2.abs())
    val cf1: Double = radial.sum / nd - 2 * _cf.multiply(q4).getReal
    // Compute Fourier Coefficient #2
    val cf2: Double = _cf.getReal
    // Compute Fourier Coefficient #3
    val cf3: Double = _cf.getImaginary
    // Wind direction
    var dw: Double = math.Pi - math.atan2(cf3, cf2)
    if(dw < 0) {
      dw += 2 * math.Pi
    }
    // Speed
    val spw = math.sqrt(cf2*cf2 + cf3*cf3)
    val shw = spw / math.cos(elevation)
    Map("speed" -> shw, "direction" -> dw)
  }


}
