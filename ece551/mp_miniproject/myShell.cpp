#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::pair<size_t, size_t> measure_string(
    const std::string & input,
    int int_start) {  // this function is used to parse useful info out of white spaces
  size_t start = int_start;
  while (start < input.size()) {
    if (input.at(start) == ' ')
      start++;
    else
      break;
  }
  size_t end = start;
  while (end < input.size()) {
    if (input.at(end) == ' ')
      break;
    else
      end++;
  }
  return std::pair<size_t, size_t>(start, end);
}

class Input_program
{
  std::string input_string;
  bool do_redir;  // Act as a flag for redirection or not

 public:
  char ** newargv;
  Input_program(std::string & input) : input_string(input), do_redir(false), newargv(NULL) {}
  void create_newargv() {  // This is main parsing function if you want run a excutable in the shell
    std::vector<std::string *> char_vec;
    size_t input_length = input_string.size();
    std::string temp;
    std::pair<size_t, size_t> string_path_loc = measure_string(input_string, 0);
    if (input_string.find(' ', string_path_loc.second - 1) ==
        std::string::npos) {  // check if no arguments are listed
      newargv = new char *[2];
      newargv[0] = NULL;
      newargv[1] = NULL;
      // std::cout << "no arguments" << std::endl;
      return;
    }

    int start = input_string.find(' ', string_path_loc.second - 1);
    int last = 0;
    size_t redir_loc = std::string::npos;
    if (input_string.find('>', string_path_loc.second) != std::string::npos) {
      redir_loc = input_string.find('>', string_path_loc.second);
      do_redir = true;
    }
    else if (input_string.find('<', string_path_loc.second) != std::string::npos) {
      redir_loc = input_string.find('<', string_path_loc.second);
      do_redir = true;
    }

    input_length = std::min(input_length, redir_loc - 1);  // parse until the redirection symbol

    // std::cout << "input_length: " << input_length << std::endl;

    while (start < (int)input_length) {
      if (input_string[start] != '\\' && input_string[start] != ' ') {
        if (start >= 2 && input_string[start - 2] == '\\' && input_string[start - 1] == ' ' &&
            !temp.empty() && last == start - 3) {  // check if while space is escaped with a '\'
          // std::cout << "route b" << std::endl;
          temp += ' ';
          temp += input_string[start];
          last = start;
        }
        else {
          if (!temp.empty() && start - last == 1) {
            temp += input_string[start];
            last = start;
          }
          else if (!temp.empty() && start - last != 1) {
            std::string * temp2 = new std::string(temp);
            // std::cout << "temp2" << *temp2 << std::endl;
            char_vec.push_back(temp2);
            temp.clear();
            temp = input_string[start];
            last = start;
          }
          else if (temp.empty()) {
            // std::cout << "route c" << std::endl;
            temp = input_string[start];
            last = start;
          }
        }
      }
      start++;
    }
    if (char_vec.empty() && temp.empty()) {  // check if no arguments is specified in the command
      newargv = new char *[2];
      newargv[0] = NULL;
      newargv[1] = NULL;
      // std::cout << "no arguments" << std::endl;
      return;
    }
    std::string * temp2 = new std::string(temp);
    char_vec.push_back(temp2);
    newargv = new char *[char_vec.size() + 2];
    newargv[0] = NULL;
    newargv[char_vec.size() + 1] = NULL;
    //std::cout << "size: " << char_vec.size() << std::endl;
    for (size_t i = 0; i < char_vec.size(); ++i) {
      newargv[i + 1] = const_cast<char *>(
          char_vec.at(i)->c_str());  //Add argument into the newargv which has type Char**
    }
  }

  bool get_redir() { return do_redir; }

  ~Input_program() {
    delete[] newargv;
    //  delete newargv;
  }
};

std::pair<int, std::string> parse_redir(
    std::string &
        input_string) {  //This function is to determine the std file descriptor to close and the file to redirect
  std::pair<size_t, size_t> string_path_loc = measure_string(input_string, 0);
  int stream = -1;
  size_t redir_loc = -1;
  if (input_string.find('>', string_path_loc.second) != std::string::npos) {
    redir_loc = input_string.find('>', string_path_loc.second);
    //std::cout << "> is here: " << redir_loc << std::endl;
    if (input_string.at(redir_loc - 1) == '2') {
      stream = 2;
    }
    else {
      stream = 1;
    }
  }
  else {
    redir_loc = input_string.find('<', string_path_loc.second);
    //std::cout << "< is here: " << redir_loc << std::endl;
    stream = 0;
  }
  std::pair<size_t, size_t> file_loc = measure_string(input_string, redir_loc + 1);
  std::string file_name = input_string.substr(file_loc.first, file_loc.second - file_loc.first);
  // std::cout << "file name is: " << file_name << " stream type is: " << stream << std::endl;
  return std::pair<int, std::string>(stream, file_name);
}

bool has_execut(
    const char * directory,
    const char *
        target) {  //This function is to see if a directory has the specified excutable file
  DIR * dir;
  struct dirent * entry;
  if ((dir = opendir(directory)) == NULL)
    perror("opendir() error");
  else {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_type == DT_LNK) {
        continue;
      }
      if (strcmp(entry->d_name, target) == 0) {
        closedir(dir);
        return true;
      }
    }
  }
  closedir(dir);
  return false;
}

void change_dir(const std::string & input) {
  size_t start = 2;
  while (start < input.size()) {
    if (input.at(start) == ' ')
      start++;
    else
      break;
  }
  size_t end = start;
  while (end < input.size()) {
    if (input.at(end) == ' ')
      break;
    else
      end++;
  }
  std::string new_dir = input.substr(start, end - start);
  if (chdir(new_dir.c_str()) != 0) {
    std::cerr << "cd error" << std::endl;
  }
}

void set_variable(const std::string & input,
                  std::unordered_map<std::string, std::string> & hashmap) {
  std::pair<size_t, size_t> key_loc = measure_string(
      input,
      3);  //It start parse from pos 3 is becuase the std::string input is parsed by the function if_other_functions to start with set
  std::string key = input.substr(key_loc.first, key_loc.second - key_loc.first);
  key_loc = measure_string(input, (int)key_loc.second);
  std::string value = input.substr(key_loc.first);
  //std::cout << "key and value " << key << " " << value << std::endl;
  //hashmap[key] = value
  if (hashmap.count(key) > 0) {
    hashmap.at(key) = value;
  }
  else {
    hashmap.emplace(key, value);
  }
}

void export_variable(const std::string & input,
                     std::unordered_map<std::string, std::string> & hashmap) {
  std::pair<size_t, size_t> key_loc = measure_string(input, 6);
  std::string key = input.substr(key_loc.first, key_loc.second - key_loc.first);
  if (hashmap.count(key) == 0) {
    std::cout << "you have not set up the variable" << std::endl;
    return;
  }
  std::string value = hashmap.at(key);
  setenv(key.c_str(), value.c_str(), 1);
  //for testing
  if (key == "test") {
    std::string test_env = getenv("test");
    std::cout << test_env << std::endl;
  }
}

void inc_variable(const std::string & input,
                  std::unordered_map<std::string, std::string> & hashmap) {
  std::pair<size_t, size_t> key_loc = measure_string(input, 3);
  std::string key = input.substr(key_loc.first, key_loc.second - key_loc.first);
  std::string value = hashmap[key];
  bool is_number = true;
  for (size_t i = 0; i < value.size(); ++i) {  // To determine if value is a number
    if (!isdigit(value.at(i))) {
      is_number = false;
      break;
    }
  }
  if (!is_number) {
    value = "0";
  }
  int number = atoi(value.c_str()) + 1;
  std::stringstream ss;
  ss << number;
  hashmap.at(key) = ss.str();
  std::cout << "inc value: " << ss.str() << std::endl;
}

void display_variable(const std::string & input,
                      const std::unordered_map<std::string, std::string> & hashmap) {
  std::string result;
  size_t start = 0;
  size_t end = 0;
  std::string key;
  while (input.find('$', start + 1) !=
         std::string::
             npos) {  // if the input has multiple variable to show then concatenate the results
    end = start;
    start = input.find('$', end + 1);
    key = input.substr(end + 1, start - end - 1);
    if (hashmap.count(key) == 0) {
      std::cout << "you have not set up one of the variables" << std::endl;
      return;
    }
    result += hashmap.at(key);
  }
  key.erase();
  size_t i;
  for (i = start + 1; i < input.size(); ++i) {
    if (isalnum(input.at(i)) || input.at(i) == '_') {
      key += input.at(i);
    }
    else {
      break;
    }
  }
  if (hashmap.count(key) == 0) {
    std::cout << "you have not set up one of the variables" << std::endl;
    return;
  }
  result += hashmap.at(key);
  if (i < input.size())
    result += input.at(i);  // for the case such as $a-
  std::cout << result << std::endl;
}

bool if_other_functions(
    std::string & input,
    std::unordered_map<std::string, std::string> &
        hashmap) {  // this is function act as menu if the user wants to use the functions listed in step3
  std::pair<size_t, size_t> request_loc = measure_string(input, 0);
  std::string request = input.substr(request_loc.first, request_loc.second - request_loc.first);
  if (request.compare("cd") == 0) {
    change_dir(input.substr(request_loc.first));
    return true;
  }
  else if (request.compare("set") == 0) {
    set_variable(input.substr(request_loc.first), hashmap);
    return true;
  }
  else if (request.compare("export") == 0) {
    export_variable(input.substr(request_loc.first), hashmap);
    return true;
  }
  else if (request.compare("inc") == 0) {
    inc_variable(input.substr(request_loc.first), hashmap);
    return true;
  }
  else if (request.compare(0, 1, "$") == 0) {
    display_variable(input.substr(request_loc.first), hashmap);
    return true;
  }
  return false;
}

int main(int argc, char * argv[]) {
  std::unordered_map<std::string, std::string> hashmap;

  while (1) {  // start the shell
    std::string env_path = getenv("PATH");
    // std::cout << "env_path:" << env_path << std::endl;
    char * pwd = get_current_dir_name();
    std::cout << "myShell:" << pwd << " $";
    free(pwd);
    std::string whole_progam;
    std::getline(std::cin, whole_progam);
    if (whole_progam == "exit" || whole_progam.c_str()[0] == std::char_traits<char>::eof()) {
      exit(EXIT_SUCCESS);
    }

    if (if_other_functions(whole_progam, hashmap)) {
      continue;
    }

    std::pair<size_t, size_t> string_path_loc = measure_string(whole_progam, 0);
    std::string program_path = whole_progam.substr(
        string_path_loc.first,
        string_path_loc.second -
            string_path_loc
                .first);  //extract the path of the executable file from the string whole_program

    if (whole_progam.find('/') == std::string::npos) {  //does not have forward slash
      int start = env_path.find(':');
      int end = 0;
      bool has_program = false;
      while ((env_path.find(':', start + 1)) != std::string::npos) {
        end = env_path.find(':', start + 1);
        std::string dir = env_path.substr(start + 1, end - start - 1);
        std::cout << dir << std::endl;
        if (has_execut(dir.c_str(), program_path.c_str())) {
          has_program = true;
          program_path = dir + '/' + program_path;
          break;
        }
        start = end;
      }
      if (!has_program) {
        std::cout << "Command " << program_path << " not found" << std::endl;
        continue;
      }
    }

    //start the fork process
    pid_t cpid, w;
    int status;
    cpid = fork();
    if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (cpid == 0) { /* Code run by child */
      // printf("Child PID is %ld\n", (long)getpid());
      Input_program arguments(whole_progam);
      arguments.create_newargv();
      arguments.newargv[0] = const_cast<char *>(program_path.c_str());
      char * newenviron[] = {NULL};
      if (arguments.get_redir()) {
        std::pair<int, std::string> redir = parse_redir(whole_progam);
        int pfd;
        close(redir.first);
        if (redir.first > 0) {  // redirection for output or std error
          if ((pfd = open(redir.second.c_str(),
                          O_WRONLY | O_CREAT | O_TRUNC,
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
            perror("Cannot open output file\n");
            exit(1);
          }
        }
        else {  // redirection for input
          if ((pfd = open(redir.second.c_str(), O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH)) == -1) {
            perror("Cannot open output file\n");
            exit(1);
          }
        }
        if (dup2(pfd, redir.first) == -1) {
          perror("Cannot dup2 output file\n");
          _exit(1);
        }
      }
      execve(program_path.c_str(), arguments.newargv, newenviron);
      std::cerr << "execve execution error" << std::endl;
      _exit(0);  // if the status is right here
    }
    else { /* Code run by parent */
      do {
        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
        if (w == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
          printf("Program exited with status %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
          printf("Program was killed by signal %d\n", WTERMSIG(status));
        }
        else if (WIFSTOPPED(status)) {
          printf("stopped by signal %d\n", WSTOPSIG(status));
        }
        else if (WIFCONTINUED(status)) {
          printf("continued\n");
        }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
      // exit(EXIT_SUCCESS);
    }
    // std::cout << "one round complete" << std::endl;
  }
}
