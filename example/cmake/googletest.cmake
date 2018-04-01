# Copyright 2017 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
include (ExternalProject)

if(WIN32)
  set(googletest_STATIC_LIBRARIES
      ${CMAKE_CURRENT_BINARY_DIR}/googletest/src/googletest/googletest/$(Configuration)/gtest.lib)
else()
  set(googletest_STATIC_LIBRARIES
      ${CMAKE_CURRENT_BINARY_DIR}/googletest/src/googletest/googletest/${CMAKE_BUILD_TYPE}/gtest.a)
endif()

ExternalProject_Add(googletest
    PREFIX googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "ec44c6c1675c25b9827aacd08c02433cccde7780"
    DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
    #SOURCE_DIR "googletest"
    BUILD_IN_SOURCE 1
    #PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/patches/grpc/CMakeLists.txt ${GRPC_BUILD}
    INSTALL_COMMAND ""
    CMAKE_CACHE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=Release
        -DBUILD_GMOCK:BOOL=OFF
        -DBUILD_GTEST:BOOL=ON
        -Dgtest_force_shared_crt:BOOL=ON
)
