#!/bin/bash

set -e

ensure_installed() {
  TO_INSTALL=$(dpkg -s $1 2>/dev/null | grep Status.*installed | wc -l)
  if [ $TO_INSTALL -eq 0 ]; then 
    sudo apt-get install $1
  fi
}

ensure_installed libglfw3-dev
ensure_installed libglm-dev
ensure_installed libbullet-dev

cpp-dependencies --regen
mkdir -p build
cd build
cmake -G Ninja ..
ninja all unittests
cd ..

