#!/bin/sh
rm -rf build
mkdir -p build
cd build
cmake ..
make
# make test
cd ..
# ./build/apps/app
# ./build/apps/hello-triangle
# ./build/apps/shader
# ./build/apps/texture-demo
# ./build/apps/transformation
# ./build/apps/6.1.coordinate_systems
./build/apps/camera