#!/bin/sh
#
# Commands for compiling and linking a GSL test program 
# on Linux using a main C++ program
#
#                              Graham W. Wilson       
#

target=$1
echo 'Running cl.script with target of '${target}

echo 'Compiling C++ code'
g++ -c ${target}.cpp

echo 'Linking C++ code with GSL libraries'
#g++ -o ${target} -L/usr/lib64 ${target}.o -lgsl -lgslcblas -lm
g++ -o ${target} ${target}.o -lgsl -lgslcblas -lm

echo 'Removing unneeded object file'
rm ${target}.o

echo 'Finished Compilation and Linking'

exit
