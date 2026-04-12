
mkdir build
set -e
BUILD_DIR="build"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..
cmake --build . --parallel 
cd tests
ctest --output-on-failure

mkdir build
set -e  BUILD_DIR="build" 
cd "$BUILD_DIR"   
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_MAIN=ON ..   
cmake --build . --parallel  ./main