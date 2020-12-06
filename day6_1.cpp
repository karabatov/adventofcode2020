#include <fstream>
#include <iostream>
#include <set>
#include <string>

// https://adventofcode.com/2020/day/6

int solve(std::fstream &in) {
  int sum{0};
  std::set<char> letters;
  std::string line{};
  while (getline(in, line)) {
    if (line.empty()) {
      sum += letters.size();
      letters.clear();
      continue;
    }
    for (auto& c : line) {
      letters.insert(c);
    }
  }
  return sum;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day6.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
