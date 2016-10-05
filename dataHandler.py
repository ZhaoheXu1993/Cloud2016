from netCDF4 import Dataset, num2date
from datetime import datetime
import time

vcp_dict = {11: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
            211: (0.5, 1.5, 2.4, 3.4, 4.3, 5.3, 6.2, 7.5, 8.7, 10.0, 12.0, 14.0, 16.7, 19.5),
            12: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
            212: (0.5, 0.9, 1.3, 1.8, 2.4, 3.1, 4.0, 5.1, 6.4, 8.0, 10.0, 12.5, 15.6, 19.5),
            21: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
            121: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5),
            221: (0.5, 1.5, 2.4, 3.4, 4.3, 6.0, 9.9, 14.6, 19.5)}


def combine_scanV_HI(data_set):
    if not data_set.dimensions['scanV_HI'] or data_set.dimensions['scanV_HI'].size <= 0:
        return





def preprocess_data(data_set):
    combine_scanV_HI(data_set)
    return


def invalid_data(data_set, scan, radial, gate):
    return data_set.variables['Reflectivity'][scan][radial].mask[gate] or \
           data_set.variables['RadialVelocity'][scan][radial].mask[gate] or \
           data_set.variables['DifferentialReflectivity'][scan][radial].mask[gate] or \
           data_set.variables['SpectrumWidth'][scan][radial].mask[gate] or \
           data_set.variables['CorrelationCoefficient'][scan][radial].mask[gate] or \
           data_set.variables['DifferentialPhase'][scan][radial].mask[gate]


def main(file_path):
    data_set = Dataset(file_path)

    elevation_set = vcp_dict[data_set.VolumeCoveragePattern]
    time_units = "milli" + data_set.variables['timeR'].units[1:]

    preprocess_data(data_set)

    coordinates = {}

    for scan in range(len(data_set.dimensions['scanR'])):
        for radial in range(len(data_set.dimensions['radialR'])):
            for gate in range(len(data_set.dimensions['gateR'])):
                if invalid_data(data_set, scan, radial, gate):
                    continue

                time = data_set.variables['timeR'][scan][radial]
                elevation = data_set.variables['elevationR'][scan][radial]
                azimuth = data_set.variables['azimuthR'][scan][radial]
                distance = data_set.variables['distanceR'][gate]

                point = (avg_time, avg_elevation, avg_azimuth, avg_distance)

                if point not in coordinates:
                    coordinates[point] = {"Reflectivity": data_set.variables['Reflectivity'][scan][radial][gate],
                                          "RadialVelocity": data_set.variables['RadialVelocity'][scan][radial][gate],
                                          "DifferentialReflectivity": data_set.variables['DifferentialReflectivity'][scan][radial][gate],
                                          "SpectrumWidth": data_set.variables['SpectrumWidth'][scan][radial][gate],
                                          "CorrelationCoefficient": data_set.variables['CorrelationCoefficient'][scan][radial][gate],
                                          "DifferentialPhase": data_set.variables['DifferentialPhase'][scan][radial][gate]}

                    print point, coordinates[point]




if __name__ == '__main__':
    file_path = "/home/joexu/KDOX20121029_024440_V07.nc";
    main(file_path)