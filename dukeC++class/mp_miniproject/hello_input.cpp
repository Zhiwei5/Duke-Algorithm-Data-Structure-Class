#include <cstdlib>
#include <iostream>
#include <string>
int main(int argc, char * argv[]) {
  std::cout << "argc: " << argc << std::endl;
  std::cout << "hello world" << std::endl;
  std::string input;
  std::cin >> input;
  std::cout << input << std::endl;
  int j;
  for (j = 0; j < argc; j++) {
    std::cout << "argv: " << argv[j] << std::endl;
  }
  exit(EXIT_SUCCESS);
}
