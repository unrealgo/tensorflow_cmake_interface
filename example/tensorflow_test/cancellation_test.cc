/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/framework/cancellation.h"

#include <vector>
#include "tensorflow/core/lib/core/notification.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/platform/test.h"

namespace tensorflow {

TEST(LambdaFunction, lambda2) {
  struct X {
    int x, y;
    X(int _x, int _y) : x(_x), y(_y) {}
    int operator()(int a) {
      return a*a;
    };
    int f()
    {
      // the context of the following lambda is the member function X::f
      return [=]()->int
      {
        return operator()(this->x + y); // X::operator()(this->x + (*this).y)
        // this has type X*
      }();
    }
  };

  X x(1,2);
  std::cout << x.f() << std::endl;
}

TEST(LambdaFunction, lambda3) {
  struct X {
    int x, y;
    X(int _x, int _y) : x(_x), y(_y) {}
    int operator()(int a) {
      return a*a;
    };
    int f()
    {
      // the context of the following lambda is the member function X::f
      return [&]()->int
      {
        x += 9;
        return operator()(this->x + y); // X::operator()(this->x + (*this).y)
        // this has type X*
      }();
    }
  };

  X x(1,2);
  std::cout << x.f() << std::endl;
  std::cout << x.x << std::endl;
}


TEST(LambdaFunction, lambda0) {
  int x = 4;
  auto y = [&r = x, x = x + 3]()->int
  {
    r += 2;
    return x * x;
  }(); // updates ::x to 6 and initializes y to 25.
  std::cout << y << std::endl;
}

TEST(LambdaFunction, lambda) {
  int a = 1, b = 1, c = 1;

  a = a - 20;
  // a function with 3 parameter, 1st by value, 2nd and 3rd by reference
  auto m1 = [a, &b, &c]() mutable {
    a += 3;
    b += 3;
    c += 3 + a;
  };

  a = 2; b = 2; c = 2;

  m1();                             // calls m2() and prints 123
  std::cout << a << " " << b << " " << c << '\n'; // prints 234
}

TEST(LambdaFunction, lambda4) {
  int a = 1, b = 1, c = 1;

  a = 2; b = 2; c = 2;

  // a function with 3 parameter, 1st by value, 2nd and 3rd by reference
  auto m1 = [a, &b, &c]() mutable {
    a += 3;
    b += 3;
    c += 3 + a;
  };

  m1();                             // calls m2() and prints 123
  std::cout << a << " " << b << " " << c << '\n'; // prints 234
}


TEST(Cancellation, SimpleNoCancel) {
  bool is_cancelled = false;
  auto* manager = new CancellationManager();
  auto token = manager->get_cancellation_token();
  bool registered = manager->RegisterCallback(token, [&is_cancelled]() { is_cancelled = true; });
  EXPECT_TRUE(registered);
  bool deregistered = manager->DeregisterCallback(token);
  EXPECT_TRUE(deregistered);
  delete manager;
  EXPECT_FALSE(is_cancelled);
}
}  // namespace tensorflow
