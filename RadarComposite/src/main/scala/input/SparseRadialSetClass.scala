package input

import java.util.HashMap

class SparseRadialSetClass {

  var sizeX: Int = 0
  var sizeY: Int = 0
  var pixels: Int = 0
  var dimensionXVariable: Array[Double] = null
  var dimensionYVariable: Array[Double] = null
  var encodedValues: Array[Double] = null
  var decodedValues: Array[Array[Double]] = null
  private var pixel_x: Array[Int] = null
  private var pixel_y: Array[Int] = null
  private var pixel_count: Array[Int] = null

  def setPixelX(pixel_x: Array[Int]) {
    this.pixel_x = pixel_x
  }

  def setPixelY(pixel_y: Array[Int]) {
    this.pixel_y = pixel_y
  }

  def setPixelCount(pixel_count: Array[Int]) {
    this.pixel_count = pixel_count
  }

  def setEncodedValues(values: Array[Double]) {
    this.encodedValues = values
  }

  def setDimensionXVariable(dimensionXVariable: Array[Double]) {
    this.dimensionXVariable = dimensionXVariable
  }

  def setDimensionYVariable(dimensionYVariable: Array[Double]) {
    this.dimensionYVariable = dimensionYVariable
  }

  def setSize(X: Int, Y: Int) {
    this.sizeX = X
    this.sizeY = Y
    this.decodedValues = Array.ofDim[Double](X,Y)
  }

  def decodeSet(): Boolean = {
    try {
      for (i <- 0 to this.encodedValues.length - 1) {
        val c: Int = this.pixel_count(i)
        var X: Int = this.pixel_x(i)
        var Y: Int = this.pixel_y(i)
        for (j <- 0 to c - 1) {
          this.decodedValues(X)(Y) = this.encodedValues(i)
          Y += 1
          if (Y >= sizeY) {
            Y = 0
            X += 1
          }
        }
      }
      return true
    }
    catch {
      case ex: Exception =>
        ex.printStackTrace()
    }
    false
  }
}