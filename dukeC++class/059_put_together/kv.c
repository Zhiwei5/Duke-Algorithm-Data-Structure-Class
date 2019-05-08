#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char * start2 = line;
    char * end = NULL;
    if ((end = strchr(line, '=')) == NULL) {
      free(start2);
      continue;
    }
    int length = end - start;
    kvpair_t * new_kvpair_ptr = &(kvarr_ptr->kvpair_arr[pair_number]);
    char * key_ptr = new_kvpair_ptr->key;
    initial_char(&key_ptr, arr_length);
    for (int i = 0; i < length; ++i) {
      new_kvpair_ptr->key[i] = start[i];
    }

    start = end + 1;
    end = strchr(line, '\n');
    char * value_ptr = new_kvpair_ptr->value;
    initial_char(&value_ptr, arr_length);
    length = end - start;
    for (int i = 0; i < length; ++i) {
      new_kvpair_ptr->value[i] = start[i];
    }
    // strcpy(new_kvpair_ptr->value, start);
    // free(line);
    line = NULL;
    free(start2);
    pair_number++;
  }
  free(line);
  kvarr_ptr->length = pair_number;
  fclose(f);
  return kvarr_ptr;
  //free line
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  free(pairs->kvpair_arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t * array = pairs->kvpair_arr;
  for (int i = 0; i < pairs->length; ++i) {
    printf("key = '%s' value = '%s'\n", array[i].key, array[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  kvpair_t * array = pairs->kvpair_arr;
  for (int i = 0; i < pairs->length; ++i) {
    int result = strcmp(array[i].key, key);
    if (result == 0) {
      return array[i].value;
    }
  }
  return NULL;
}
