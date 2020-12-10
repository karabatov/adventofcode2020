#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

// https://adventofcode.com/2020/day/10

int solve(std::fstream &in) {
  std::vector<int> num{0};
  std::string line{};
  while (getline(in, line)) {
    num.push_back(std::stoi(line));
  }
  std::sort(num.begin(), num.end());
  num.push_back(num.back() + 3);

  std::adjacent_difference(num.begin(), num.end(), num.begin());
  std::unordered_map<int, int> diffs;
  for (auto &v : num) {
    diffs[v]++;
  }

  return diffs[1] * diffs[3];
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day10.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
