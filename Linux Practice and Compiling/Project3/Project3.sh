#!/bin/bash

#Author: Daniel Navarro
#Course: CPSC 254

rm *.o*

echo DataAnalysis.c compilation
gcc -c -m64 -Wall -o DataAnalysis.o DataAnalysis.c

echo Get_Data.c compilation
gcc -c -m64 -Wall -o Get_Data.o Get_Data.c

echo ComputeMean.c compilation
gcc -c -m64 -Wall -o ComputeMean.o ComputeMean.c

echo SortArray.c compilation
gcc -c -m64 -Wall -o SortArray.o SortArray.c

echo ComputeMedian.cpp compilation
g++ -c -m64 -Wall -l ComputeMedian.lis -o ComputeMedian.o ComputeMedian.cpp
echo The exit code of ComputeMedian.cpp with g++ is $?

echo ComputeHarmonicMean.cpp compilation
g++ -c -m64 -Wall -l ComputerHarmonicMean.lis -o ComputeHarmonicMean.o ComputeHarmonicMean.cpp
echo The exit code of ComputeHarmonicMean.cpp with g++ is $?

echo Display.cpp compilation
g++ -c -m64 -Wall -l Display.lis -o Display.o Display.cpp
echo The exit code of Display.cpp with g++ is $?

echo Linking the 8 files together
g++ -m64 -o Project3.out DataAnalysis.o Get_Data.o ComputeMean.o SortArray.o ComputeMedian.o ComputeHarmonicMean.o Display.o
echo The exit code of linking 8 objects with g++ is $?

echo Now list the files in this directory
ls -l

echo Now run the .exe file
./Project3.out


