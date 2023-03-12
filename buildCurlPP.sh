#!/bin/bash 
cd ./dependencies/curlpp-0.8.1
mkdir builddir
cd builddir
cmake -S .. -B .
make
