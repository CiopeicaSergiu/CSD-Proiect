#!/bin/bash 
cd ./Client
rm -rf builddir
mkdir builddir
cd builddir
cmake -S .. -B .
make