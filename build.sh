#!/usr/bin/env bash
mkdir -p build
cd build
PYTHON_EXE=/usr/local/bin/python2
PYTHON_DIR=/usr/local/Frameworks/Python.framework/Versions/2.7
PYTHON_INC_DIR=$PYTHON_DIR/include/python2.7
PYTHON_LIB_DIR=$PYTHON_DIR/lib/libpython2.7.dylib
cmake -DPYTHON_EXECUTABLE=$PYTHON_EXE \
      -DPYTHON_INCLUDE_DIR=$PYTHON_INC_DIR \
      -DPYTHON_LIBRARY=$PYTHON_LIB_DIR \
      ..
make
make install
