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
    if [[ $OPTARG == BOOST_ROOT* ]] ; then
    arr=( `echo $OPTARG | tr -s '=' ' '`)
    BOOST_ROOT=-DBOOST_ROOT:STRING=${arr[1]}
    fi
    ;;
  esac
done
echo "Cpp Version"
cp CMakeListsCpp.txt CMakeLists.txt
mkdir build
cd build
cmake ${BOOST_ROOT} -DBOOST_LIBRARYDIR=/stage/lib -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ../
cmake --build . --config Release --target install

