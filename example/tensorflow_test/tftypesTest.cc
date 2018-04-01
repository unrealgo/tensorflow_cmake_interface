
#include <iostream>
#include <vector>
#include "tensorflow/core/graph/types.h"

#ifndef __cplusplus
extern "C" {
#endif
  int max(int a, int b) {
    return a > b? a:b;
  }

  float max(float a, float b) {
    return a > b? a:b;
  }
#ifndef __cplusplus
}
#endif

int main(int argc, char** argv) {

  tensorflow::Bytes_tag_ tag;
  tensorflow::Bytes bytes;
  bytes += 10000;
  std::cout << sizeof(bytes) << std::endl;
  std::cout << bytes.value() << std::endl;
  std::cout << sizeof(tensorflow::Bytes) << std::endl;
  std::cout << sizeof(tensorflow::Nanoseconds) << std::endl;
  std::cout << sizeof(tensorflow::Microseconds) << std::endl;

  std::cout << +bytes << std::endl;
  std::cout << -bytes << std::endl;

  std::cout << __cplusplus << std::endl;
  std::cout << max(1.0f, 2.f) << std::endl;

  std::vector<std::string> names = {"abc", "test", "gif", "png"};
  return 0;
}