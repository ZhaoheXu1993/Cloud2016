import ucar.ma2.Array;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import java.io.*;
import java.nio.file.NoSuchFileException;
import java.util.List;
import java.util.jar.Pack200;

import static com.sun.activation.registries.LogSupport.log;

public class coordinatesGenerator {
    private final static String rootPath = "/tmp/sampleData";
    private final static float[] ELEVATION_COLLECTION = {
            (float)0.5,
            (float)1.45,
            (float)2.4,
            (float)3.35,
            (float)4.3,
            (float)6.0,
            (float)9.9,
            (float)14.6,
            (float)19.5};
    private final static String[][] filePath = {
        {
                    "/00.50_AliasedVelocity_20121029-000451.netcdf",
                    "/00.50_PhiDP_20121029-000421.netcdf",
                    "/00.50_Reflectivity_20121029-000421.netcdf",
                    "/00.50_ReflectivityQC_20121029-000421.netcdf",
                    "/00.50_SpectrumWidth_20121029-000451.netcdf",
                    "/00.50_Zdr_20121029-000421.netcdf",
                    "/00.50_RhoHV_20121029-000421.netcdf"

        },
        {
                    "/01.45_AliasedVelocity_20121029-000551.netcdf",
                    "/01.45_PhiDP_20121029-000521.netcdf",
                    "/01.45_Reflectivity_20121029-000521.netcdf",
                    "/01.45_ReflectivityQC_20121029-000521.netcdf",
                    "/01.45_SpectrumWidth_20121029-000551.netcdf",
                    "/01.45_Zdr_20121029-000521.netcdf",
                    "/01.45_RhoHV_20121029-000521.netcdf"
        },
        {
                    "/02.40_AliasedVelocity_20121029-000622.netcdf",
                    "/02.40_PhiDP_20121029-000622.netcdf",
                    "/02.40_Reflectivity_20121029-000622.netcdf",
                    "/02.40_ReflectivityQC_20121029-000622.netcdf",
                    "/02.40_SpectrumWidth_20121029-000622.netcdf",
                    "/02.40_Zdr_20121029-000622.netcdf",
                    "/02.40_RhoHV_20121029-000622.netcdf"
        },
        {
                    "/03.35_AliasedVelocity_20121029-000652.netcdf",
                    "/03.35_PhiDP_20121029-000652.netcdf",
                    "/03.35_Reflectivity_20121029-000652.netcdf",
                    "/03.35_ReflectivityQC_20121029-000652.netcdf",
                    "/03.35_SpectrumWidth_20121029-000652.netcdf",
                    "/03.35_Zdr_20121029-000652.netcdf",
                    "/03.35_RhoHV_20121029-000652.netcdf"
        },
        {
                    "/04.30_AliasedVelocity_20121029-000723.netcdf",
                    "/04.30_PhiDP_20121029-000723.netcdf",
                    "/04.30_Reflectivity_20121029-000723.netcdf",
                    "/04.30_ReflectivityQC_20121029-000723.netcdf",
                    "/04.30_SpectrumWidth_20121029-000723.netcdf",
                    "/04.30_Zdr_20121029-000723.netcdf",
                    "/04.30_RhoHV_20121029-000723.netcdf"
        },
        {
                    "/06.00_AliasedVelocity_20121029-000754.netcdf",
                    "/06.00_PhiDP_20121029-000754.netcdf",
                    "/06.00_Reflectivity_20121029-000754.netcdf",
                    "/06.00_ReflectivityQC_20121029-000754.netcdf",
                    "/06.00_SpectrumWidth_20121029-000754.netcdf",
                    "/06.00_Zdr_20121029-000754.netcdf",
                    "/06.00_RhoHV_20121029-000754.netcdf"
        },
        {
                    "/09.90_AliasedVelocity_20121029-000826.netcdf",
                    "/09.90_PhiDP_20121029-000826.netcdf",
                    "/09.90_Reflectivity_20121029-000826.netcdf",
                    "/09.90_ReflectivityQC_20121029-000826.netcdf",
                    "/09.90_SpectrumWidth_20121029-000826.netcdf",
                    "/09.90_Zdr_20121029-000826.netcdf",
                    "/09.90_RhoHV_20121029-000826.netcdf"
        },
        {
                    "/14.60_AliasedVelocity_20121029-000851.netcdf",
                    "/14.60_PhiDP_20121029-000851.netcdf",
                    "/14.60_Reflectivity_20121029-000851.netcdf",
                    "/14.60_ReflectivityQC_20121029-000851.netcdf",
                    "/14.60_SpectrumWidth_20121029-000851.netcdf",
                    "/14.60_Zdr_20121029-000851.netcdf",
                    "/14.60_RhoHV_20121029-000851.netcdf"
        },
        {
                    "/19.50_AliasedVelocity_20121029-000916.netcdf",
                    "/19.50_PhiDP_20121029-000916.netcdf",
                    "/19.50_Reflectivity_20121029-000916.netcdf",
                    "/19.50_ReflectivityQC_20121029-000916.netcdf",
                    "/19.50_SpectrumWidth_20121029-000916.netcdf",
                    "/19.50_Zdr_20121029-000916.netcdf",
                    "/19.50_RhoHV_20121029-000916.netcdf"
        }
    };
    private final static String echoPath[] = {
            "/TraditionalEchoTop_5_20121029-000421.netcdf",
            "/TraditionalEchoTop_15_20121029-000421.netcdf",
            "/TraditionalEchoTop_20_20121029-000421.netcdf",
            "/TraditionalEchoTop_30_20121029-000421.netcdf"
    };

    private static void writeToFile(float[][][] flattenedData) {
        BufferedWriter output = null;
        try {
            File file = new File("outModel.txt");
            output = new BufferedWriter(new FileWriter(file));

            for (int azi = 0; azi < 720; azi++) {
                for (int gate = 0; gate < 920; gate++) {
                    String line = "";
                    for (int v = 0; v < 36; v++) {
                        line += Float.toString(flattenedData[azi][gate][v]) + " ";
                    }
                    line += "\n";
                    output.write(line);
                }
            }
        } catch ( IOException e ) {
            e.printStackTrace();
        } finally {
            if ( output != null ) {
                try {
                    output.close();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        }
        return;
    }

    private static float getLabel(int aIdx, int gIdx, float[][][][] coordinates) {
        for (int e = 0; e < 9; e++) {
            if (coordinates[e][aIdx][gIdx][7] == 0) {
                return 0;
            }
        }
        return 1;
    }

    private static float getLocMean(int aIdx, int gIdx, int eIdx, int vIdx, float[][][][] coordinates) {
        int aStart = aIdx - 2 < 0 ? 0 : aIdx - 2, aEnd = aIdx + 2 > 719 ? 719 : aIdx + 2;
        int gStart = gIdx - 2 < 0 ? 0 : gIdx - 2, gEnd = gIdx + 2 > 919 ? 919 : gIdx + 2;
        int count = 0;
        float res = 0;
        for (int azi = aStart; azi <= aEnd; azi++) {
            for (int gate = gStart; gate <= gEnd; gate++) {
                if (coordinates[eIdx][azi][gate][vIdx] == -99900 || coordinates[eIdx][azi][gate][vIdx] == -99901) {
                    continue;
                }
                res += coordinates[eIdx][azi][gate][vIdx];
                count++;
            }
        }

        return res/count;
    }

    private static float getLocVariance(int aIdx, int gIdx, int eIdx, int vIdx, float[][][][] coordinates) {
        float mean = getLocMean(aIdx, gIdx, eIdx, vIdx, coordinates);

        int aStart = aIdx - 2 < 0 ? 0 : aIdx - 2, aEnd = aIdx + 2 > 719 ? 719 : aIdx + 2;
        int gStart = gIdx - 2 < 0 ? 0 : gIdx - 2, gEnd = gIdx + 2 > 919 ? 919 : gIdx + 2;
        int count = 0;
        float segma = 0;
        for (int azi = aStart; azi <= aEnd; azi++) {
            for (int gate = gStart; gate <= gEnd; gate++) {
                segma += (float)Math.pow(coordinates[eIdx][azi][gate][vIdx] - mean, 2);
                count++;
            }
        }
        return segma/count;
    }

    private static float getShMean(int aIdx, int gIdx, int eIdx, int vIdx, float[][][][] coordinates) {
        int gStart = gIdx - 2 < 0 ? 0 : gIdx - 2, gEnd = gIdx + 2 > 919 ? 919 : gIdx + 2;
        int count = 0;
        float segma = 0;
        for (int gate = gStart; gate <= gEnd; gate++) {
            segma += coordinates[eIdx][aIdx][gate][vIdx];
            count++;
        }

        return segma/count;
    }

    private static float getShVariance(int aIdx, int gIdx, int eIdx, int vIdx, float[][][][] coordinates) {
        float mean = getShMean(aIdx, gIdx, eIdx, vIdx, coordinates);
        int count = 0;
        float segma = 0;
        int gStart = gIdx - 2 < 0 ? 0 : gIdx - 2, gEnd = gIdx + 2 > 919 ? 919 : gIdx + 2;
        for (int gate = gStart; gate <= gEnd; gate++) {
            segma += (float)Math.pow(coordinates[eIdx][aIdx][gate][vIdx] - mean, 2);
            count++;
        }

        return segma/count;

    }

    private static float[] getMaxRefl(int aIdx, int gIdx, float[][][][] coordinates) {
        float[] ret = new float[2];
        float max = Float.MIN_VALUE, h = 0;
        for (int e = 0; e < 9; e++) {
            if (coordinates[e][aIdx][gIdx][2] > max) {
                max = coordinates[e][aIdx][gIdx][2];
                h = ELEVATION_COLLECTION[e];
            }
        }

        ret[0] = max;
        ret[1] = h;
        return ret;
    }

    private static float getWeightedAvg(int aIdx, int gIdx, float[][][][] coordinates) {
        float sumRefl = 0;
        float sumEle = 0;
        for (int e = 0; e < 9; e++) {
            sumRefl += ELEVATION_COLLECTION[e] * coordinates[e][aIdx][gIdx][2];
            sumEle += ELEVATION_COLLECTION[e];
        }

        return sumRefl/sumEle;
    }

    private static float getInBound(int aIdx, float[][][] data) {
        float count = 0;
        for (int gate = 919; gate >= 0; gate--) {
            //[29] echo top 5
            if (data[aIdx][gate][29] >= 3) {
                count++;
            }
        }

        return count;
    }

    private static void dataHandlerPhase1(float[][][][] coordinates, float[][][] flattenedData) {
        /*
            @36 variables in map:

       */
        for (int azi = 0; azi < 720; azi++) {
            for (int gate = 0; gate < 920; gate++) {
                //[0] label
                flattenedData[azi][gate][0] = getLabel(azi, gate, coordinates);
                //[1] 0.5R value
                flattenedData[azi][gate][1] = coordinates[0][azi][gate][2];
                //[2] 0.5R 5*5 mean
                flattenedData[azi][gate][2] = getLocMean(azi, gate, 0, 2, coordinates);
                //[3] 0.5R 5*5 variance
                flattenedData[azi][gate][3] = getLocVariance(azi, gate, 0, 2, coordinates);
                //[4] 0.5R 1*5 variance
                flattenedData[azi][gate][4] = getShVariance(azi, gate, 0, 2, coordinates);
                //[5] 0.5R diff (phase 2)
                //[6] 0.5R diff 1*5 (phase 2)
                //[7] 0.5R SPIN (phase 2)
                //[8] 0.5R inflection along radius (phase 2)
                //[9] 0.5V value
                flattenedData[azi][gate][9] = coordinates[0][azi][gate][0];
                //[10] 0.5V 5*5 mean
                flattenedData[azi][gate][10] = getLocMean(azi, gate, 0, 0, coordinates);
                //[11] 0.5V 5*5 variance
                flattenedData[azi][gate][10] = getLocVariance(azi, gate, 0, 0, coordinates);
                //[12] 0.5V diff (phase 2)
                //[13] 0.5V minimal variance (phase 2)
                //[14] 0.5Zdr value
                flattenedData[azi][gate][14] = coordinates[0][azi][gate][5];
                //[15] 0.5RHov value
                flattenedData[azi][gate][15] = coordinates[0][azi][gate][6];
                //[16] 0.5DP value
                flattenedData[azi][gate][16] = coordinates[0][azi][gate][1];
                //[17] 0.5Spect value
                flattenedData[azi][gate][17] = coordinates[0][azi][gate][4];
                //[18] 1.45R value
                flattenedData[azi][gate][18] = coordinates[1][azi][gate][2];
                //[19] 1.45R 5*5 mean
                flattenedData[azi][gate][19] = getLocMean(azi, gate, 1, 2, coordinates);
                //[20] 1.45R 5*5 variance
                flattenedData[azi][gate][20] = getLocVariance(azi, gate, 1, 2, coordinates);
                //[21] 1.45R 1*5 variance
                flattenedData[azi][gate][21] = getShVariance(azi, gate, 1, 2, coordinates);
                //[22] 1.45R diff (phase 2)
                //[23] 1.45R diff 1*5 (phase 2)
                //[24] 1.45R minimal variance (phase 2)
                //[25] 1.45Zdr value
                flattenedData[azi][gate][25] = coordinates[1][azi][gate][5];
                //[26] 1.45Rhov value
                flattenedData[azi][gate][26] = coordinates[1][azi][gate][6];
                //[27] 1.45Spect value
                flattenedData[azi][gate][27] = coordinates[1][azi][gate][4];
                //[28] 1.45DP value
                flattenedData[azi][gate][28] = coordinates[1][azi][gate][1];
                //[29] echo top 5
                flattenedData[azi][gate][29] = coordinates[0][azi][gate][8];
                //[30] echo top 15
                flattenedData[azi][gate][30] = coordinates[0][azi][gate][9];
                //[31] echo top 20
                flattenedData[azi][gate][31] = coordinates[0][azi][gate][10];
                //[32] vertical max refl
                float[] tmp = getMaxRefl(azi, gate, coordinates);
                flattenedData[azi][gate][32] = tmp[0];
                //[33] weighted average
                flattenedData[azi][gate][33] = getWeightedAvg(azi, gate, coordinates);
                //[34] height of maximum
                flattenedData[azi][gate][34] = tmp[1];
                //[35] inbound (phase 2)
                flattenedData[azi][gate][35] = getInBound(azi, flattenedData);
            }
        }
    }

    private static float getMinVariance(int aIdx, int gIdx, int vIdx, float[][][] data) {
        int aStart = aIdx - 2 < 0 ? 0 : aIdx - 2, aEnd = aIdx + 2 > 719 ? 719 : aIdx + 2;
        int gStart = gIdx - 2 < 0 ? 0 : gIdx - 2, gEnd = gIdx + 2 > 919 ? 919 : gIdx + 2;
        float min = Float.MAX_VALUE;

        for (int azi = aStart; azi <= aEnd; azi++) {
            for (int gate = gStart; gate <= gEnd; gate++) {
                min = data[azi][gate][vIdx] < min ? data[azi][gate][vIdx] : min;
            }
        }

        return min;
    }

    private static float getSpin(int aIdx, int gIdx, float[][][] data) {
        // in radial direction -> azimuth
        float count = 0;
        int aStart = aIdx - 2 < 0 ? 0 : aIdx - 2, aEnd = aIdx + 2 > 719 ? 719 : aIdx + 2;
        int gStart = gIdx - 2 < 0 ? 0 : gIdx - 2, gEnd = gIdx + 2 > 919 ? 919 : gIdx + 2;

        for (int gate = gStart; gate <= gEnd; gate++) {
            for (int azi = aStart; azi <= aEnd; azi++) {
                int next = (azi + 1 > aEnd) ? aEnd : azi + 1;
                if (Math.abs(data[azi][gate][1] - data[next][gate][1]) >= 2) {
                    count++;
                }
            }
        }

        return count;
    }

    private static float getShSpin(int aIdx, int gIdx, float[][][] data) {
        // in radial direction -> azimuth
        float count = 0;
        int aStart = aIdx - 2 < 0 ? 0 : aIdx - 2, aEnd = aIdx + 2 > 719 ? 719 : aIdx + 2;

        for (int azi = aStart; azi <= aEnd; azi++) {
            int next = (azi + 1 > aEnd) ? aEnd : azi + 1;
            if (Math.abs(data[azi][gIdx][1] - data[next][gIdx][1]) >= 2) {
                count++;
            }
        }

        return count;
    }

    private static void dataHandlerPhase2(float[][][][] coordinates, float[][][] flattenedData) {
        for (int azi = 0; azi < 720; azi++) {
            for (int gate = 0; gate < 920; gate++) {
                //[5] 0.5R diff (phase 2)
                flattenedData[azi][gate][5] = flattenedData[azi][gate][1]
                        - flattenedData[azi][gate][2];
                //[6] 0.5R diff 1*5 (phase 2)
                flattenedData[azi][gate][6] = flattenedData[azi][gate][1]
                        - getShMean(azi, gate, 0, 2, coordinates);
                //[7] 0.5R SPIN (phase 2)
                flattenedData[azi][gate][7] = getSpin(azi, gate, flattenedData);
                //[8] 0.5R inflection along radius (phase 2)
                flattenedData[azi][gate][8] = getShSpin(azi, gate, flattenedData);
                //[12] 0.5V diff (phase 2)
                flattenedData[azi][gate][12] = flattenedData[azi][gate][9]
                        - flattenedData[azi][gate][10];
                //[13] 0.5V minimal variance (phase 2)
                flattenedData[azi][gate][13] = getMinVariance(azi, gate, 11, flattenedData);
                //[22] 1.45R diff (phase 2)
                flattenedData[azi][gate][22] = flattenedData[azi][gate][18]
                        - flattenedData[azi][gate][19];
                //[23] 1.45R diff 1*5 (phase 2)
                flattenedData[azi][gate][23] = flattenedData[azi][gate][18]
                        - getShMean(azi, gate, 1, 2, coordinates);
                //[24] 1.45R minimal variance (phase 2)
                flattenedData[azi][gate][24] = getMinVariance(azi, gate, 20, flattenedData);
            }
        }
    }

    private static void fillEcho(Array echoData,
                                 float echoAziStart,
                                 float echoAziInterval,
                                 int echoGateInterval,
                                 float[][][][] coordinates,
                                 int echoVal) {
        for (int azi = 0; azi < 720; azi++) {
            //System.out.println(azi);
            for (int gate = 0; gate < 920; gate++) {
                int factor = (int)((1000/echoGateInterval) * echoAziInterval*2);
                int echoAziIndex = azi;
                echoAziIndex = echoAziIndex > 719 ? (echoAziIndex - 720): echoAziIndex;
                for (int e = 0; e < 9; e++) {
                    coordinates[e][echoAziIndex][gate][echoVal] = echoData.getFloat((azi * 920 + gate)/factor);
                }
            }
        }
    }

    private static void fillCoornates(Array vData, float vAziStart, float vAziInterval, int vGateInterval,
                                      Array dpData, float dpAziStart, float dpAziInterval, int dpGateInterval,
                                      Array reflData, float reflAziStart, float reflAziInterval, int reflGateInterval,
                                      Array qcData, float qcAziStart, float qcAziInterval, int qcGateInterval,
                                      Array spectData, float spectAziStart, float spectAziInterval, int spectGateInterval,
                                      Array zdrData, float zdrAziStart, float zdrAziInterval, int zdrGateInterval,
                                      Array rhovData, float rhovAziStart, float rhovAziInterval, int rhovGateInterval,
                                      float[][][][] coordinates, int eIndex) {

        for (int azi = 0; azi < 720; azi++) {
//            if (azi == 569) {
//                System.out.println("haha");
//            }
            //System.out.println(azi);
            for (int gate = 0; gate < 920; gate++) {
                int[] shape = vData.getShape();
                // velocity
                //System.out.println("Gate: " + gate);
                int factor = (int)((vGateInterval/250) * vAziInterval*2);
                int vAziIndex = (int)(vAziStart * 2 - 1 + azi);
                vAziIndex = vAziIndex > 719 ? (vAziIndex - 720): vAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][vAziIndex][gate][0] = -99900;
                } else {
                    coordinates[eIndex][vAziIndex][gate][0] = vData.getFloat((azi * 920 + gate) / factor);
                }
                // difference phase
                factor = (int)((dpGateInterval/250) * dpAziInterval*2);
                int dpAziIndex = (int)(dpAziStart * 2 - 1 + azi);
                dpAziIndex = dpAziIndex > 719 ? (dpAziIndex - 720): dpAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][dpAziIndex][gate][1] = -99900;
                } else {
                    coordinates[eIndex][dpAziIndex][gate][1] = dpData.getFloat((azi * 920 + gate) / factor);
                }
                // reflectivity
                factor = (int)((reflGateInterval/250) * reflAziInterval*2);
                int reflAziIndex = azi;
                reflAziIndex = reflAziIndex > 719 ? (reflAziIndex - 720): reflAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][reflAziIndex][gate][1] = -99900;
                } else {
                    coordinates[eIndex][reflAziIndex][gate][2] = reflData.getFloat((azi * 920 + gate) / factor);
                }
                // qc
                factor = (int)((qcGateInterval/250) * qcAziInterval*2);
                int qcAziIndex = (int)(qcAziStart * 2 - 1 + azi);
                qcAziIndex = qcAziIndex > 719 ? (qcAziIndex - 720): qcAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][qcAziIndex][gate][1] = -99900;
                } else {
                    coordinates[eIndex][qcAziIndex][gate][3] = qcData.getFloat((azi * 920 + gate) / factor);
                }
                // spect
                factor = (int)((spectGateInterval/250) * spectAziInterval*2);
                int spectAziIndex = (int)(spectAziStart * 2 - 1 + azi);
                spectAziIndex = spectAziIndex > 719 ? (spectAziIndex - 720): spectAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][spectAziIndex][gate][1] = -99900;
                } else {
                    coordinates[eIndex][spectAziIndex][gate][4] = spectData.getFloat((azi * 920 + gate) / factor);
                }
                // zdr
                factor = (int)((zdrGateInterval/250) * zdrAziInterval*2);
                int zdrAziIndex = (int)(zdrAziStart * 2 - 1 + azi);
                zdrAziIndex = zdrAziIndex > 719 ? (zdrAziIndex - 720): zdrAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][zdrAziIndex][gate][1] = -99900;
                } else {
                    coordinates[eIndex][zdrAziIndex][gate][5] = zdrData.getFloat((azi * 920 + gate) / factor);
                }
                // rhov
                factor = (int)((rhovGateInterval/250) * rhovAziInterval*2);
                int rhovAziIndex = (int)(rhovAziStart * 2 - 1 + azi);
                rhovAziIndex = rhovAziIndex > 719 ? (rhovAziIndex - 720): rhovAziIndex;
                if (shape[0] * shape[1] - 1 < (azi * 920 + gate) / factor) {
                    coordinates[eIndex][rhovAziIndex][gate][1] = -99900;
                } else {
                    coordinates[eIndex][rhovAziIndex][gate][6] = rhovData.getFloat((azi * 920 + gate) / factor);
                }
//                //echo top 5
//                coordinates[eIndex][azi][gate][16] = 0;
//                //echo top 10
//                coordinates[eIndex][azi][gate][17] = 0;
//                //echo top 20
//                coordinates[eIndex][azi][gate][18] = 0;
//                //echo top 30
//                coordinates[eIndex][azi][gate][19] = 0;
                //label
                if (coordinates[eIndex][qcAziIndex][gate][3] == -99900 ||
                        coordinates[eIndex][qcAziIndex][gate][3] == -99901) {
                    coordinates[eIndex][qcAziIndex][gate][7] = 0;
                } else {
                    coordinates[eIndex][qcAziIndex][gate][7] = 1;
                }
            }
        }

//        // 3*3 and 1*5
//        for (int azi = 0; azi < 720; azi++) {
//            for (int gate = 0; gate < 920; gate++) {
//
//            }
//        }
    }

    public static void main(String[] args) {
        /*
            @ 9 elevations (flatten)
            @ 720 azimuths
            @ 920 gates
            @ 36 variables: label,

                            0.5R value,
                            0.5R 5*5 mean (local mean),
                            0.5R 5*5 variance (local variance),
                            0.5R difference (value - local mean),
                            0.5R difference for 1*5 (value - 1*5 mean),
                            0.5R 1*5 variance,
                            0.5R SPIN (5*5 area difference >= 2, ++1),
                            0.5R inflection along radius (1*5 SPIN),
                            0.5V value,
                            0.5V 5*5 mean (local mean),
                            0.5V 5*5 variance (local variance),
                            0.5V difference (value - local mean),
                            0.5V minimal variance (5*5 min variance),
                            1.45R value,
                            1.45R 5*5 mean (local mean),
                            1.45R 5*5 variance (local variance),
                            1.45R difference (value - local mean),
                            1.45R 1*5 variance,
                            1.45R difference for 1*5 (value - 1*5 mean),
                            1.45R minimal variance,

                            AllE vertical max Refl value,
                            AllE weighted average (sum(elevation*R) / sum(elevation))
                            AllE height of maximum (gate, elevation),
                            AllE inbound (5 echo top >= 3km then 0, else inbound distance, from 920 to 0),
                            AllE echo top 5,
                            AllE echo top 15,
                            AllE echo top 20,

                            0.5Zdr value,
                            0.5RHoV value,
                            0.5DP value
                            0.5Spect value,
                            1.45Zdr value,
                            1.45RHoV value,
                            1.45Spect value
                            1.45DP value

         */
        // basic coordinates
        float[][][][] coordinates = new float[9][720][920][11];
        float[][][] flattenedData = new float[720][920][36];

        long s = System.currentTimeMillis();

        NetcdfFile[] vFiles = new NetcdfFile[9];
        NetcdfFile[] dpFiles = new NetcdfFile[9];
        NetcdfFile[] reflFiles = new NetcdfFile[9];
        NetcdfFile[] qcFiles = new NetcdfFile[9];
        NetcdfFile[] spectrumFiles = new NetcdfFile[9];
        NetcdfFile[] zdrFiles = new NetcdfFile[9];
        NetcdfFile[] rhoFiles = new NetcdfFile[9];
        NetcdfFile[] echoFiles = new NetcdfFile[4];

        try {
            // open all basic files
            for (int eIndex = 0; eIndex < 9; eIndex++) {
                vFiles[eIndex] = null;
                dpFiles[eIndex] = null;
                reflFiles[eIndex] = null;
                qcFiles[eIndex] = null;
                spectrumFiles[eIndex] = null;
                zdrFiles[eIndex] = null;
                rhoFiles[eIndex] = null;

                vFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][0]);
                dpFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][1]);
                reflFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][2]);
                qcFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][3]);
                spectrumFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][4]);
                zdrFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][5]);
                rhoFiles[eIndex] = NetcdfFile.open(rootPath + filePath[eIndex][6]);

                List<Variable> vDataset = vFiles[eIndex].getVariables();
                Array vAzimuth = vDataset.get(0).read();
                Array vData = vDataset.get(5).read();
                float vAzimuthInterval = (vAzimuth.getFloat(1) - vAzimuth.getFloat(0)) < 0 ?
                        (vAzimuth.getFloat(2) - vAzimuth.getFloat(1)) :
                        (vAzimuth.getFloat(1) - vAzimuth.getFloat(0));
                vAzimuthInterval = (float)Math.round(vAzimuthInterval * 10f) / 10f;
                int vGateInterval = vDataset.get(3).read().getInt(0);
                float vAziStart = vAzimuth.getFloat(0);

                List<Variable> dpDataset = dpFiles[eIndex].getVariables();
                Array dpAzimuth = dpDataset.get(0).read();
                Array dpData = dpDataset.get(5).read();
                float dpAzimuthInterval = (dpAzimuth.getFloat(1) - dpAzimuth.getFloat(0)) < 0 ?
                        (dpAzimuth.getFloat(2) - dpAzimuth.getFloat(1)) :
                        (dpAzimuth.getFloat(1) - dpAzimuth.getFloat(0));
                dpAzimuthInterval = (float)Math.round(dpAzimuthInterval * 10f) / 10f;
                int dpGateInterval = dpDataset.get(3).read().getInt(0);
                float dpAziStart = dpAzimuth.getFloat(0);

                List<Variable> reflDataset = reflFiles[eIndex].getVariables();
                Variable reflDatas = reflFiles[eIndex].findVariable("Reflectivity");
                Array reflAzimuth = reflDataset.get(0).read();
                Array reflData = reflDatas.read();
                float reflAzimuthInterval = (reflAzimuth.getFloat(1) - reflAzimuth.getFloat(0)) < 0 ?
                        (reflAzimuth.getFloat(2) - reflAzimuth.getFloat(1)) :
                        (reflAzimuth.getFloat(1) - reflAzimuth.getFloat(0));
                reflAzimuthInterval = (float)Math.round(reflAzimuthInterval * 10f) / 10f;
                int reflGateInterval = reflDataset.get(3).read().getInt(0);
                float reflAziStart = reflAzimuth.getFloat(0);

                List<Variable> qcDataset = qcFiles[eIndex].getVariables();
                Array qcAzimuth = qcDataset.get(0).read();
                Array qcData = qcDataset.get(5).read();

//                for (int i = 0; i < 720; i++) {
//                    if (qcData.getFloat(i) != -99900 && qcData.getFloat(i) != -99901) {
//                        System.out.println(i);
//                    }
//                }

                float qcAzimuthInterval = (qcAzimuth.getFloat(1) - qcAzimuth.getFloat(0)) < 0 ?
                        (qcAzimuth.getFloat(2) - qcAzimuth.getFloat(1)) :
                        (qcAzimuth.getFloat(1) - qcAzimuth.getFloat(0));
                qcAzimuthInterval = (float)Math.round(qcAzimuthInterval * 10f) / 10f;
                int qcGateInterval = qcDataset.get(3).read().getInt(0);
                float qcAziStart = qcAzimuth.getFloat(0);

                List<Variable> spectrumDataset = spectrumFiles[eIndex].getVariables();
                Array spectAzimuth = spectrumDataset.get(0).read();
                Array spectData = spectrumDataset.get(5).read();
                float spectAzimuthInterval = (spectAzimuth.getFloat(1) - spectAzimuth.getFloat(0)) < 0 ?
                        (spectAzimuth.getFloat(2) - spectAzimuth.getFloat(1)) :
                        (spectAzimuth.getFloat(1) - spectAzimuth.getFloat(0));
                spectAzimuthInterval = (float)Math.round(spectAzimuthInterval * 10f) / 10f;
                int spectGateInterval = spectrumDataset.get(3).read().getInt(0);
                float spectAziStart = spectAzimuth.getFloat(0);

                List<Variable> zdrDataset = zdrFiles[eIndex].getVariables();
                Array zdrAzimuth = zdrDataset.get(0).read();
                Array zdrData = zdrDataset.get(5).read();
                float zdrAzimuthInterval = (zdrAzimuth.getFloat(1) - zdrAzimuth.getFloat(0)) < 0 ?
                        (zdrAzimuth.getFloat(2) - zdrAzimuth.getFloat(1)) :
                        (zdrAzimuth.getFloat(1) - zdrAzimuth.getFloat(0));
                zdrAzimuthInterval = (float)Math.round(zdrAzimuthInterval * 10f) / 10f;
                int zdrGateInterval = zdrDataset.get(3).read().getInt(0);
                float zdrAziStart = zdrAzimuth.getFloat(0);

                List<Variable> rhovDataset = rhoFiles[eIndex].getVariables();
                Array rhovAzimuth = rhovDataset.get(0).read();
                Array rhovData = zdrDataset.get(5).read();
                float rhovAzimuthInterval = 0;
                if ((rhovAzimuth.getFloat(1) - rhovAzimuth.getFloat(0)) < 0 ) {
                    rhovAzimuthInterval = rhovAzimuth.getFloat(2) - rhovAzimuth.getFloat(1);
                } else {
                    rhovAzimuthInterval = rhovAzimuth.getFloat(1) - rhovAzimuth.getFloat(0);
                }

                rhovAzimuthInterval = (float)Math.round(rhovAzimuthInterval * 10f) / 10f;
                int rhovGateInterval = rhovDataset.get(3).read().getInt(0);
                float rhovAziStart = rhovAzimuth.getFloat(0);

                fillCoornates(vData, vAziStart, vAzimuthInterval, vGateInterval,
                        dpData, dpAziStart, dpAzimuthInterval, dpGateInterval,
                        reflData, reflAziStart, reflAzimuthInterval, reflGateInterval,
                        qcData, qcAziStart, qcAzimuthInterval, qcGateInterval,
                        spectData, spectAziStart, spectAzimuthInterval, spectGateInterval,
                        zdrData, zdrAziStart, zdrAzimuthInterval, zdrGateInterval,
                        rhovData, rhovAziStart, rhovAzimuthInterval, rhovGateInterval,
                        coordinates, eIndex);
            }
            // open echoTop files
            for (int echoIndex = 0; echoIndex < 3; echoIndex++) {
                echoFiles[echoIndex] = null;

                echoFiles[echoIndex] = NetcdfFile.open(rootPath + echoPath[echoIndex]);

                List<Variable> echoDataset = echoFiles[echoIndex].getVariables();
                Array echoAzimuth = echoDataset.get(0).read();
                Array echoData = echoDataset.get(4).read();
                float echoAzimuthInterval = (echoAzimuth.getFloat(1) - echoAzimuth.getFloat(0)) < 0 ?
                        (echoAzimuth.getFloat(2) - echoAzimuth.getFloat(1)) :
                        (echoAzimuth.getFloat(1) - echoAzimuth.getFloat(0));
                echoAzimuthInterval = (float)Math.round(echoAzimuthInterval * 10f) / 10f;
                int echoGateInterval = echoDataset.get(3).read().getInt(0);
                float echoAziStart = echoAzimuth.getFloat(0);

                fillEcho(echoData, echoAziStart, echoAzimuthInterval, echoGateInterval, coordinates, echoIndex + 8);
            }

            dataHandlerPhase1(coordinates, flattenedData);
            dataHandlerPhase2(coordinates, flattenedData);
            //dataHandlerPhase3(coordinates, flattenedData);
            //normalPhase(flattenedData);
            //System.out.println(vDataset.get(1).read().getFloat(0));
            //Array data = vDataset.get(1).read();
            //NCdumpW.printArray(data, "FF",System.out, null);

        } catch (IOException ioe) {
            log("Fail to open", ioe);
        } finally {
            try {
                for (int idx = 0; idx < 9; idx++) {
                    if (null != vFiles[idx]) {
                        vFiles[idx].close();
                    }
                    if (null != dpFiles[idx]) {
                        dpFiles[idx].close();
                    }
                    if (null != reflFiles[idx]) {
                        reflFiles[idx].close();
                    }
                    if (null != qcFiles[idx]) {
                        qcFiles[idx].close();
                    }
                    if (null != spectrumFiles[idx]) {
                        spectrumFiles[idx].close();
                    }
                    if (null != zdrFiles[idx]) {
                        zdrFiles[idx].close();
                    }
                }
                for (int idx = 0; idx < 4; idx++) {
                    if (null != echoFiles[idx]) {
                        echoFiles[idx].close();
                    }
                }
            } catch (IOException ioe) {
                log("Fail to close", ioe);
            }
        }

        //System.out.println((System.currentTimeMillis()-s)/1000);

        //check valid data and invalid
//        for (int i = 0; i < 720; i++) {
//            for (int j = 0; j < 920; j++) {
//                if (flattenedData[i][j][0] == 1) {
//                    System.out.println(i + ":" + j);
//                }
//            }
//        }
        writeToFile(flattenedData);
    }
}
