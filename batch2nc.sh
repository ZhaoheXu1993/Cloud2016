#!/bin/bash

cd ~/Downloads/rawData

for x in *.gz
do
	sudo gunzip $x
done

echo "Finish extract!"

for x in `ls`; do 
    if [[ $x =~ ^K ]]; then 
        sudo java -classpath ~/Downloads/toolsUI-4.6.6.jar ucar.nc2.dataset.NetcdfDataset -in $x -out $x.nc 
    fi; 
done

echo "Finish data format transfer!"

