#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_vec(std::vector<std::string> & vec) {
  std::vector<std::string>::iterator it = vec.begin();
  while (it != vec.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string line;
    std::vector<std::string> vec;
    while (std::getline(std::cin, line)) {
      if (line.length() == 0) {
        continue;
      }
      vec.push_back(line);
    }
    std::sort(vec.begin(), vec.end());
    print_vec(vec);
  }

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      const char * file_name = argv[i];
      std::ifstream in_file;
      in_file.open(file_name, std::ios::in);
      if (!in_file) {
        std::cerr << "cannot open the file" << std::endl;
        return EXIT_FAILURE;
      }
      std::string line;
      std::vector<std::string> vec;
      while (std::getline(in_file, line)) {
        if (line.length() == 0) {
          continue;
        }
        vec.push_back(line);
      }
      std::sort(vec.begin(), vec.end());
      print_vec(vec);
      in_file.close();
    }
  }
  return EXIT_SUCCESS;
}
