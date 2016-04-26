@echo off
setlocal
set BUILD_TYPE=Release
rem if "%~1"!="" set BUILD_TYPE=%1
echo "Python Version"
cp CMakeListsPython.txt CMakeLists.txt
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=%BUILD_TYPE% ../
cmake --build . --config Release --target install

cd ../Python
if exist sioclientCpp.dll (
move /y sioclientCpp.dll sioclientCpp.pyd
del sioclientCpp.lib
)
if exist sioclient_tlsCpp.dll (
move /y sioclient_tlsCpp.dll sioclient_tlsCpp.pyd
//del sioclient_tlsCpp.lib
)
