#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

// https://adventofcode.com/2020/day/6#part2

int solve(std::fstream &in) {
  int sum{0};
  std::unordered_map<char, int> letters;
  int group_size{0};
  std::string line{};
  while (getline(in, line)) {
    if (line.empty()) {
      sum +=
          std::transform_reduce(letters.begin(), letters.end(), 0, std::plus(),
                                [&group_size](const auto &p) -> int {
                                  return p.second == group_size ? 1 : 0;
                                });
      letters.clear();
      group_size = 0;
      continue;
    }
    for (auto &c : line) {
      letters[c]++;
    }
    group_size++;
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
