# Radar Composite: a scalable framework for digesting and analyzing WSR-88D radar data

[![Build Status](https://travis-ci.org/striges/RadarComposite.svg?branch=master)](https://travis-ci.org/striges/RadarComposite)

New Python version is coming!

## Highlights:
* Big Data ready: Apache Spark based parallel engine with Apache Hadoop based storage.
* Cross-platform: run on Windows, Mac and Linux
* Scalable anywhere: from personal PC to High-performance cluster environments (PBS). 
* Plugable interface to accept almost any MapReduce function
* Spatial analysts compatibility: Run geoprocessing scripts without standalone GIS software, and in parallel

License: LGPLv3

We're actively moving this project to completely free-of-use. We're actively removing any components that rely on closed source product.

On-going task:
* Migrating to SBT. <del> Handle Python codes in SBT tasks </del>
* Use streaming API with customized radar data feeding.
* <del>Adopting Py-ART and wradlib to support more data type.</del>
* Providing quality control and data correction.
* <del>3D wind field retrieval.</del>
* Add EVAD and GBVTD to single radar algorithms
* Increase compatibility on Windows platform.
* Decode NEXRAD using netcdf4-java
* <del>Increase GIS compatibility on Linux.</del>
 
**This a data-processing framework, thus there is no visualization in this system. We have no plan to add any visualization function in this framework.**

To load radar data into GIS, please check Radar Toolkit for ArcGIS.

**We're moving code to GitHub as SBT project. Codes may not be complete now. Please go back and check often.**

*You must obtain your own ArcGIS Runtime Developer license (free) to execute geoprocessing function. Due to license restriction, we **only** provide source code.*
*You need ArcGIS Desktop to build geoprocessing package. (Guides will be provided later)*

## Acknowledgements:

Py-ART: https://github.com/ARM-DOE/pyart
wradlib: http://wradlib.bitbucket.org/
WDSS-II: http://www.wdssii.org/
Py-ART forks by Kirk North: https://github.com/kirknorth
