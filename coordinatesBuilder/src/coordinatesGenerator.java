import ucar.ma2.Array;
import ucar.nc2.NCdumpW;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import java.io.IOException;
import java.util.List;

import static com.sun.activation.registries.LogSupport.log;

public class coordinatesGenerator {
    private final static String rootPath = "/home/joexu/Cloud2016/sampleData";
    private final static String[][] filePath = {
        {
                    "/00.50_AliasedVelocity_20121029-000451.netcdf",
                    "/00.50_PhiDP_20121029-000421.netcdf",
                    "/00.50_Reflectivity_20121029-000421.netcdf",
                    "/00.50_ReflectivityQC_20121029-000421.netcdf",
                    "/00.50_SpectrumWidth_20121029-000451.netcdf",
                    "/00.50_Zdr_20121029-000421.netcdf"
        },
        {
                    "/01.45_AliasedVelocity_20121029-000551.netcdf",
                    "/01.45_PhiDP_20121029-000521.netcdf",
                    "/01.45_Reflectivity_20121029-000521.netcdf",
                    "/01.45_ReflectivityQC_20121029-000521.netcdf",
                    "/01.45_SpectrumWidth_20121029-000551.netcdf",
                    "/01.45_Zdr_20121029-000521.netcdf"
        },
        {
                    "/02.40_AliasedVelocity_20121029-000622.netcdf",
                    "/02.40_PhiDP_20121029-000622.netcdf",
                    "/02.40_Reflectivity_20121029-000622.netcdf",
                    "/02.40_ReflectivityQC_20121029-000622.netcdf",
                    "/02.40_SpectrumWidth_20121029-000622.netcdf",
                    "/02.40_Zdr_20121029-000622.netcdf"
        },
        {
                    "/03.35_AliasedVelocity_20121029-000652.netcdf",
                    "/03.35_PhiDP_20121029-000652.netcdf",
                    "/03.35_Reflectivity_20121029-000652.netcdf",
                    "/03.35_ReflectivityQC_20121029-000652.netcdf",
                    "/03.35_SpectrumWidth_20121029-000652.netcdf",
                    "/03.35_Zdr_20121029-000652.netcdf"
        },
        {
                    "/04.30_AliasedVelocity_20121029-000723.netcdf",
                    "/04.30_PhiDP_20121029-000723.netcdf",
                    "/04.30_Reflectivity_20121029-000723.netcdf",
                    "/04.30_ReflectivityQC_20121029-000723.netcdf",
                    "/04.30_SpectrumWidth_20121029-000723.netcdf",
                    "/04.30_Zdr_20121029-000723.netcdf"
        },
        {
                    "/06.00_AliasedVelocity_20121029-000754.netcdf",
                    "/06.00_PhiDP_20121029-000754.netcdf",
                    "/06.00_Reflectivity_20121029-000754.netcdf",
                    "/06.00_ReflectivityQC_20121029-000754.netcdf",
                    "/06.00_SpectrumWidth_20121029-000754.netcdf",
                    "/06.00_Zdr_20121029-000754.netcdf"
        },
        {
                    "/09.90_AliasedVelocity_20121029-000826.netcdf",
                    "/09.90_PhiDP_20121029-000826.netcdf",
                    "/09.90_Reflectivity_20121029-000826.netcdf",
                    "/09.90_ReflectivityQC_20121029-000826.netcdf",
                    "/09.90_SpectrumWidth_20121029-000826.netcdf",
                    "/09.90_Zdr_20121029-000826.netcdf"
        },
        {
                    "/14.60_AliasedVelocity_20121029-000851.netcdf",
                    "/14.60_PhiDP_20121029-000851.netcdf",
                    "/14.60_Reflectivity_20121029-000851.netcdf",
                    "/14.60_ReflectivityQC_20121029-000851.netcdf",
                    "/14.60_SpectrumWidth_20121029-000851.netcdf",
                    "/14.60_Zdr_20121029-000851.netcdf"
        },
        {
                    "/19.50_AliasedVelocity_20121029-000916.netcdf",
                    "/19.50_PhiDP_20121029-000916.netcdf",
                    "/19.50_Reflectivity_20121029-000916.netcdf",
                    "/19.50_ReflectivityQC_20121029-000916.netcdf",
                    "/19.50_SpectrumWidth_20121029-000916.netcdf",
                    "/19.50_Zdr_20121029-000916.netcdf"
        }
    };

    private static void writeToFile(float[][][][] coordinates) {

        return;
    }
    private static int counter = 724;
    private static void fillCoornates(Array vData, float vAziInterval, int vGateInterval,
                                      Array dpData, float dpAziInterval, int dpGateInterval,
                                      Array reflData, float reflAziInterval, int reflGateInterval,
                                      Array qcData, float qcAziInterval, int qcGateInterval,
                                      Array spectData, float spectAziInterval, int spectGateInterval,
                                      Array zdrData, float zdrAziInterval, int zdrGateInterval,
                                      float[][][][] coordinates, int eIndex) {

        for (int azi = 0; azi < 720; azi++) {
            if (counter == 0) {
                System.out.println("FIND");
            }
            counter--;
            //System.out.println(azi);
            int counterB = 119;
            for (int gate = 0; gate < 920; gate++) {
                // velocity
                if (counter==0 && counterB == 0) {
                    System.out.println("GET");
                }
                counterB--;
                //System.out.println("Gate: " + gate);
                int factor = (int)((1000/vGateInterval) * vAziInterval*2);
                coordinates[eIndex][azi][gate][0] = vData.getFloat((azi * 920 + gate)/factor);
                // difference phase
                factor = (int)((1000/dpGateInterval) * dpAziInterval*2);
                coordinates[eIndex][azi][gate][3] = dpData.getFloat((azi * 920 + gate)/factor);
                // reflectivity
                factor = (int)((1000/reflGateInterval) * reflAziInterval*2);
                coordinates[eIndex][azi][gate][6] = reflData.getFloat((azi * 920 + gate)/factor);
                // qc
                factor = (int)((1000/qcGateInterval) * qcAziInterval*2);
                coordinates[eIndex][azi][gate][9] = qcData.getFloat((azi * 920 + gate)/factor);
                // spect
                factor = (int)((1000/spectGateInterval) * spectAziInterval*2);
                coordinates[eIndex][azi][gate][12] = spectData.getFloat((azi * 920 + gate)/factor);
                // zdr
                factor = (int)((1000/zdrGateInterval) * zdrAziInterval*2);
                coordinates[eIndex][azi][gate][15] = zdrData.getFloat((azi * 920 + gate)/factor);
                //echo top 5
                coordinates[eIndex][azi][gate][16] = 0;
                //echo top 10
                coordinates[eIndex][azi][gate][17] = 0;
                //echo top 20
                coordinates[eIndex][azi][gate][18] = 0;
                //echo top 30
                coordinates[eIndex][azi][gate][19] = 0;
                //label
                coordinates[eIndex][azi][gate][20] = (coordinates[eIndex][azi][gate][9] == -99900) ? 0 : 1;
            }
        }

        // 3*3 and 1*5
        for (int azi = 0; azi < 720; azi++) {
            for (int gate = 0; gate < 920; gate++) {

            }
        }
    }

    public static void main(String[] args) {
        /*
            @ 9 elevations
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
                            AllE echo top 10,
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
        long s = System.currentTimeMillis();
        float[][][][] coordinates = new float[9][720][920][28];

        for (int eIndex = 0; eIndex < 9; eIndex++) {
            NetcdfFile vFile = null, dpFile = null,
                    reflFile = null, spectrumFile = null,
                    zdrFile = null, qcFile = null;

            try {
                vFile = NetcdfFile.open(rootPath + filePath[eIndex][0]);
                dpFile = NetcdfFile.open(rootPath + filePath[eIndex][1]);
                reflFile = NetcdfFile.open(rootPath + filePath[eIndex][2]);
                qcFile = NetcdfFile.open(rootPath + filePath[eIndex][3]);
                spectrumFile = NetcdfFile.open(rootPath + filePath[eIndex][4]);
                zdrFile = NetcdfFile.open(rootPath + filePath[eIndex][5]);

                List<Variable> vDataset = vFile.getVariables();
                Array vAzimuth = vDataset.get(0).read();
                Array vData = vDataset.get(5).read();
                float vAzimuthInterval = (vAzimuth.getFloat(1) - vAzimuth.getFloat(0)) < 0 ?
                        (vAzimuth.getFloat(2) - vAzimuth.getFloat(1)) :
                        (vAzimuth.getFloat(1) - vAzimuth.getFloat(0));
                vAzimuthInterval = (float)Math.round(vAzimuthInterval * 10f) / 10f;
                int vGateInterval = vDataset.get(3).read().getInt(0);

                List<Variable> dpDataset = dpFile.getVariables();
                Array dpAzimuth = dpDataset.get(0).read();
                Array dpData = dpDataset.get(5).read();
                float dpAzimuthInterval = (dpAzimuth.getFloat(1) - dpAzimuth.getFloat(0)) < 0 ?
                        (dpAzimuth.getFloat(2) - dpAzimuth.getFloat(1)) :
                        (dpAzimuth.getFloat(1) - dpAzimuth.getFloat(0));
                dpAzimuthInterval = (float)Math.round(dpAzimuthInterval * 10f) / 10f;
                int dpGateInterval = dpDataset.get(3).read().getInt(0);

                List<Variable> reflDataset = reflFile.getVariables();
                Variable reflDatas = reflFile.findVariable("Reflectivity");
                Array reflAzimuth = reflDataset.get(0).read();
                Array reflData = reflDatas.read();
                float reflAzimuthInterval = (reflAzimuth.getFloat(1) - reflAzimuth.getFloat(0)) < 0 ?
                        (reflAzimuth.getFloat(2) - reflAzimuth.getFloat(1)) :
                        (reflAzimuth.getFloat(1) - reflAzimuth.getFloat(0));
                reflAzimuthInterval = (float)Math.round(reflAzimuthInterval * 10f) / 10f;
                int reflGateInterval = reflDataset.get(3).read().getInt(0);

                List<Variable> qcDataset = qcFile.getVariables();
                Array qcAzimuth = qcDataset.get(0).read();
                Array qcData = qcDataset.get(5).read();
                float qcAzimuthInterval = (qcAzimuth.getFloat(1) - qcAzimuth.getFloat(0)) < 0 ?
                        (qcAzimuth.getFloat(2) - qcAzimuth.getFloat(1)) :
                        (qcAzimuth.getFloat(1) - qcAzimuth.getFloat(0));
                qcAzimuthInterval = (float)Math.round(qcAzimuthInterval * 10f) / 10f;
                int qcGateInterval = qcDataset.get(3).read().getInt(0);

                List<Variable> spectrumDataset = spectrumFile.getVariables();
                Array spectAzimuth = spectrumDataset.get(0).read();
                Array spectData = spectrumDataset.get(5).read();
                float spectAzimuthInterval = (spectAzimuth.getFloat(1) - spectAzimuth.getFloat(0)) < 0 ?
                        (spectAzimuth.getFloat(2) - spectAzimuth.getFloat(1)) :
                        (spectAzimuth.getFloat(1) - spectAzimuth.getFloat(0));
                spectAzimuthInterval = (float)Math.round(spectAzimuthInterval * 10f) / 10f;
                int spectGateInterval = spectrumDataset.get(3).read().getInt(0);

                List<Variable> zdrDataset = zdrFile.getVariables();
                Array zdrAzimuth = zdrDataset.get(0).read();
                Array zdrData = zdrDataset.get(5).read();
                float zdrAzimuthInterval = (zdrAzimuth.getFloat(1) - zdrAzimuth.getFloat(0)) < 0 ?
                        (zdrAzimuth.getFloat(2) - zdrAzimuth.getFloat(1)) :
                        (zdrAzimuth.getFloat(1) - zdrAzimuth.getFloat(0));
                zdrAzimuthInterval = (float)Math.round(zdrAzimuthInterval * 10f) / 10f;
                int zdrGateInterval = zdrDataset.get(3).read().getInt(0);

                fillCoornates(vData, vAzimuthInterval, vGateInterval,
                        dpData, dpAzimuthInterval, dpGateInterval,
                        reflData, reflAzimuthInterval, reflGateInterval,
                        qcData, qcAzimuthInterval, qcGateInterval,
                        spectData, spectAzimuthInterval, spectGateInterval,
                        zdrData, zdrAzimuthInterval, zdrGateInterval,
                        coordinates, eIndex);
                //System.out.println(vDataset.get(1).read().getFloat(0));
                //Array data = vDataset.get(1).read();
                //NCdumpW.printArray(data, "FF",System.out, null);

            } catch (IOException ioe) {
                log("Fail to open", ioe);
            } finally {
                try {
                    if (null != vFile) {
                        vFile.close();
                    }
                    if (null != dpFile) {
                        dpFile.close();
                    }
                    if (null != reflFile) {
                        reflFile.close();
                    }
                    if (null != qcFile) {
                        qcFile.close();
                    }
                    if (null != spectrumFile) {
                        spectrumFile.close();
                    }
                    if (null != zdrFile) {
                        zdrFile.close();
                    }
                } catch (IOException ioe) {
                    log("Fail to close", ioe);
                }
            }
        }
        //System.out.println((System.currentTimeMillis()-s)/1000);
        writeToFile(coordinates);
    }
}
