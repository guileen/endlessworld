#!/bin/sh
rm -rf build
mkdir -p build
cd build
cmake ..
make
# make test
# ./apps/app
# ./apps/hello-triangle
cd ..
./build/apps/shader