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


def invalid_data(data_set, scan, radial, gate, is_v):
    if is_v:
        return data_set.variables['Reflectivity'][scan][radial].mask[gate] or \
               data_set.variables['RadialVelocity'][scan][radial].mask[gate] or \
               data_set.variables['DifferentialReflectivity'][scan][radial].mask[gate] or \
               data_set.variables['SpectrumWidth'][scan][radial].mask[gate] or \
               data_set.variables['CorrelationCoefficient'][scan][radial].mask[gate] or \
               data_set.variables['DifferentialPhase'][scan][radial].mask[gate]
    else:
        return data_set.variables['Reflectivity'][scan][radial].mask[gate] or \
               data_set.variables['RadialVelocity_HI'][scan][radial].mask[gate] or \
               data_set.variables['DifferentialReflectivity'][scan][radial].mask[gate] or \
               data_set.variables['SpectrumWidth'][scan][radial].mask[gate] or \
               data_set.variables['CorrelationCoefficient'][scan][radial].mask[gate] or \
               data_set.variables['DifferentialPhase'][scan][radial].mask[gate]


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

    return


def main(input_path, output_path):
    # data from netcdf file
    data_set = Dataset(input_path, "a")

    # get VCR type
    elevation_set = vcp_dict[data_set.VolumeCoveragePattern]

    # get time unit
    time_units = "milli" + data_set.variables['timeR'].units[1:]

    # build a 4-D coordinates
    coordinates = {}

    # data size
    scan_size = len(data_set.dimensions['scanR'])
    radial_size = len(data_set.dimensions['radialR'])
    # gate_size = len(data_set.dimensions['gateR'])

    if scan_size != 9:
        return
    if radial_size < 360 or radial_size > 720:
        return

    # data process
    for scan in range(3):
        # print "Scan: ", scan

        for radial in range(2):
            # print "Radial: ", radial

            for gate in range(9):
                if scan == 0:
                    if invalid_data(data_set, scan, radial, gate, True):
                        continue
                elif scan == 1:
                    if invalid_data(data_set, scan - 1, radial, gate, False):
                        continue
                else:
                    if invalid_data(data_set, scan - 1, radial, gate, True):
                        continue
                _date = num2date(data_set.variables['timeR'][scan][radial], time_units)
                timeR = time.mktime(_date.timetuple())
                elevation = elevation_set[scan]
                if (radial_size / 360) == 1:
                    azimuth = float(int(data_set.variables['azimuthR'][scan][radial]))
                else:
                    azimuth = float(int(data_set.variables['azimuthR'][scan][radial] * 2)) / 2

                distance = float(int(data_set.variables['distanceR'][gate] / 1000 * 4)) / 4

                point = (timeR, elevation, azimuth, distance)

                if point not in coordinates:
                    if scan == 0:
                        radial_velocity = data_set.variables['RadialVelocity'][scan][radial][gate]
                    elif scan == 1:
                        radial_velocity = data_set.variables['RadialVelocity_HI'][scan - 1][radial][gate]
                    else:
                        radial_velocity = data_set.variables['RadialVelocity'][scan - 1][radial][gate]
                    coordinates[point] = {"Reflectivity": data_set.variables['Reflectivity'][scan][radial][gate],
                                          "RadialVelocity": radial_velocity,
                                          "DifferentialReflectivity": data_set.variables['DifferentialReflectivity'][scan][radial][gate],
                                          "SpectrumWidth": data_set.variables['SpectrumWidth'][scan][radial][gate],
                                          "CorrelationCoefficient": data_set.variables['CorrelationCoefficient'][scan][radial][gate],
                                          "DifferentialPhase": data_set.variables['DifferentialPhase'][scan][radial][gate]}

                    # print point, coordinates[point]

    output2file(output_path, coordinates)
    return


if __name__ == '__main__':
    in_path = "/home/joexu/copy.nc"
    out_path = "/home/joexu/output.txt"
    main(in_path, out_path)