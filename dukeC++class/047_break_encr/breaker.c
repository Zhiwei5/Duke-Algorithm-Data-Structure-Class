#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int arrayMax(int * array, int n) {
  if (n == 0) {
    printf("The input array is wrong\n");
    return EXIT_FAILURE;
  }
  int i;
  int * large_ptr = array;
  for (i = 0; i < n; i++) {
    if (*large_ptr < array[i]) {
      large_ptr = array + i;
    }
  }
  return large_ptr - array;
}

int find_key(int encrypt_e) {
  int letter_e = 'e' - 'a';
  if (encrypt_e >= letter_e)
    return encrypt_e - letter_e;
  else {
    return ('z' - 'e' + encrypt_e + 1);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "The number of input is not righ\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open the file\n");
    return EXIT_FAILURE;
  }

  int code_arr[26] = {0};
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      // c = tolower(c);
      int letter = c - 'a';
      code_arr[letter]++;
    }
  }

  int letter_e = arrayMax(code_arr, 26);
  int key = find_key(letter_e);

  fprintf(stdout, "%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
