mkdir build
cd build

cmake -G "Visual Studio 15 2017" -A "x64" -T "host=x64" ^
    -DCMAKE_TOOLCHAIN_FILE=%CONDA_PREFIX%/h2o.cmake ^
    -DCMAKE_BUILD_TYPE=Release ^
    ../

