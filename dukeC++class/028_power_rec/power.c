#include <stdio.h>
#include <stdlib.h>

unsigned power_help(unsigned x, unsigned y, unsigned answer) {
  if (y == 0)
    return answer;
  return power_help(x, y - 1, x * answer);
}

unsigned power(unsigned x, unsigned y) {
  return power_help(x, y, 1);
}
