@echo off
setlocal
set BUILD_TYPE=Release
rem if "%~1"!="" BUILD_TYPE="~%1"
echo "Cpp Version"
cp CMakeListsCpp.txt CMakeLists.txt
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=%BUILD_TYPE% ../

cmake --build . --config Release --target install
