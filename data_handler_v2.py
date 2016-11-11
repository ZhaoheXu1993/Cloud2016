# coding=utf-8
import time
from datetime import datetime, timedelta

from sortedcontainers import SortedDict as OrderedDict

from functools import reduce

import json

from pprint import pprint as pp

import numpy
import numpy.ma

import netCDF4
from netCDF4 import Dataset, num2date

from typing import List, Dict, Tuple


class RadarNetcdf(object):
    VcpTable = {
        11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
        211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
        12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
        212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
        21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
        121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
        221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)
    }

    var_names = ["Reflectivity", "RadialVelocity", "SpectrumWidth",
                 "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
    var_suffix = list("RVSDCP")

    velocity_var_list = {"RadialVelocity", "SpectrumWidth", "RadialVelocity_HI", "SpectrumWidth_HI"}

    ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)
    ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)

    def __init__(self, dataset: Dataset, legacy: bool = False):
        """
        :dataset: an opened object of `netCDF4.Dataset`
        """
        self.dataset = dataset
        self.vcp_mode = self.VcpTable[self.dataset.VolumeCoveragePattern]
        self.array_shape = (len(self.vcp_mode), 360, 230) if legacy else (len(self.vcp_mode), 720, 920)
        self.legacy_mode = legacy

        # Copy entire data from netCDF file to memory
        self.data_dict = {
            "Reflectivity": numpy.zeros(self.array_shape, dtype='f4'),
            "RadialVelocity": numpy.zeros(self.array_shape, dtype='f4'),
            "SpectrumWidth": numpy.zeros(self.array_shape, dtype='f4'),
            "DifferentialReflectivity": numpy.zeros(self.array_shape, dtype='f4'),
            "CorrelationCoefficient": numpy.zeros(self.array_shape, dtype='f4'),
            "DifferentialPhase": numpy.zeros(self.array_shape, dtype='f4')
        }  # type: Dict[str, numpy.ndarray]

        self.time_data_dict = OrderedDict()
        self.dump_data_by_time(self.var_names, self.time_data_dict)
        self.dump_data_by_time(["elevation" + p for p in self.var_suffix], self.time_data_dict)

    def dump_data_by_time(self, dump_var_names, dump_target):

        # Dump helper function
        def __dump(var, time_var, dump_dict):
            if not time_var in ds.variables or not var in ds.variables:
                return
            time_var_dump = ds.variables[time_var][:]
            var_dump = ds.variables[var][:]
            assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
            scan_start_time = time_var_dump.min(axis=1)
            for t in range(scan_start_time.shape[0]):
                print(var, t, scan_start_time[t])
                try:
                    dump_dict[scan_start_time[t]][var] = var_dump[t]
                except KeyError:
                    dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})

        assert len(dump_var_names) == len(self.var_suffix)

        for i in range(len(dump_var_names)):
            # Dump general variables
            var = dump_var_names[i]
            time_var = "time" + self.var_suffix[i]
            __dump(var, time_var, dump_target)
            # Dump high_resolution variables
            var_hi = var + "_HI"
            time_var_hi = time_var + "_HI"
            __dump(var_hi, time_var_hi, dump_target)

    def order_data(self):
        """Restore the order of data, by scanning start time."""
        # Scan start time at each elevation.
        ds = self.dataset
        start_timeR = ds.variables['timeR'][:].min(axis=1)
        # If there is high resolution data, merge it
        start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1) if "Reflectivity_HI" in ds.variables else []
        timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()
        self.ref_sort_order = timeR_sort
        self.sorted_timeR = numpy.concatenate((start_timeR, start_timeR_HI)).sort()

        # ElevationR
        elevationR = ds.variables['elevationR'][:].mean(axis=1)
        elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1) if "Reflectivity_HI" in ds.variables else []
        all_elevationR = numpy.concatenate((elevationR, elevationR_HI))
        sorted_elevationR = all_elevationR[timeR_sort]

        # Once we get sorted elevation, we should extract SAILS elevations.
        # Problem is, how can we deal with these elevations
        self.normalized_elevation = sorted_elevationR.round(1)  # type: numpy.ma.MaskedArray

        # Then we check if elevationV is all included in elevationR.
        # If true, means CD contains reflectivity data, we need drop them, if false, we merge velocity data
        start_timeV = ds.variables['timeV'][:].min(axis=1)
        start_timeV_HI = ds.variables['timeV_HI'][:].min(axis=1)
        timeV_sort = numpy.concatenate((start_timeV, start_timeV_HI)).argsort()
        self.vel_sort_order = timeV_sort
        self.sorted_timeV = numpy.concatenate((start_timeV, start_timeV_HI)).sort()

    def tag_elevation(self):
        # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
        self.is_sails = numpy.zeros_like(self.normalized_elevation)
        j = 0
        for i in range(0, self.normalized_elevation.shape[0]):
            # Just in case, rounded value is wrong, maximum error would be ~0.1
            if abs(self.normalized_elevation[i] - self.ScanTable[j]) < 0.2:
                self.is_sails[i] = 0
                j += 1
            else:
                self.is_sails[i] = 1

    @staticmethod
    def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
        """Fix wrong unsigned value"""
        if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
            v.set_auto_scale(False)
            # Dump out
            _v = v[:]
            _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
            return numpy.ma.MaskedArray(_v1, _v.mask)
        else:
            return v[:]

    def mask_data(self):
        # Create a mask to remove all invalid data from reflectivity scan.
        total_mask = reduce(numpy.ma.logical_or,
                            tuple([v.mask for k, v in self.data_dict if k not in velocity_var_list]))
        # Update mask
        for v in self.data_dict.values():
            v.mask = total_mask

    def output2file(self, path, coordinate):
        print("start output...")
        f = open(path, 'w')
        for point, attri in coordinate.items():
            f.write(str(point))
            f.write(' ')
            for variable, value in attri.items():
                f.write(variable)
                f.write(':')
                f.write(str(value))
                f.write(' ')
            f.write('\n')
        f.close()
        print("finish output")


if __name__ == "__main__":
    ds = Dataset('/home/sugar/Developer/Cloud2016/KDOX20121029_002042_V07.nc', 'r')
    R = RadarNetcdf(ds)
