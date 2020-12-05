#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/5#part2

int solve(std::fstream &in) {
  std::vector<int> seats{};
  std::string line{};
  while (getline(in, line)) {
    if (line.size() != 10)
      continue;
    int row{0}, col{0};
    for (size_t i = 0; i < 7; i++) {
      row *= 0b10;
      if (line[i] == 'B')
        row += 0b1;
    }
    for (size_t i = 7; i < line.size(); i++) {
      col *= 0b10;
      if (line[i] == 'R')
        col += 0b1;
    }

    seats.push_back(row * 8 + col);
  }

  std::sort(seats.begin(), seats.end());
  for (size_t i = 1; i < seats.size(); i++) {
    if (seats[i - 1] != seats[i] - 1)
      return seats[i] - 1;
  }
  return 0;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day5.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
