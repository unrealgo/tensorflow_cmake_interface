cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")
project(tensorflowcc-example)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(TensorflowCC_DIR "../build/lib/cmake/TensorflowCC")
option(LINK_SHARED_TENSORFLOW "Link Shared Tensorflow" ON)

message(_targetsDefined=${_targetsDefined})
message(CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR})
message(CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH})
message(CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH})

find_package(TensorflowCC REQUIRED)

message(TensorflowCC=${TensorflowCC})
message(_expectedTargets=${_expectedTargets})
message(INTERFACE_INCLUDE_DIRECTORIES=${INTERFACE_INCLUDE_DIRECTORIES})
message(_DIR=${_DIR})
message(CONFIG_FILES=${CONFIG_FILES})

add_subdirectory(example)
add_subdirectory(tensorflow_test)