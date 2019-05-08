#include <cstdlib>
#include <iostream>

int main(int argc, char * argv[]) {
  std::cout << "argc: " << argc << std::endl;
  std::cout << "hello world" << std::endl;
  int j;
  for (j = 0; j < argc; j++) {
    std::cout << "argv: " << argv[j] << std::endl;
  }
  exit(EXIT_SUCCESS);
}
