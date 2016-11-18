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

import numexpr

import netCDF4
from netCDF4 import Dataset, num2date

from typing import List, Dict, Tuple


@jit(nopython=True)
def find_elevation_index(vcp_mode, e):
    j = 0
    for i in vcp_mode:
        if -0.2 < e - i < 0.2:
            return j
        j += 1

@jit(nopython=True)
def fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
    r = gate_array[:size_y, :]
    a = azimuth_array[:size_y]
    # Determine azimuthal resolution
    ad = a[1:] - a[:-1]
    # This is a slow way to determine if it is truly high resolution.
    # Well, maybe not necessary as we patched netcdf jar.
    # TODO: Remove this, only relies on "_HI" or not.
    az_downscale = round(numpy.mean(ad[ad > 0]),1) > 0.7
    # As long as it is not legacy, we expand it to 720
    # Then we fill the shape
    if az_downscale:
        for k in range(r.shape[0]):
            az_index = int(a[k] * 2)
            dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
            dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
    else:
        for k in range(r.shape[0]):
            az_index = int(a[k] * 2)
            dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
    pass


def fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
    r = gate_array[:size_y, :]
    a = azimuth_array[:size_y]
    # Determine azimuthal resolution
    ad = numpy.ediff1d(a)
    # This is a slow way to determine if it is truly high resolution.
    # Well, maybe not necessary as we patched netcdf jar.
    # TODO: Remove this, only relies on "_HI" or not.
    az_downscale = round(numpy.mean(ad[ad > 0])) > 0.7
    # As long as it is not legacy, we expand it to 720
    # Then we fill the shape
    if az_downscale:
        for k in range(r.shape[0]):
            az_index = int(a[k] * 2)
            dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]
            dump_array[elevation_index, (az_index + 1) % size_y, :] = r[k, :size_z]
    else:
        for k in range(r.shape[0]):
            az_index = int(a[k] * 2)
            dump_array[elevation_index, az_index % size_y, :] = r[k, :size_z]

def fill_data_function(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z):
    try:
        fill_data_jit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)
    except:
        logging.warning("Failed to run JIT functions")
        fill_data_nojit(gate_array, azimuth_array, dump_array, elevation_index, size_y, size_z)


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

    all_var_suffix = list("RVVDCP")
    ref_var_suffix = list("RDCP")
    vel_var_suffix = list("VV")

    def __init__(self, dataset: Dataset, legacy: bool = False, dualpol: bool = True):

        self.dataset = dataset
        self.legacy_mode = legacy
        self.dualpol = dualpol

        self.vcp_mode = self.VcpTable[self.dataset.VolumeCoveragePattern]

        logging.info(self.vcp_mode)

        self.beams_count = 360 if self.legacy_mode else 720
        self.gates_count = 230 if self.legacy_mode else 920
        self.array_shape = (len(self.vcp_mode), self.beams_count, self.gates_count)

        # Copy entire data from netCDF file to memory
        self.data_dict = {
            "Reflectivity": numpy.empty(self.array_shape, dtype='f4'),
            "RadialVelocity": numpy.empty(self.array_shape, dtype='f4'),
            "SpectrumWidth": numpy.empty(self.array_shape, dtype='f4'),
            "DifferentialReflectivity": numpy.empty(self.array_shape, dtype='f4'),
            "CorrelationCoefficient": numpy.empty(self.array_shape, dtype='f4'),
            "DifferentialPhase": numpy.empty(self.array_shape, dtype='f4')
        }  # type: Dict[str, numpy.ndarray]
        # Fill data
        for p in self.data_dict.values():
            p.fill(-99990.0)

        self.extended_data_dict = {
            "EchoTop5Z": numpy.empty(self.array_shape, dtype='f4'),
            "EchoTop10Z": numpy.empty(self.array_shape, dtype='f4'),
            "EchoTop20Z": numpy.empty(self.array_shape, dtype='f4'),
            "Reflectivity_Avg3x3": numpy.empty(self.array_shape, dtype='f4'),
            "Reflectivity_Std3x3": numpy.empty(self.array_shape, dtype='f4'),
            "Reflectivity_Avg1x5": numpy.empty(self.array_shape, dtype='f4'),
            "Reflectivity_Std1x5": numpy.empty(self.array_shape, dtype='f4'),
            "DifferentialReflectivity_": numpy.empty(self.array_shape, dtype='f4'),
            ""
        }



        # Filling status, ensure everything is filled!
        self.filling_table = numpy.zeros((len(self.vcp_mode), len(self.data_dict)), dtype='b1')

        self.time_data_dict = OrderedDict()  # type: Dict[int, Dict[str, numpy.ma.MaskedArray]
        self.dump_data_by_time(self.all_var_names, self.time_data_dict)
        self.dump_data_by_time(["elevation" + p for p in self.all_var_suffix], self.time_data_dict)
        self.dump_data_by_time(["azimuth" + p for p in self.all_var_suffix], self.time_data_dict)

        self.fill_data(first_pass=True)

    def is_filled(self):
        # All filled means all is True
        return numpy.all(numpy.logical_not(self.filling_table))  # type: bool

    # Dump helper function
    def __dump(self, var, time_var, dump_dict):
        if time_var not in ds.variables or var not in ds.variables:
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

    @jit
    def __fill_data_internal(self, i, id_var, var_names, var_suffix):
        mode = "_HI" if id_var + "_HI" in i else ""
        elevation = i[id_var + mode].mean()
        elevation_index = find_elevation_index(self.vcp_mode, elevation)
        logging.info("%f - %d" % (elevation, elevation_index))
        for j, s in zip(var_names, var_suffix):
            logging.debug("Dumping variable: %s - %s" % (j, s))
            fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
                               self.beams_count, self.gates_count)

    def fill_data(self, *args, **kwargs):

        for i in self.time_data_dict.values():
            # There are several cases:
            # Case 1: CS case, only reflectivity related variable will be here
            if 'elevationV' not in i and 'elevationV_HI' not in i:
                try:
                    self.__fill_data_internal(i, "elevationR", self.ref_var_names, self.ref_var_suffix)
                except:
                    logging.warning("Failed to run JITed fill_data function: CS")
                    mode = "_HI" if 'elevationR_HI' in i else ""
                    elevation = i["elevationR" + mode].mean()
                    elevation_index = find_elevation_index(self.vcp_mode, elevation)
                    logging.info("%f - %d" % (elevation, elevation_index))
                    for j, s in zip(self.ref_var_names, self.ref_var_suffix):
                        logging.debug("Dumping variable: %s - %s" % (j, s))
                        fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
                                        self.beams_count, self.gates_count)
                        pass
            # CD pulses: we only use Doppler Velocity
            elif (('elevationV' in i or 'elevationV_HI' in i) and ('elevationR' not in i and 'elevationR_HI' not in i)) \
                    or (('elevationV' in i or 'elevationV_HI' in i) and
                            ('elevationR' in i or 'elevationR_HI' in i) and
                            ('DifferentialReflectivity' not in i and 'DifferentialReflectivity' not in i)
                        ):
                try:
                    self.__fill_data_internal(i, "elevationV", self.vel_var_names, self.vel_var_suffix)
                except:
                    logging.warning("Failed to run JITed fill_data function: CD")
                    mode = "_HI" if 'elevationV_HI' in i else ""
                    elevation = i["elevationV" + mode].mean()
                    elevation_index = find_elevation_index(self.vcp_mode, elevation)
                    logging.info("%f - %d" % (elevation, elevation_index))
                    for j, s in zip(self.vel_var_names, self.vel_var_suffix):
                        logging.debug("Dumping variable: %s - %s" % (j, s))
                        fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
                                        self.beams_count, self.gates_count)
                        pass
            # Normal case, all variables will be gathered in one scan
            else:
                try:
                    self.__fill_data_internal(i, "elevationR", self.all_var_names, self.all_var_suffix)
                except:
                    logging.warning("Failed to run JITed fill_data function: Mixed")
                    mode = "_HI" if 'elevationR_HI' in i else ""
                    elevation = i["elevationR" + mode].mean()
                    elevation_index = find_elevation_index(self.vcp_mode, elevation)
                    logging.info("%f - %d" % (elevation, elevation_index))
                    for j, s in zip(self.all_var_names, self.all_var_suffix):
                        logging.debug("Dumping variable: %s - %s" % (j, s))
                        fill_data_function(i[j + mode], i["azimuth" + s + mode], self.data_dict[j], elevation_index,
                                        self.beams_count, self.gates_count)
                        pass
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
        for point, attr in coordinate.items():
            f.write(str(point))
            f.write(' ')
            for variable, value in attr.items():
                f.write(variable)
                f.write(':')
                f.write(str(value))
                f.write(' ')
            f.write('\n')
        f.close()
        print("finish output")


if __name__ == "__main__":
    ds = Dataset('/home/sugar/Developer/Cloud2016/KTLH20160902_000332_V06.nc', 'r')
    R = RadarNetcdf(ds)
