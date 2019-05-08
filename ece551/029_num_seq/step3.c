// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return -3 * x + (x + 2) * y;
}

void test_seq3(int input_x, int input_y) {
  int result = seq3(input_x, input_y);
  printf("seq3(%d, %d) = %d\n", input_x, input_y, result);
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int even_numbers = 0;
  if (xLow < xHi && yLow < yHi) {  //if xLow>xHi or yLow>yHi, even_number is 0
    int i, j;
    for (i = xLow; i < xHi; i++) {
      for (j = yLow; j < yHi; j++) {
        int temp = seq3(i, j);
        if (temp % 2 == 0)  // decide if temp is a even number
          even_numbers++;
      }
    }
  }
  return even_numbers;
}

void test_countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int result = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, result);
}

int main() {
  //test the seq3 function
  test_seq3(-4, -5);

  test_seq3(0, 0);

  test_seq3(3, -4);

  test_seq3(-2, 3);

  test_seq3(3, 3);

  // test the countEvenInSeq3Range function
  test_countEvenInSeq3Range(0, 2, 0, 3);

  test_countEvenInSeq3Range(0, -1, 0, 3);

  test_countEvenInSeq3Range(0, 1, 0, 5);

  test_countEvenInSeq3Range(1, 2, 0, 3);

  return 0;
}
