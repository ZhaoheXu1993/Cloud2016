package input

/**
 * NOAA's National Climatic Data Center
 * NOAA/NESDIS/NCDC
 * 151 Patton Ave, Asheville, NC  28801
 *
 * THIS SOFTWARE AND ITS DOCUMENTATION ARE CONSIDERED TO BE IN THE
 * PUBLIC DOMAIN AND THUS ARE AVAILABLE FOR UNRESTRICTED PUBLIC USE.
 * THEY ARE FURNISHED "AS IS." THE AUTHORS, THE UNITED STATES GOVERNMENT, ITS
 * INSTRUMENTALITIES, OFFICERS, EMPLOYEES, AND AGENTS MAKE NO WARRANTY,
 * EXPRESS OR IMPLIED, AS TO THE USEFULNESS OF THE SOFTWARE AND
 * DOCUMENTATION FOR ANY PURPOSE. THEY ASSUME NO RESPONSIBILITY (1)
 * FOR THE USE OF THE SOFTWARE AND DOCUMENTATION; OR (2) TO PROVIDE
 * TECHNICAL SUPPORT TO USERS.
 */
object NexradEquation {

    def getAltitudeFromPressureInMeters(pressureInPa: Double): Double = {
        val pressure_hPa: Double = pressureInPa * 0.01
        val standardPressure_hPa: Double = 1013.25
        val a: Double = Math.log10(pressure_hPa / standardPressure_hPa)
        val b: Double = Math.pow(10, a / 5.2558797) - 1
        val c: Double = b / (-6.8755856 * Math.pow(10, -6))
        c * 0.3048
    }

    /**
     * Uses WSR-88D Range-Height equation on: http://www.wdtb.noaa.gov/courses/dloc/topic3/lesson1/Section5/Section5-4.html
     * with default index of refraction of 1.21 .
     * @param elevAngleInDegrees
     * @param range
     * @return
     */
    def getRelativeBeamHeight(elevAngleInDegrees: Double, range: Double): Double =
      getRelativeBeamHeight(Math.cos(elevAngleInDegrees), Math.sin(elevAngleInDegrees), range, 1.21)

    /**
     * Uses WSR-88D Range-Height equation on: http://www.wdtb.noaa.gov/courses/dloc/topic3/lesson1/Section5/Section5-4.html
     * with custom index of refraction.
     * @param elevAngleRadiansCos
     * @param elevAngleRadiansSin
     * @param range
     * @param refractiveIndex
     * @return
     */
    def getRelativeBeamHeight(elevAngleRadiansCos: Double, elevAngleRadiansSin: Double, range: Double, refractiveIndex: Double): Double = {
        val slantRange: Double = range
        val earthRadius: Double = 6371000
        slantRange * elevAngleRadiansSin + (Math.pow(slantRange, 2) / (2 * refractiveIndex * earthRadius))
    }

    def getRelativeBeamHeight2(elevAngleCos: Double, elevAngleSin: Double, range: Double): Double = {
        val slantRange: Double = range
        val refractionCoef: Double = 4.0 / 3.0
        val earthRadius: Double = 6371000
        Math.sqrt(Math.pow(slantRange, 2) + Math.pow(refractionCoef * earthRadius, 2) + 2 * slantRange * refractionCoef * earthRadius * elevAngleSin) - (refractionCoef * earthRadius) + 0
    }
}