#!/bin/bash
# This file is from PyART project, help to build KDTree library in place
# remove and rebuild the ckdtree.so module
rm ckdtree*.so
cython ckdtree.pyx
python setup.py build_ext -i
rm -rf build
