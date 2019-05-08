#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array1, size_t n1);

void run_check(int * array, size_t n, size_t number) {
  if (maxSeq(array, n) != number) {
    exit(EXIT_FAILURE);
  }
  printf("you have passed this test\n");
}

int main() {
  int arr00[] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int arr01[] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
  // int arr1[] = {};
  int arr2[] = {1, 1, 1};
  int arr3[] = {1, 2, 100000000, 3, 1};
  int arr4[] = {5};
  int arr5[] = {5, -2, -3, -4, 2};
  int arr6[] = {1, 1.2, 1.3, 2};
  int arr7[] = {1, 3, 3, 5, 5, 7, -2, 9};
  run_check(arr00, 10, 4);
  run_check(arr01, 14, 2);
  //run_check(arr1, 0, 0);
  run_check(arr2, 3, 1);
  run_check(arr3, 5, 3);
  run_check(arr4, 1, 1);
  run_check(arr5, 5, 2);
  run_check(arr6, 4, 2);
  run_check(arr7, 8, 2);

  exit(EXIT_SUCCESS);
}
