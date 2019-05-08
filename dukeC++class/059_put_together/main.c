#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "the input file cannot be opened");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  ssize_t line_length = 0;
  counts_t * c = createCounts();

  while ((line_length = getline(&line, &sz, f)) >= 0) {
    char key[string_length];
    strcpy(key, line);
    key[line_length - 1] = '\0';
    char * value = lookupValue(kvPairs, key);
    addCount(c, value);
    char * temp = line;
    line = NULL;
    free(temp);
  }
  free(line);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)

  //count from 2 to argc (call the number you count i)

  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv
  if (argc < 3) {
    fprintf(stderr, "the number of input is not right,please add more");
    exit(EXIT_FAILURE);
  }
  kvarray_t * pairs = NULL;
  pairs = readKVs(argv[1]);
  //  printKVs(pairs);
  for (int i = 2; i < argc; ++i) {
    counts_t * c = NULL;
    c = countFile(argv[i], pairs);
    char * outname = computeOutputFileName(argv[i]);
    FILE * fout = fopen(outname, "w");
    printCounts(c, fout);
    //  fclose(fout);
    free(outname);
    if (c->count_arr != NULL) {
      free(c->count_arr);
    }
    if (c != NULL) {
      free(c);
    }
  }

  if (pairs->kvpair_arr != NULL) {
    free(pairs->kvpair_arr);
  }

  if (pairs != NULL) {
    free(pairs);
  }
  return EXIT_SUCCESS;
}
