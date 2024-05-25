#!/bin/bash

if [ "$1" = "build" ]; then
    echo -e "\033[32m\033[1mBuild Blackhole\033[0m"
    sudo apt install -y libgl1-mesa-dev libglew-dev libxkbcommon-dev libx11-dev libwayland-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev build-essential cmake pkg-config
    git submodule update --init --recursive
    mkdir -p build && cd build
    cmake .. && make -j$(( $(nproc) - 1 ))
    cd ..
elif [ "$1" = "run" ]; then
    echo -e "\033[32m\033[1mRun Blackhole\033[0m"
    ./build/Blackhole
else
    echo "Usage: ./Blackhole [build|run]"
    exit 1
fi