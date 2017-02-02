#!/bin/bash

ensure_installed() {
  TO_INSTALL=$(dpkg -s $1 2>/dev/null | grep Status.*installed | wc -l)
  if [ $TO_INSTALL -eq 0 ]; then 
    sudo apt-get install $1
  fi
}

ensure_installed libglfw3-dev
ensure_installed libglm-dev

cpp-dependencies --regen
cd build
cmake -G Ninja ..
ninja
ninja unittests
cd ..

