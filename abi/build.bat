mkdir build
cd build

cmake -G "Visual Studio 16 2019" -A x64 -T host=x64 ../
if errorlevel 1 exit 1

cmake --build . --target ALL_BUILD --config Release
if errorlevel 1 exit 1
