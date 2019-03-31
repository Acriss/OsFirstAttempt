## Clean
rm -rf CMakeFiles
rm cmake_install.cmake
rm CMakeCache.txt

cmake CMakeLists.txt
make
./runTests