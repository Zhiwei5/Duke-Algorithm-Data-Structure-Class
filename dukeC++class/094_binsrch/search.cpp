#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //  if (f->invoke(high) < 0) {
  // return high - 1;
  // }
  if (high - low <= 1) {
    if (f->invoke(high) <= 0) {
      return high;
    }
    else {
      return low;
    }
  }
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
