#!/bin/bash 
mkdir dependencies/yaml/build
cd dependencies/yaml/build
cmake -S .. -B .
make
