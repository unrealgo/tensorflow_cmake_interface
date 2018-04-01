#!/bin/bash
set -e

# configure and build
./configure
bazel build -c opt --incompatible_disallow_set_constructor=false tensorflow:libtensorflow_cc.so
bazel shutdown