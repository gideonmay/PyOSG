#!/usr/bin/env bash
mkdir -p build
cd build
PYTHON_EXE=/usr/bin/python2
PYTHON_INC_DIR=/usr/include/python2.7
PYTHON_LIB_DIR=/usr/lib/x86_64-linux-gnu/libpython2.7.so
cmake -DPYTHON_EXECUTABLE=${PYTHON_EXE} \
      -DPYTHON_INCLUDE_DIR=${PYTHON_INC_DIR} \
      -DPYTHON_LIBRARY=${PYTHON_LIB_DIR} \
      ..
make
make install
