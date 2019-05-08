#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class XFunction : public Function<int, int>
{
 public:
  virtual int invoke(int x) { return x; }
  virtual ~XFunction() {}
};

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //  if (f->invoke(high) < 0) {
  //return high - 1;
  // }
  int mid = low + (high - low) / 2;
  while (low != mid) {
    int mid_ans = f->invoke(mid);
    if (mid_ans == 0) {
      return mid_ans;
    }
    else if (mid_ans > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
    mid = low + (high - low) / 2;
  }
  return low;
}

void check(Function<int, int> * fn, int low, int high, int expected_ans, const char * mesg) {
  if (high > low) {
    int max = (int)log2(high - 2) + 1;
    Function<int, int> * f = new CountedIntFn(max, fn, mesg);
    int result = binarySearchForZero(f, low, high);
    assert(result == expected_ans);
    delete f;
  }
  else {
    int max = 1;
    Function<int, int> * f = new CountedIntFn(max, fn, mesg);
    int result = binarySearchForZero(f, low, high);
    assert(result == expected_ans);
    delete f;
  }
}

int main() {
  Function<int, int> * sinfunc_ptr = new SinFunction();
  check(sinfunc_ptr, 0, 150000, 52359, "sinc_function");
  Function<int, int> * xfunction_ptr = new XFunction();
  check(xfunction_ptr, -20, 180, 0, "normal test");
  // check(xfunction_ptr, 2, -2, 2, "low>high test");
  check(xfunction_ptr, -300000, -10, -11, "negative test");
  check(xfunction_ptr, 100, 15000, 100, "positive test");
  check(xfunction_ptr, -20, 180, 0, "normal test");
  //  check(xfunction_ptr, 2, -2, 2, "low>high test");
  check(xfunction_ptr, -1, 4, 0, "linear func test");
  delete sinfunc_ptr;
  delete xfunction_ptr;
  return EXIT_SUCCESS;
}
