set -e
 
BUILD_DIR="build"
cd "$BUILD_DIR"
 
echo "Configuring project..."
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_MAIN=ON ..
 
echo "Building project..."
cmake --build . --parallel
 
./main