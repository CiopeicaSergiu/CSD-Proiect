#!/bin/bash 
cd dependencies/restbed/dependency
env -i git submodule init
env -i git submodule update
cd ..
mkdir build
cd build
cmake [-DBUILD_SSL=NO] [-DBUILD_TESTS=NO] ..
make install
make test