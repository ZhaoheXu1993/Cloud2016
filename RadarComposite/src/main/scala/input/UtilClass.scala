package input

import java.io.File
import java.text.ParseException
import java.text.SimpleDateFormat
import java.util.Date

/**
 * Created with IntelliJ IDEA.
 * User: sugar
 * Date: 7/17/13
 * Time: 1:53 PM
 * To change this template use File | Settings | File Templates.
 */
object UtilClass {

    def ShortArrayToIntArray(input: Array[Short]): Array[Int] = {
        input.map(_.asInstanceOf[Int])
    }

    def FloatArrayToDoubleArray(input: Array[Float]): Array[Double] = {
        input.map(_.asInstanceOf[Double])
    }

    def ExtractDateFromFilePath(input_path: String): Date = {
        val f: File = new File(input_path)
        if (!f.exists) {
            println(input_path + " is not found. It may cause problems afterwards.")
        }
        val filename: String = f.getName
        val format = new SimpleDateFormat("YYYYMMDD-HHmmss")
        format.parse(filename)
    }
}