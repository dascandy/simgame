#!/bin/bash

cpp-dependencies --regen
cd build
cmake -G Ninja ..
ninja
cd ..

