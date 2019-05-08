// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int input_number) {
  return (-3 + (input_number)*4);
}

void test_seq1(int test_number) {
  int result = seq1(test_number);

  printf("seq1(%d) = %d\n", test_number, result);
}

void printSeq1Range(int low, int high) {
  if (low < high) {
    int i;
    for (i = low; i < high - 1; i++) {  //ensure no extra comma at the end
      int temp = seq1(i);
      printf("%d, ", temp);
    }
    int temp_end = seq1(high - 1);
    printf("%d\n", temp_end);
  }
  else if (low == high) {
    printf("\n");
  }
  else {
    printf("\n%cthat is, a blank line, as there is nothing in the range from %d to %d %c\n",
           '[',
           low,
           high,
           ']');
  }
}

void test_printSeq1Range(int test_low, int test_high) {
  printf("printSeq1Range(%d, %d)\n", test_low, test_high);
  printSeq1Range(test_low, test_high);
}

int main() {
  //Test the seq1 function

  test_seq1(0);

  test_seq1(-3);

  test_seq1(10);

  //test the printSeq1Range function
  test_printSeq1Range(0, 4);

  test_printSeq1Range(0, 0);

  test_printSeq1Range(7, 3);

  test_printSeq1Range(0, 1);

  test_printSeq1Range(-2, 20);

  return 0;
}
