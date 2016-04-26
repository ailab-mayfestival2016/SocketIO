#!/bin/bash
BUILD_TYPE=Release
while getopts D: OPT
do
  case $OPT in
    "D" ) 
    if [[ $OPTARG == CMAKE_BUILD_TYPE* ]] ; then
    arr=( `echo $OPTARG | tr -s '=' ' '`)
    BUILD_TYPE=${arr[1]}
    fi
    ;;
  esac
done
echo "Python Version"
cp CMakeListsPython.txt CMakeLists.txt
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ../
cmake --build . --config Release --target install
cd ../Python
mv libsioclientCpp.so sioclientCpp.so
if test -f libsioclientCpp_tls.so; then
mv libsioclientCpp_tls.so sioclientCpp_tls.so
fi
