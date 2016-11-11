# coding=utf-8
# TODO: create an abstract interface for it
# TODO: General abstract design VCP => Clear/Rain => VCP_SAIL/VCP_NOSAIL => VCP

from enum import Enum

from typing import List, Tuple, Dict

from collections import OrderedDict

from sortedcontainers import SortedDict

import numpy

import netCDF4
from netCDF4 import Dataset


class BeamScanMode(Enum):
    R = 0b0001  # 1 - Reflectivity
    V = 0b0010  # 2 - Velocity
    S = 0b0100  # 4 - SAILS Scan


class VcpMode(object):
    pass


class VcpRain(VcpMode):
    pass


class Vcp212(VcpRain):
    ScanTable = (0.5, 0.5, 0.9, 0.9, 1.3, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5)
    ScanVariable = (1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)

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

    def __init__(self, dataset: Dataset):

        self.dataset = dataset
        self.variable_list = "Reflectivity", "RadialVelocity", "SpectrumWidth", \
                             "DifferentialReflectivity", "CorrelationCoefficient", "DifferentialPhase"
        self.variable_list_HI = map(lambda p: p + "_HI", self.variable_list)  # Append high resolution variables
        self.suffix = list("RVSDCP")
        self.time_vars = ["time" + p for p in self.suffix]
        self.time_vars_HI = [p + "_HI" for p in self.time_vars]
        self.elevation_vars = self.time_vars = ["elevation" + p for p in self.suffix]
        self.elevation_vars_HI = [p + "_HI" for p in self.elevation_vars]

        # Dump data variables
        self.data_dict = {p: dataset.variables[p] if p in dataset.variables else None for p in
                          self.variable_list}  # type: Dict[str, numpy.ma.MaskedArray]
        self.data_dict += {p: dataset.variables[p] if p in dataset.variables else None for p in
                           self.variable_list_HI}  # type: Dict[str, numpy.ma.MaskedArray]

        self.data_by_time = SortedDict()
        self.elevation_by_time = SortedDict()

        for k, v in self.dataset.variables.iteritems():
            # NOTE: Make corrections if we observe things
            self.data_dict[k] = self.__fix_variable__(v)
        # Output dictionary is contains K-V pairs to write in text format.
        self.output_dict = {}

        self.is_dualpol = self.data_dict["DifferentialReflectivity"] is not None \
                          or self.data_dict["DifferentialReflectivity_HI"] is not None

        self.order_data()

    def tag_elevation(self):
        # First, all SAILS elevation is at 0.5, we can assume, it is definitely less than 0.7
        self.is_sails = numpy.zeros_like(self.normalized_elevation)
        j = 0
        for i in range(0, self.normalized_elevation.shape[0]):
            if abs(self.normalized_elevation[i] - self.ScanTable[j]) <= 0.1:  # Just in case, rounded value is wrong, maximum error would be 0.1
                self.is_sails[i] = 0
                j += 1
            else:
                self.is_sails[i] = 1

    def link_data_to_time(self):
        if self.sorted_timeR.shape == self.sorted_timeV.shape:
            # Means there is no reflectivity scan for CD scan
            pass
        else:
            for t in self.time_vars:
                if t not in self.dataset.variables:
                    continue
                time_value = self.dataset.variables[t][:].min(axis=1)
                for i in list(time_value):
                    self.data_by_time[i] = self.data_dict['Reflectivity'][i]
                    self.elevation_by_time[i] = self.data_by_time['elevationR'][i].mean().round(1)

            pass


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

    def order_data(self):
        """Restore the order of data, by scanning start time."""
        # Scan start time at each elevation.
        ds = self.dataset
        start_timeR = ds.variables['timeR'][:].min(axis=1)
        # If there is high resolution data, merge it
        start_timeR_HI = ds.variables['timeR_HI'][:].min(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
        timeR_sort = numpy.concatenate((start_timeR, start_timeR_HI)).argsort()
        self.ref_sort_order = timeR_sort
        self.sorted_timeR = numpy.concatenate((start_timeR, start_timeR_HI)).sort()

        # ElevationR
        elevationR = ds.variables['elevationR'][:].mean(axis=1)
        elevationR_HI = ds.variables['elevationR_HI'][:].mean(axis=1)  # if "Reflectivity_HI" in self.data_dict_hi else []
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

        if timeR_sort.shape[0] != timeV_sort.shape[0]:
            # We need mask CD from elevationR
            rm = numpy.ediff1d(self.normalized_elevation)
            self.normalized_elevation.mask[1:] = rm == 0
