# coding=utf-8
import time
from datetime import datetime, timedelta

from numba import jit
from sortedcontainers import SortedDict as OrderedDict

from functools import reduce

import logging
logging.basicConfig(level=logging.DEBUG)

import json

from pprint import pprint as pp

import numpy
import numpy.ma

import netCDF4
from netCDF4 import Dataset, num2date

from typing import List, Dict, Tuple


@jit
def find_elevation_index(vcp_mode, e):
    for i in vcp_mode:
        if -0.2 < e - i < 0.2:
            return i

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

    all_var_names = ["Reflectivity",
                     "RadialVelocity", "SpectrumWidth",
                     "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
    ref_var_names = ["Reflectivity", "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"]
    vel_var_names = ["RadialVelocity", "SpectrumWidth"]

    all_var_suffix = list("RVSDCP")
    ref_var_suffix = list("RDCP")
    vel_var_suffix = list("VS")


    def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):

        self.dataset = dataset
        self.vcp_mode = self.VcpTable[self.dataset.VolumeCoveragePattern]

        logging.info(self.vcp_mode)
        self.array_shape = (len(self.vcp_mode), 360, 230) if legacy else (len(self.vcp_mode), 720, 920)
        self.legacy_mode = legacy
        self.dualpol = dualpol



        # Copy entire data from netCDF file to memory
        self.data_dict = {
            "Reflectivity": numpy.zeros(self.array_shape, dtype='f4'),
            "RadialVelocity": numpy.zeros(self.array_shape, dtype='f4'),
            "SpectrumWidth": numpy.zeros(self.array_shape, dtype='f4'),
            "DifferentialReflectivity": numpy.zeros(self.array_shape, dtype='f4'),
            "CorrelationCoefficient": numpy.zeros(self.array_shape, dtype='f4'),
            "DifferentialPhase": numpy.zeros(self.array_shape, dtype='f4')
        }  # type: Dict[str, numpy.ndarray]

        self.time_data_dict = OrderedDict()  # type: Dict[int, Dict[str, numpy.ma.MaskedArray]
        self.dump_data_by_time(self.all_var_names, self.time_data_dict)
        self.dump_data_by_time(["elevation" + p for p in self.all_var_suffix], self.time_data_dict)

        self.fill_data()

    # Dump helper function
    def __dump(self, var, time_var, dump_dict):
        if not time_var in ds.variables or not var in ds.variables:
            return
        time_var_dump = ds.variables[time_var][:]
        var_dump = self.__fix_variable__(self.dataset.variables[var])
        assert time_var_dump.min(axis=1).data == time_var_dump[:, 0].data
        scan_start_time = time_var_dump.min(axis=1)
        for t in range(scan_start_time.shape[0]):
            logging.debug("%s - %d - %d" % (var, t, scan_start_time[t]))
            try:
                dump_dict[scan_start_time[t]][var] = var_dump[t]
            except KeyError:
                dump_dict[scan_start_time[t]] = OrderedDict({var: var_dump[t]})

    def dump_data_by_time(self, dump_var_names, dump_target):
        assert len(dump_var_names) == len(self.all_var_suffix)
        for i in range(len(dump_var_names)):
            # Dump general variables
            var = dump_var_names[i]
            time_var = "time" + self.all_var_suffix[i]
            self.__dump(var, time_var, dump_target)
            # Dump high_resolution variables
            var_hi = var + "_HI"
            time_var_hi = time_var + "_HI"
            self.__dump(var_hi, time_var_hi, dump_target)

    @staticmethod
    def __fix_variable__(v: netCDF4.Variable) -> numpy.ma.MaskedArray:
        """Fix wrong unsigned value"""
        if 'add_offset' in v.__dict__ and 'scale_factor' in v.__dict__ and v._Unsigned:
            v.set_auto_scale(False)
            # Dump out
            _v = v[:]
            _v1 = _v.data.view('u' + str(v.datatype)) * v.scale_factor + v.add_offset
            logging.info("Fix unsigned variable:" + v.name)
            return numpy.ma.MaskedArray(_v1, _v.mask)
        else:
            return v[:]

    def first_pass(self):
        pass



    def fill_data(self):
        for i in self.time_data_dict.values():
            # There are several cases:
            # Case 1: CS case, only reflectivity related variable will be here
            if not 'elevationV' in i and not 'elevationV_HI' in i:
                mode = "_HI" if 'elevationR_HI' in i else ""
                elevation = i["elevationR" + mode].mean()
                elevation_index = find_elevation_index(self.vcp_mode, elevation)
                logging.debug("%f - %d" % (elevation, elevation_index))
                # Case 2: Normal case, all variables will be here.

                #

        pass

    def mask_data(self):
        # Create a mask to remove all invalid data from reflectivity scan.
        total_mask = reduce(numpy.ma.logical_or,
                            tuple([v.mask for k, v in self.data_dict]))
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
