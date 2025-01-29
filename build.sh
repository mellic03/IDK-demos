#!/bin/bash

mkdir -p build
mkdir -p output/include

cp -R src/flightsim output/include/.
cp -R src/init output/.
cd output/include/
find . -name "*.cpp" -type f -delete
find . -name "CMakeLists.txt" -type f -delete
cd ../../

cd build
cmake cmake -D CMAKE_BUILD_TYPE=DEBUG -D IDK_DEBUG=ON -G Ninja ../
ninja
cd ../


# function build_game()
# {
#     mkdir -p $build_dir 
#     mkdir -p $output_dir/include

#     cp -R src/flightsim $output_dir/include/.
#     cd $output_dir/include/
#     find . -name "*.cpp" -type f -delete
#     find . -name "CMakeLists.txt" -type f -delete
#     cd ../../

#     cd $build_dir
#     # cmake -D CMAKE_BUILD_TYPE=DEBUG -D IDK_DEBUG=ON -G Ninja ../
#     cmake $build_args
#     ninja
#     cd ../
# }


# build_dir="build-debug"
# output_dir="output-debug"
# build_args="-D CMAKE_BUILD_TYPE=DEBUG IDK_DEBUG=ON -G Ninja ../"
# build_game


# # build_dir="build-release"
# # output_dir="output-release"
# # build_args="-D CMAKE_BUILD_TYPE=RELEASE -G Ninja ../"
# # build_game
