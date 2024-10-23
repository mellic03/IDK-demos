#!/bin/bash

mkdir -p build
mkdir -p output


cd build
cmake -D CMAKE_BUILD_TYPE=DEBUG -D IDK_DEBUG=ON -G Ninja ../
ninja


# cd ../../../
# rm -R ./MEATWORLD/meatworldgame/src/shaders/include
# cp -R ./IDKGraphics/IDKGE/shaders/include ./MEATWORLD/meatworldgame/src/shaders/include

# cd ./build
# mkdir -p ./debug/IDKGE/runtime/modules
# cp ./lib/debug/*.so ./debug/IDKGE/runtime/.
# mv ./debug/IDKGE/runtime/libIDKBuiltin* ./debug/IDKGE/runtime/modules/.
# mv ./debug/IDKGE/runtime/libgame* ./debug/.


# mkdir -p ./release/IDKGE/runtime/modules
# cp ./lib/release/*.so ./release/IDKGE/runtime/.
# mv ./release/IDKGE/runtime/libIDKBuiltin* ./release/IDKGE/runtime/modules/.
# mv ./release/IDKGE/runtime/libgame* ./release/.
