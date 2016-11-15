#!/bin/bash
if [ -d /tmp/sampleData ]; then
	sudo rm -rf /tmp/sampleData
fi
sudo mkdir /tmp/sampleData

declare -A stime

#number of elevation
loop=9
folder=(Reflectivity ReflectivityQC AliasedVelocity PhiDP SpectrumWidth Zdr RhoHV)
elevation=(00.50 01.45 02.40 03.35 04.30 06.00 09.90 14.60 19.50)
# start time in different folder
# Reflectivity
stime[0,0]=20121029-000421 
stime[0,1]=20121029-000521 
stime[0,2]=20121029-000622 
stime[0,3]=20121029-000652 
stime[0,4]=20121029-000723 
stime[0,5]=20121029-000754 
stime[0,6]=20121029-000826 
stime[0,7]=20121029-000851 
stime[0,8]=20121029-000916
# ReflectivityQC
stime[1,0]=20121029-000421 
stime[1,1]=20121029-000521 
stime[1,2]=20121029-000622 
stime[1,3]=20121029-000652 
stime[1,4]=20121029-000723 
stime[1,5]=20121029-000754 
stime[1,6]=20121029-000826 
stime[1,7]=20121029-000851 
stime[1,8]=20121029-000916
#AliasedVelocity
stime[2,0]=20121029-000451
stime[2,1]=20121029-000551
stime[2,2]=20121029-000622
stime[2,3]=20121029-000652
stime[2,4]=20121029-000723
stime[2,5]=20121029-000754
stime[2,6]=20121029-000826
stime[2,7]=20121029-000851
stime[2,8]=20121029-000916
#PhiDP
stime[3,0]=20121029-000421
stime[3,1]=20121029-000521
stime[3,2]=20121029-000622
stime[3,3]=20121029-000652
stime[3,4]=20121029-000723
stime[3,5]=20121029-000754
stime[3,6]=20121029-000826
stime[3,7]=20121029-000851
stime[3,8]=20121029-000916
#SpectrumWidth
stime[4,0]=20121029-000451
stime[4,1]=20121029-000551
stime[4,2]=20121029-000622
stime[4,3]=20121029-000652
stime[4,4]=20121029-000723
stime[4,5]=20121029-000754
stime[4,6]=20121029-000826
stime[4,7]=20121029-000851
stime[4,8]=20121029-000916
#Zdr
stime[5,0]=20121029-000421
stime[5,1]=20121029-000521
stime[5,2]=20121029-000622
stime[5,3]=20121029-000652
stime[5,4]=20121029-000723
stime[5,5]=20121029-000754
stime[5,6]=20121029-000826
stime[5,7]=20121029-000851
stime[5,8]=20121029-000916
#RhoHV
stime[6,0]=20121029-000421
stime[6,1]=20121029-000521
stime[6,2]=20121029-000622
stime[6,3]=20121029-000652
stime[6,4]=20121029-000723
stime[6,5]=20121029-000754
stime[6,6]=20121029-000826
stime[6,7]=20121029-000851
stime[6,8]=20121029-000916

for ((j=0; j<6; j++))
do
	folder=${folder[j]}
	for ((i=0; i<$loop; i++))
	do
		e=${elevation[i]}
		t=${stime[$j,$i]}
		sudo ssh -i ~/Downloads/cloud-zh-rsa.txt cloud-zh@ls-heep.geog.ufl.edu  test -e /mnt/distributed/QCTest/KDOX_netcdf/${folder}/${e}/${t}.netcdf.gz
		if [ $? -eq 0 ]; then
			sudo scp -i ~/Downloads/cloud-zh-rsa.txt cloud-zh@ls-heep.geog.ufl.edu:/mnt/distributed/QCTest/KDOX_netcdf/${folder}/${e}/${t}.netcdf.gz /tmp/sampleData
			sudo gunzip /tmp/sampleData/${t}.netcdf.gz
		else
			sudo scp -i ~/Downloads/cloud-zh-rsa.txt cloud-zh@ls-heep.geog.ufl.edu:/mnt/distributed/QCTest/KDOX_netcdf/${folder}/${e}/${t}.netcdf /tmp/sampleData
		fi
		sudo mv /tmp/sampleData/${t}.netcdf /tmp/sampleData/${e}_${folder}_${t}.netcdf    
	done
done
