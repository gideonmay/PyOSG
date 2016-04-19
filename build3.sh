#!/usr/bin/env bash
mkdir -p build
cd build
cmake -DUSE_PYTHON=3 -DPYTHON_LIBRARY=$(python-config --prefix)/lib/libpython3.5.dylib -DPYTHON_INCLUDE_DIR=$(python-config --prefix)/include/python3.5m ..
make
make install
