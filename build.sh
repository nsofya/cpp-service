#!/bin/sh

rm -rf build
mkdir build
cd build
conan install .. --build=missing --output-folder=.
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_PREFIX_PATH=$(pwd)
cmake --build  .
