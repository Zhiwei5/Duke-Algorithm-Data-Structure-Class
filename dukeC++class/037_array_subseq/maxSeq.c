#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0)
    return 0;
  size_t long_seq = 1;
  size_t final_re = 1;
  size_t i;
  for (i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      ++long_seq;
      if (long_seq > final_re) {
        final_re = long_seq;
      }
    }
    if (array[i] >= array[i + 1]) {
      long_seq = 1;
    }
  }
  return final_re;
}
