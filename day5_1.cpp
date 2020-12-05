#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

// https://adventofcode.com/2020/day/5

int solve(std::fstream &in) {
  int max_id{0};
  std::string line{};
  while (getline(in, line)) {
    if (line.size() != 10)
      continue;
    int row{0}, col{0};
    for (size_t i = 0; i < 7; i++) {
      row *= 0b10;
      if (line[i] == 'B') row += 0b1;
    }
    for (size_t i = 7; i < line.size(); i++) {
      col *= 0b10;
      if (line[i] == 'R') col += 0b1;
    }

    max_id = std::max(row * 8 + col, max_id);
  }
  return max_id;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day5.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
