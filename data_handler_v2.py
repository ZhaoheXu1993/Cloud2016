#conding=utf-8
import time
from datetime import datetime, timedelta

from collections import OrderedDict

import json

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
                        "DifferentialPhase": "AzimuthP"}

hi_radial_dimension_var = { k + "_HI": v + "_HI" for k, v in radial_dimension_var.iteritems() }

#velocity_var_list = set("RadialVelocity", "SpectrumWidth", "RadialVelocity_HI", "SpectrumWidth_HI")
velocity_var_list = set()

class RadarNetcdf(object):

    def __init__(self, dataset):
        """
        :dataset: an opened object of `netCDF4.Dataset`
        """
        self.dataset = dataset
        # Copy entire data from netCDF file to memory
        self.data_dict = {}
        for k, v in dataset.variables.iteritems():
            # NOTE: Make corrections if we observe things
            if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
                v.set_auto_scale(False)
                # Dump out
                _v = v[:]
                _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
                self.data_dict[k] = numpy.ma.MaskedArray(_v1, _v.mask)
            else:
                self.data_dict[k] = v[:]
        # Output dictionary is contains K-V pairs to write in text format.
        self.output_dict = {}
        self.vcp_mode = vcp_dict[self.dataset.VolumeCoveragePattern]


    def sanity_check(self):
        """Check if this Level-II CF file is sane. Here are some strange examples:
1. Varname_HI has azimuthal resolution of 1.0 deg -> merge to normal `varname`
2. Radial size across variables are inconsistent across variables.
3. Gates size across variables are inconsistent across variables;
4. Radial dimension is not 360 or 720 -> ???
"""
        # Check problem 1
        hi_res_vars = filter(lambda p: p.endswith("_HI"), dataset.variables.keys())
        for h in hi_res_vars:
            var_azimuth = self.dataset.variables[hi_res_radial_dimension_var[h.replace()]]
        pass
        # Check problem 2
        pass
        # Check problem 3
        pass
        # Check problem 4
        if False:  # TODO: check problem 4
            raise NotImplementedError("Sanity check 4 not implemented")

    def mask_data(self):
        # Create a mask to remove all invalid data from reflectivity scan.
        total_mask = reduce(numpy.ma.logical_or, tuple([v.mask for k, v in self.data_dict.iteritems if k not in velocity_var_list]))
        # Update mask
        for v in self.data_dict.values():
            v.mask = total_mask

    def match_azimuth(self):
        """If reflectivity and velocity are not scanned at same time, it is possible their azimuth is not match, thus we need sync them"""
        for i in len(self.vcp_mode):
            azR = self.data_dict['azimuthR']


    def dump_to_dict():
        pass


    def output2file(self, path, coordinate):
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


if __name__ == "__main__":
    ds = Dataset('test.nc', 'r')
    R = RadarNetcdf(ds)
    R.sanity_check()

