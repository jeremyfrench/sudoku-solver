#!/bin/sh
g++ -O2 -pipe -march=armv6j -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard solver.cpp
