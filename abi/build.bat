mkdir build
cd build

pushd %VS2017INSTALLDIR%
call VC\Auxiliary\Build\vcvars64.bat
popd

cmake -GNinja ../

ninja
