#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
//This function will take in array of strings and the length of that array
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void print_free(char ** data, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    printf("%s", data[i]);
    free(data[i]);
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    char ** lines = NULL;
    char * line = NULL;
    size_t sz = 5;
    size_t line_number = 0;
    while (getline(&line, &sz, stdin) >= 0) {
      lines = realloc(lines, (line_number + 1) * sizeof(*lines));
      lines[line_number] = line;
      line = NULL;
      line_number++;
    }
    free(line);
    sortData(lines, line_number);
    print_free(lines, line_number);
    free(lines);

    return EXIT_SUCCESS;
  }

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "cannot open input file");
        return EXIT_FAILURE;
      }
      char ** lines = NULL;
      char * line = NULL;
      size_t sz = 5;
      size_t line_number = 0;
      while (getline(&line, &sz, f) >= 0) {
        lines = realloc(lines, (line_number + 1) * sizeof(*lines));
        lines[line_number] = line;
        line = NULL;
        line_number++;
      }

      free(line);
      sortData(lines, line_number);
      print_free(lines, line_number);
      free(lines);

      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
