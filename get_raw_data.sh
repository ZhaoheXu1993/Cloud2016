#!/bin/bash

##### arguments

##### function

cd ~/Downloads
sudo rm -rf rawData
sudo mkdir rawData

if [ "$1" != "cloud-zh-rsa.txt" ]; then
	echo "Wrong key" $1
	echo "Please provide right key"
	exit 0
fi

if [ "$2" != "cloud-zh" ]; then
	echo "Wrong user name" $2
	echo "Please provide right user name"
	exit 0
fi

sudo chmod 777 $1
sudo scp -i $1 $2@ls-heep.geog.ufl.edu:/mnt/distributed/QCTest/KDOX/*.gz ./rawData/
