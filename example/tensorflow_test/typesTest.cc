
#include <iostream>
#include "types.h"

struct Uncopyable {
 public:
  Uncopyable() : data(nullptr), len(0) {}
  Uncopyable(const Uncopyable&& right) {};
  // Uncopyable(const Uncopyable& right) {};

  size_t getLen() const {
    return len;
  }
  void setLen(size_t len) {
    Uncopyable::len = len;
  }

 private:
  void* data;
  std::size_t len;

  // Uncopyable(const Uncopyable& right) = delete;
  void operator=(const Uncopyable& right) = delete;
};

template <typename Type>
int compare(Type x, Type y) {
  std::cout << "calling default template function" << std::endl;
  if (x < y)
    return -1;
  if (x == y)
    return 0;
  return 1;
}

template<>
int compare<double>(double x, double y) {
  if (x < y)
    return -1;
  if (x == y)
    return 0;
  return 1;
}

int main(int argc, char** argv) {
  std::cout << IsValidDataType<int>::value << std::endl;
  std::cout << IsValidDataType<bool>::value << std::endl;
  std::cout << IsValidDataType<std::string>::value << std::endl;

  std::cout << compare(10.0, 10.0000000001) << std::endl;
  std::cout << compare<double>(10, 10) << std::endl;
  // std::cout << compare<int>(10, 10) << std::endl;

  Uncopyable a;
  Uncopyable b;
  // Uncopyable b = a;
  std::cout << a.getLen() << std::endl;
  return 0;
}