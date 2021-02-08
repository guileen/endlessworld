#!/bin/sh
mkdir -p build
cd build
cmake -Wno-dev --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H/Users/gl/work/endlessworld -B/Users/gl/work/endlessworld/build -G Ninja
cmake --build . --config Debug --target all -- -j 18 && cd .. && ./build/apps/model_loading
# make test
# cd ..
# ./build/apps/app
# ./build/apps/hello-triangle
# ./build/apps/shader
# ./build/apps/texture-demo
# ./build/apps/transformation
# ./build/apps/6.1.coordinate_systems
# ./build/apps/camera
# ./build/apps/lighting