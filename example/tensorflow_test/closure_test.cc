#include <iostream>
#include <gtest/gtest.h>

namespace tensorflow {

TEST(LambdaFunction, lambda2) {
  struct X {
    int x, y;
    X(int _x, int _y) : x(_x), y(_y) {}
    int operator()(int a) {
      return a * a;
    };
    int f() {
      // the context of the following lambda is the member function X::f
      return [=]() -> int {
        return operator()(this->x + y); // X::operator()(this->x + (*this).y)
        // this has type X*
      }();
    }
  };

  X x(1, 2);
  std::cout << x.f() << std::endl;
}


TEST(LambdaFunction, lambda3) {
  std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
  int x = 5;
  c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

  std::cout << "c: ";
  std::for_each(c.begin(), c.end(), [&](int i){ std::cout << i << ' '; });
  std::cout << '\n';
}

}