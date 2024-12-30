#!/bin/bash

mkdir -p build
mkdir -p output
mkdir -p output/include

cd build
cmake -D CMAKE_BUILD_TYPE=DEBUG -D IDK_DEBUG=ON -G Ninja ../
ninja

cd ../
# cp -R external/libidk/src/. output/include/.
# cp -R external/IDKGraphics/src/. output/include/.
# cp -R external/IDKGameEngine/src/. output/include/.
cp -R src/demo-common output/include/.
cp -R src/watercraft output/include/.

# cd output/include/
# find . -name "*.cpp" -type f -delete
# find . -name "*.txt" -type f -delete