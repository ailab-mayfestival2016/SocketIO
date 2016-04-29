@echo off
setlocal

if "%1" == "Debug" (
    set BUILD_TYPE=Debug
) else (
    set BUILD_TYPE=Release
)

echo "Cpp Version BUILD_TYPE=" %BUILD_TYPE%
cp CMakeListsCpp.txt CMakeLists.txt
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=%BUILD_TYPE% ../

cmake --build . --config %BUILD_TYPE% --target install
