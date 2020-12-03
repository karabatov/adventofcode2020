#include <fstream>
#include <iostream>
#include <string>

// https://adventofcode.com/2020/day/3

int solve(std::fstream &in) {
  std::string line;
  size_t idx{0};
  int trees{0};
  while (getline(in, line)) {
    if (line[idx] == '#') trees++;
    idx = (idx + 3) % line.size();
  }
  return trees;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day3.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
