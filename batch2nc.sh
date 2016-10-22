#!/bin/bash

for x in *.gz
do
	gunzip $x
done

echo "Finish extract!"

for x in `ls`; do 
    if [[ $x =~ ^K ]]; then 
         java -classpath netcdfAll-4.6.6.jar ucar.nc2.dataset.NetcdfDataset -in $x -out $x.nc 
    fi; 
done

echo "Finish data format transfer!"

