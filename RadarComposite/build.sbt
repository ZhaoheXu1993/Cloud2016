name := "RadarMapper"

version := "1.0"

scalaVersion := "2.10.5"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % "1.2.2",
  "com.github.nscala-time" %% "nscala-time" % "2.0.0",
  "org.apache.spark" %% "spark-mllib" % "1.2.2",
  // "org.scalanlp" %% "breeze" % "0.11.2",
  // "org.scalanlp" %% "breeze-natives" % "0.11.2",
  // It is very strange but sbt didn't resolve edu.ucar:cdm, cause unresolvable reference to ucar.ma2
  "edu.ucar" % "cdm" % "4.5.5",
  "edu.ucar" % "netcdf4" % "4.5.5",
  "gov.nist.math.jama" % "gov.nist.math.jama" % "1.1.1",
  "com.fasterxml.jackson.module" %% "jackson-module-scala" % "2.4.1",
  "org.codehaus.jettison" % "jettison" % "1.3.7",
  "org.scalatra" %% "scalatra-scalatest" % "2.0.5" % Test,
  "com.github.wendykierp" % "JTransforms" % "3.0",
  "com.amazonaws" % "aws-java-sdk" % "1.10.30"
)

resolvers ++= Seq(
  // other resolvers here
  "Sonatype Releases" at "https://oss.sonatype.org/content/repositories/releases/"
)

lazy val arcgis = ProjectRef(file("../GisComponents"), "giscomponents")

val radar = Project(id = "radarcomposite", base = file(".")).dependsOn(arcgis)
