# coding=utf-8

import os
import re
from datetime import datetime

from typing import Dict, Tuple, List

import numpy
import scipy
from numba import jit

import netCDF4

class Labeler():
    
    def __init__(self, dataset_path: str, qc_dataset_path: str, elevation: float):
        
        self.dataset_path = dataset_path
        self.qc_dataset_path = dataset_path
        
        self.dataset = netCDF4.Dataset(self.dataset_path) # type: netCDF4.Datset
        self.dataset_qc = netCDF4.Dataset(self.qc_dataset_path) # type: netCDF4.Dataset

        # Get Time for (T, *, *, *)
        self.data_time = self.analysis_time()
        # Get Elevation for (*, e, *, *)
        self.elevation = elevation

        self.decode_sparse_set()

        
    def analysis_time(self) -> datetime:
        dataset_time = re.search(r'\d{8}-\d{6}', self.dataset_path).group(0)
        qc_dataset_time = re.search(r'\d{8}-\d{6}', self.qc_dataset_path).group(0)
        assert dataset_time == qc_dataset_time
        return datetime.strptime(dataset_time, "%Y%m%d-%H%M%S")

    def dump_data_to_dict(self):
        refl = self.dataset.variables['Reflectivity'][:] if self.dataset.DataType == 'RadialSet' else self.decode_sparse_set(self.dataset)
        refl_qc = self.dataset_qc.variables['ReflectivityQC'][:] if self.dataset.DataType == 'RadialSet' else self.decode_sparse_set(self.dataset_qc)
        self.data_dict = {
            'Azimuth': self.dataset.variables['Azimuth'][:],
            'Gate': numpy.cumsum(self.dataset.variables['GateWidth']),
            'Reflectivity': refl,
            'ReflectivityQC': refl_qc,
        } # type: Dict[str, numpy.ndarray]

    @staticmethod
    @jit
    def decode_sparse_set(dataset: netCDF4.Dataset) -> numpy.ndarray:
        var_name = dataset.TypeName
        row_count = len(dataset.dimensions['Azimuth'])
        col_count = len(dataset.dimensions['Gate'])
        pixel_x = dataset.variables['pixel_x']
        pixel_y = dataset.variables['pixel_y']
        pixel_c = dataset.variables['pixel_count']
        reflect = dataset.variables[var_name]
        # Decode the run-length encoding
        reflect_array = numpy.zeros((row_count, col_count))
        # Should be shifted by numba
        for i in range(len(pixel_x)):
            startx = pixel_x[i]
            starty = pixel_y[i]
            for j in range(pixel_c[i]):
                reflect_array[pixel_x[i], pixel_y[i]] = reflect[i]
                starty += 1
                if starty == col_count:
                    startx += 1
                    starty = 0
        return reflect_array






