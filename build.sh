#!/bin/bash

cpp-dependencies --regen
cd build
cmake -G "Unix Makefiles" ..
make -j8
cd ..

