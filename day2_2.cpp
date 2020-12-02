#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// https://adventofcode.com/2020/day/2

int solve(std::fstream &in) {
  int valid{0};
  std::string line;
  int lo{0}, hi{0};
  char letter{0};
  std::string pass;
  while (getline(in, line)) {
    std::stringstream ss(line);
    ss >> lo;
    ss.ignore(1, '-');
    ss >> hi;
    ss.ignore(1, ' ');
    ss >> letter;
    ss.ignore(1, ':');
    ss.ignore(1, ' ');
    ss >> pass;

    auto a = pass[lo - 1] == letter;
    auto b = pass[hi - 1] == letter;
    if ((a || b) && !(a && b)) valid++;
  }
  return valid;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day2.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << std::endl;
  }
  in_file.close();
}
