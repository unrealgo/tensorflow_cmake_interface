
#include <iostream>
#include <vector>
#include <map>
#include "gtest/gtest.h"

TEST(TF_TEST, String) {
  std::string str = "obfs";
  str[2] = 'g';
  EXPECT_STREQ(str.c_str(), "obgs");
}