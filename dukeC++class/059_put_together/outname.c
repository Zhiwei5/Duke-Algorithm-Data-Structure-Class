#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  int length = strlen(inputName) + strlen(suffix) + 1;
  char * output = malloc(length * sizeof(*output));
  strcpy(output, inputName);
  strcat(output, suffix);
  output[length - 1] = '\0';
  return output;
}
