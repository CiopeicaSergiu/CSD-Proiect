#!/bin/bash 
rm -rf builddir
mkdir builddir
cmake -S . -B ./builddir
cd ./builddir
make