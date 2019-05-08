/* -*- C++ -*- */
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

void deleteduplicate(const char * directory, unordered_map<size_t, string> & dir_map) {
  DIR * dir;
  struct dirent * entry;

  if ((dir = opendir(directory)) == NULL)
    perror("opendir() error");
  else {
    //cout << "directory is" << directory << endl;
    //unordered_map<size_t, string> dir_map;
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_type == DT_LNK) {
        continue;
      }
      //cout << entry->d_name << endl;
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue;
      }
      string file_name = directory;
      file_name += "/";
      file_name += entry->d_name;
      if (entry->d_type == DT_DIR) {
        const char * new_dir = file_name.c_str();
        deleteduplicate(new_dir, dir_map);
        continue;
      }
      ifstream in_file(file_name.c_str());
      if (!in_file) {
        cerr << "File open error" << endl;
      }
      stringstream ss;
      ss << in_file.rdbuf();

      std::hash<std::string> str_hash;
      size_t key = str_hash(ss.str());
      if (dir_map.count(key) < 1) {
        dir_map.insert(make_pair(key, file_name));
      }
      else {
        cout << "#Removing " << file_name << " (duplicate of " << dir_map[key] << ")." << endl;
        cout << "rm " << file_name << endl;
      }
      in_file.close();
    }
    closedir(dir);
  }
}
int main(int argc, char ** argv) {
  if (argc < 2) {
    std::cout << "Should have more input" << std::endl;
  }
  cout << "#!/bin/bash" << endl;
  unordered_map<size_t, string> dir_map;
  for (int i = 1; i < argc; ++i) {
    deleteduplicate(argv[i], dir_map);
  }
  return EXIT_SUCCESS;
}
