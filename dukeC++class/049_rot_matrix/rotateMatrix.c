#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "The number of input is not right\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Have problem opening the file\n");
    return EXIT_FAILURE;
  }

  char matrix[10][10];

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = 0;
    }
  }

  // char r_matrix[10][10];
  int row_number = 0;
  int line_size = 12;
  char line[12];

  while (fgets(line, line_size, f) != NULL) {
    // printf("okay for this part\n");
    char * newline_ptr;

    if ((newline_ptr = strchr(line, '\n')) == NULL) {
      fprintf(stderr, "the input is not right");
      return EXIT_FAILURE;
      // continue;
    }

    if (newline_ptr - line != 10) {
      fprintf(stderr, "the input length is not right");
      return EXIT_FAILURE;
    }

    if (row_number > 9) {
      fprintf(stderr, "the input length is not right");
      return EXIT_FAILURE;
    }
    // if (row_number == 11)
    //break;
    for (int i = 0; i < 10; ++i) {
      matrix[i][9 - row_number] = line[i];
    }

    /* for (int i = 0; i < 10; ++i) {
      matrix[row_number][i] = line[i];
      }*/

    row_number++;
  }

  if (row_number != 10) {
    fprintf(stderr, "the input length is not right");
    return EXIT_FAILURE;
  }

  /*for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      r_matrix[j][9 - i] = matrix[i][j];
    }
    }*/

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
