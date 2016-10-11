import time
from datetime import datetime

import numpy
import numpy.ma

from netCDF4 import Dataset, num2date

vcp_dict = {11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
            211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
            12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
            212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
            21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
            121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
            221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)}

radial_dimension_var = {"Reflectivity": "AzimuthR",
                        "RadialVelocity": "AzimuthV",
                        "SpectrumWidth": "AzimuthV",
                        "DifferentialReflectivity": "AzimuthD",                                
                        "CorrelationCoefficient": "AzimuthC",
                        "DifferentialPhase_HI": "AzimuthP"}

hi_radial_dimension_var = { k + "_HI": v + "_HI" for k, v in radial_dimension_var.iteritems() }

class RadarNetcdf(object):
    
    def __init__(self, dataset):
        """
        :dataset: an opened object of `netCDF4.Dataset`
        """
        self.dataset = dataset
        
        
    def sanity_check(self, dataset):
        """Check if this Level-II CF file is sane. Here are some strange examples:
1. Varname_HI has azimuthal resolution of 1.0 deg or bin size of 1000 m
2. Radial dimension is not 360 or 720
3. Dimensions across variables are inconsistent."""
        # Check problem 1

        hi_res_vars = filter(lambda p: p.endswith("_HI"), dataset.variables.keys())
        for h in hi_res_vars:
            var_azimuth = self.dataset.variables[hi_res_radial_dimension_var[h.replace()]]
            
        pass    
    
    def output2file(path, coordinate):
        print "start output..."    
        f = open(path, 'w')    
        for point, attri in coordinate.iteritems():
            f.write(str(point))
            f.write(' ')
            for variable, value in attri.iteritems():
                f.write(variable)
                f.write(':')
                f.write(str(value))
                f.write(' ')
            f.write('\n')    
        f.close()    
        print "finish output"
        

 