// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  if (x >= -1)
    return -1 + (x + 2) * (x + 1);
  return seq2(-x - 3);  //for x<-1 seq2(x) = seq2(-x-3)
}

void test_seq2(int input_x) {
  int result = seq2(input_x);
  printf("seq2(%d) = %d\n", input_x, result);
}

int sumSeq2(int low, int high) {
  int sum = 0;
  if (low < high) {
    int i;
    for (i = low; i < high; i++) {
      sum += seq2(i);
    }
    return sum;
  }
  return sum;  //if low>=high then return 0
}

void test_sumSeq2(int test_low, int test_high) {
  int result = sumSeq2(test_low, test_high);
  printf("sumSeq2(%d, %d) = %d\n", test_low, test_high, result);
}

int main() {
  //test the seq2

  test_seq2(0);

  test_seq2(-1);

  test_seq2(-2);

  test_seq2(-4);

  test_seq2(10);

  // test the test_sumSeq2 function

  test_sumSeq2(0, 2);

  test_sumSeq2(3, 6);

  test_sumSeq2(9, 7);

  test_sumSeq2(0, 0);

  test_sumSeq2(5, 5);

  return 0;
}
