#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/9

bool is_valid(const std::vector<size_t> &v, const size_t preamble,
              const size_t next) {
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

size_t solve(std::fstream &in) {
  const size_t preamble{25};
  std::vector<size_t> num{};
  std::string line{};
  while (getline(in, line)) {
    const auto next = std::stoull(line);
    if (num.size() > preamble) {
      if (!is_valid(num, preamble, next))
        return next;
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
