package alg.wind

import java.io.File
import java.util

import alg.wind.nativelib.wind
import config._
import org.apache.commons.io.{FilenameUtils, FileUtils}
import org.apache.commons.lang.SystemUtils
import org.apache.commons.math3.analysis.{MultivariateVectorFunction, MultivariateFunction}
import org.apache.commons.math3.optim.{MaxEval, MaxIter, InitialGuess, SimpleValueChecker}
import org.apache.commons.math3.optim.nonlinear.scalar.{ObjectiveFunctionGradient, ObjectiveFunction}
import org.apache.commons.math3.optim.nonlinear.scalar.gradient._
import scala.math


/**
 * Created by sugar on 5/27/15.
 */
object WindSolve3D {

  def optimizeCostFunc(): Unit = {
    val optimizer = new NonLinearConjugateGradientOptimizer(
      NonLinearConjugateGradientOptimizer.Formula.POLAK_RIBIERE,
      new SimpleValueChecker(1e-6, 1e-6))

    // TODO: Integrate with native function, this function should return total cost.
    val costFunc = new ObjectiveFunction(new MultivariateFunction {
      override def value(doubles: Array[Double]): Double = {
        // return
        0.0
      }
    })

    // TODO: Integrate with native function, this function should return partial derivation on each param
    val costFuncGradient = new ObjectiveFunctionGradient(new MultivariateVectorFunction {
      override def value(doubles: Array[Double]): Array[Double] = {
        // return partial differential
        Array.ofDim[Double](doubles.length)
      }
    })

    // Initial guess should come from VAD
    val initialGuess = new InitialGuess(Array())

    val maxIter = new MaxIter(10000)

    val maxEval = new MaxEval(10000)

    val optimal = optimizer.optimize(costFunc, costFuncGradient, initialGuess, maxIter, maxEval)

  }

  var useNative = true

  def loadNativeLibrary(): Unit = {
    try {
      val libraryPath = System.getenv("RC_NATIVE_WIND")
      System.loadLibrary(libraryPath)
      useNative = true
    } catch {
      case (_: NullPointerException | _: UnsatisfiedLinkError) => try {
        // Find library in path
        val libPath = FilenameUtils.getPath(
          classOf[nativelib.wind].getProtectionDomain.getCodeSource.getLocation.getFile)
        val libName = FilenameUtils.concat(libPath, System.mapLibraryName("wind"))
        println(s"Try to load native wind library from ${libName}")
        System.loadLibrary(libName)
        useNative = true
      } catch {
        case ex: Exception => {
          ex.printStackTrace()
          useNative = false
        }
      }
    }
  }

  def solveWindField(grids: AnyRef, sonde: AnyRef) = {

  }

  // Calculate terminal velocity based on reflectivity
  def terminalVelocity(grids: Array[Array[Array[Double]]], smooth: Boolean): Array[Array[Array[Double]]] = {

    // There should not be any case temperature below 0C in summer
    def liquid(M: Double, Z: Double) = {
      -5.94 * math.pow(M, 1.0 / 8.0) * math.exp(Z / 20000.0)
    }
    def ice(M: Double, Z: Double) = {
      -1.15 * math.pow(M, 1.0 / 12.0) * math.exp(Z / 20000.0)
    }

    def x = grids.length
    def y = grids(0).length
    def z = grids(0)(0).length

    val result = Array.ofDim[Double](x, y, z)

    for (i <- 0 to x - 1) {
      for (j <- 0 to y - 1) {
        for (k <- 0 to z - 1) {
          result(i)(j)(k) =
            liquid(math.exp((grids(i)(j)(k) - 43.1) / 7.6), k * SiteConf.SpatialResolution("X") + SiteConf.SpatialExtend("Z")._1)
        }
      }
    }

    if (smooth) {
      // Apply gaussian filter here for terminal velocity

    }

    result
  }

  def solve_wind_field(grids: AnyRef, initialGuess: AnyRef = null, target:AnyRef = null, lengthScale:Double=1.0, firstPass:Boolean=true,
  subBeam:Boolean=false, verbose:Boolean=false) : AnyRef = {
    val grids1 = grids.asInstanceOf[util.HashMap[String, AnyRef]]
    val reflect = grids1.get("Reflectivity").asInstanceOf[Array[Array[Array[Double]]]]
    val dopVelocity = grids1.get("DopplerVelocity").asInstanceOf[Array[Array[Array[Double]]]]


    val x = reflect.length
    val y = reflect(0).length
    val z = reflect(0)(0).length
    val n = x * y * z

    // Here what we need to do.
    // From single radar stage, we have rasterized Doppler velocity, interpolated locally.


    // From first guess, we have X-Y-0 wind grid mosaicked from VAD.
    // With reflectivity, we could calculate terminal velocity, then we could calculate Doppler velocity for each cell
    // in inital guess, then we could calculate error cost

    // We need copy 3D wind to 1D wind for cost function and gradient function.
    val u1dWind = Array.ofDim[Double](n)
    val v1dWind = Array.ofDim[Double](n)
    val w1dWind = Array.ofDim[Double](n)

    // Then with mass equation, we could calculate penalty function from wind grid mosaic.

    // Same for cost function 1st order differential.


    // Now we have a initial status for the optimization.

    // Then we need repeat this step during convex optimization then finally. We hope to have a good result of X-Y-Z
    // with best agreements of radar observed Doppler velocity.






    return null
  }

  loadNativeLibrary()

}

