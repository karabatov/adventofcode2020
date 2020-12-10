#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/10#part2

int64_t solve(std::fstream &in) {
  std::vector<int> num{0};
  std::string line{};
  while (getline(in, line)) {
    num.push_back(std::stoi(line));
  }
  std::sort(num.begin(), num.end());
  num.push_back(num.back() + 3);

  std::vector<int64_t> sum{1, 1};
  for (int i = 2; i < num.size(); i++) {
    int64_t next{0};
    for (int j = i - 1; j > i - 4 && j >= 0 && num[i] - num[j] < 4; j--) {
      next += sum[j];
    }
    sum.push_back(next);
  }
  return sum.back();
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
