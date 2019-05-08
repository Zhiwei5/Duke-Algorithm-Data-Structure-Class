#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->count_arr = NULL;
  c->length = 0;
  c->number_unknown = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->number_unknown++;
    return;
  }
  else {
    one_count_t * array = c->count_arr;
    for (size_t i = 0; i < c->length; ++i) {
      if ((strcmp(name, array[i].name)) == 0) {
        array[i].number++;
        return;
      }
    }
    c->count_arr = realloc(c->count_arr, (c->length + 1) * sizeof(*(c->count_arr)));
    one_count_t * new_count = &(c->count_arr[c->length]);
    // int name_length = strlen(name);
    for (int i = 0; i < string_length; ++i) {
      new_count->name[i] = '\0';
    }
    strcpy(new_count->name, name);
    // new_count->name[name_length] = '\0';
    new_count->number = 1;
    c->length++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (outFile == NULL) {
    fprintf(stderr, "the outfile cannot be opened");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < c->length; ++i) {
    fprintf(outFile, "%s: %ld\n", (c->count_arr[i]).name, (c->count_arr[i]).number);
  }
  if (c->number_unknown > 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->number_unknown);
  }
  fclose(outFile);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  free(c->count_arr);
  free(c);
}
