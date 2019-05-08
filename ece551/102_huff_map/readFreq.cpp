#include "readFreq.h"

#include <stdio.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream in_file(fname);
  char c;
  uint64_t * array = new uint64_t[257];
  for (int i = 0; i < 257; ++i) {
    array[i] = 0;
  }
  while (in_file.get(c)) {
    unsigned char cc = c;
    array[(int)cc]++;
  }
  array[256]++;
  in_file.close();
  return array;
}
