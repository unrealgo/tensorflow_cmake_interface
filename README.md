# tensorflow_cmake_interface
This repository makes possible the usage of the [TensorFlow C++](https://www.tensorflow.org/api_docs/cc/) library from the outside of the TensorFlow source code folders and without the use of the [Bazel](https://bazel.build/) build system.

This repository contains two CMake projects. The [tensorflow_cmake_interface](tensorflow_cmake_interface) project downloads, builds and installs the TensorFlow C++ library into the operating system and the [example](example) project demonstrates its simple usage.

## Installation

#### 1) Install requirements

##### Ubuntu 16.04+:
```
# On Ubuntu 16.04, add ubuntu-toolchain-r PPA (for g++-6)
# sudo apt-get install software-properties-common
# sudo add-apt-repository ppa:ubuntu-toolchain-r/test
# sudo apt-get update

sudo apt-get install build-essential curl git cmake unzip autoconf autogen libtool mlocate zlib1g-dev \
                     g++-6 python python3-numpy python3-dev python3-pip python3-wheel wget
sudo updatedb
```

If you require GPU support on Ubuntu, please also install [Bazel](https://bazel.build/), NVIDIA CUDA Toolkit, NVIDIA drivers, cuDNN, and `libcupti-dev` package. The tensorflow build script will automatically detect CUDA if it is installed in `/opt/cuda` or `/usr/local/cuda` directories.

##### Arch Linux:
```
sudo pacman -S base-devel cmake git unzip mlocate python python-numpy wget
sudo updatedb
```

For GPU support on Arch, also install the following:

```
sudo pacman -S gcc6 bazel cuda cudnn nvidia
```

#### 2) Clone this repository
```
git clone https://github.com/unrealgo/tensorflow_cmake_interface.git
cd tensorflow_cmake_interface
```

#### 3) Build and install the library

```
$ mkdir build
$ cd build
# setup tensorflow source
$ export tensorflow_source_dir="your tensorflow source dir"
$ cmake -DTENSORFLOW_SHARED=ON -DTENSORFLOW_SOURCE_DIR="${tensorflow_source_dir}" ..
$ make
$ make install
```

#### 4) (Optional) Free disk space

```
# cleanup bazel build directory
rm -rf ~/.cache
# remove the build folder
cd .. && rm -rf build
```

## Usage

#### 1) Write your C++ code:
```C++
// example.cpp

#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>
#include <iostream>
using namespace std;
using namespace tensorflow;

int main()
{
    Session* session;
    Status status = NewSession(SessionOptions(), &session);
    if (!status.ok()) {
        cout << status.ToString() << "\n";
        return 1;
    }
    cout << "Session successfully created.\n";
}
```

#### 2) Link TensorflowCC to your program using CMake
```
set(TensorflowCC_DIR "tensorflow_cmake_interface/build/lib/cmake/TensorflowCC")
find_package(TensorflowCC REQUIRED)

add_executable(example example.cpp)
# link the shared Tensorflow library
target_link_libraries(example TensorflowCC::Shared)
```

#### 3) Build and run your program
```
mkdir build && cd build
cmake .. && make
./example 
```
