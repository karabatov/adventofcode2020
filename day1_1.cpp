#include <fstream>
#include <iostream>
#include <unordered_map>

// https://adventofcode.com/2020/day/1

int solve(std::fstream &in) {
  int i{0};
  // Store true for 2020 - i.
  std::unordered_map<int, bool> rec;
  while (in >> i) {
    // We already saw N such that 2020 - N == i.
    if (rec[i]) {
      return i * (2020 - i);
    }
    rec[2020 - i] = true;
  }
  return 0;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day1.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << std::endl;
  }
  in_file.close();
}
