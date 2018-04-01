
#include <iostream>
#include "inlined_vector.h"

void inlinedString() {
  tensorflow::gtl::InlinedVector<std::string, 4> strVec;
  int sizeAligned = ((4 * sizeof(std::string) + 1 + 15) / 16)*16; // = (4*sizeof(T)/16 + 1)*16 = (8+1)*16 = 144
  std::cout << sizeof(std::string) << std::endl;
  std::cout << strVec.kSizeUnaligned << std::endl;
  std::cout << strVec.kSize << std::endl;
  std::cout << strVec.kSentinel << std::endl;

  std::cout << strVec.outofline_pointer() << std::endl;
  std::cout << reinterpret_cast<std::string*>(strVec.u_.data) << std::endl;

  std::cout << "isInline:" << strVec.is_inline() << std::endl;
  strVec.emplace_back("as");
  std::cout << &strVec[0] << std::endl;
  strVec.emplace_back("as");
  strVec.emplace_back("as");
  strVec.emplace_back("as");
  strVec.emplace_back("as");
  strVec.emplace_back("as");
  strVec.emplace_back("as");
  std::cout << "isInline:" << strVec.is_inline() << std::endl;
  std::cout << &strVec[0] << std::endl;

  std::cout << !std::is_trivially_destructible<char>::value << std::endl;
  std::cout << !std::is_trivially_destructible<bool>::value << std::endl;
  std::cout << !std::is_trivially_destructible<int>::value << std::endl;
  std::cout << !std::is_trivially_destructible<std::string>::value << std::endl;
}

#include <tensorflow/core/framework/types.h>
int main(int agrc, char** argv) {
  inlinedString();

  std::cout << "test valid:" << std::endl;
  std::cout << tensorflow::IsValidDataType<float>::value << std::endl;
  std::cout << tensorflow::IsValidDataType<std::string>::value << std::endl;
  std::cout << tensorflow::IsValidDataType<std::vector<int>>::value << std::endl;
  return 0;
}