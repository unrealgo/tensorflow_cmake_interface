#!/bin/bash

rm -rf include
rm -rf lib

# change tensorflow_source_dir to your tensorflow source dir
cmake -DTENSORFLOW_SHARED=ON -DTENSORFLOW_SOURCE_DIR="tensorflow_source_dir" ..
make
make install
