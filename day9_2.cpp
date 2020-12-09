#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/9#part2

bool is_valid(const std::vector<size_t> &v, const int preamble,
              const int next) {
  for (size_t i = v.size() - preamble; i < v.size(); i++) {
    for (size_t j = v.size() - preamble; j < v.size(); j++) {
      if (i == j)
        continue;
      if (v[i] + v[j] == next)
        return true;
    }
  }
  return false;
}

size_t find_adjacent(const std::vector<size_t> &v, const int next) {
  for (size_t i = 0; i < v.size(); i++) {
    size_t sum{0};
    for (size_t j = i; j < v.size(); j++) {
      sum += v[j];
      if (sum > next)
        break;
      if (sum == next)
        return *std::min_element(v.begin() + i, v.begin() + j + 1) +
               *std::max_element(v.begin() + i, v.begin() + j + 1);
    }
  }
  return 0;
}

size_t solve(std::fstream &in) {
  const size_t preamble{25};
  std::vector<size_t> num{};
  std::string line{};
  while (getline(in, line)) {
    const auto next = std::stoi(line);
    if (num.size() > preamble) {
      if (!is_valid(num, preamble, next))
        return find_adjacent(num, next);
    }
    num.push_back(next);
  }
  return 0;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day9.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
