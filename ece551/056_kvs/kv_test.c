#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LOOKUPS 5

/*
void initial_char(char ** chararr, int length) {
  for (int i = 0; i < length; ++i) {
    (*chararr)[i] = '\0';
  }
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "the input file cannot be open");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kvarr_ptr = malloc(sizeof(*kvarr_ptr));
  kvarr_ptr->kvpair_arr = NULL;
  kvarr_ptr->length = 0;

  char * line = NULL;
  size_t sz = 5;
  size_t pair_number = 0;

  while (getline(&line, &sz, f) >= 0) {
    kvarr_ptr->kvpair_arr =
        realloc(kvarr_ptr->kvpair_arr, (pair_number + 1) * sizeof(*(kvarr_ptr->kvpair_arr)));
    char * start = line;
    char * end = NULL;
    if ((end = strchr(line, '=')) == NULL) {
      continue;
    }
    int length = start - end;
    kvpair_t * new_kvpair_ptr = &(kvarr_ptr->kvpair_arr[pair_number]);
    char * key_ptr = new_kvpair_ptr->key;
    initial_char(&key_ptr, arr_length);
    for (int i = 0; i < length; ++i) {
      new_kvpair_ptr->key[i] = start[i];
    }

    start = start + 1;
    char * value_ptr = new_kvpair_ptr->value;
    initial_char(&value_ptr, arr_length);
    strcpy(new_kvpair_ptr->value, start);
    line = NULL;
    pair_number++;
  }
  free(line);
  kvarr_ptr->length = pair_number;
  return kvarr_ptr;
  //free line
  } */

int main(void) {
  kvarray_t * array = readKVs("test.txt");
  printf("Printing all keys\n\n");
  printKVs(array);
  char * tests[NUM_LOOKUPS] = {"banana", "grapes", "cantaloupe", "lettuce", "orange"};
  for (int i = 0; i < NUM_LOOKUPS; i++) {
    printf("lookupValue('%s')=%s\n", tests[i], lookupValue(array, tests[i]));
  }
  freeKVs(array);
  return EXIT_SUCCESS;
}
