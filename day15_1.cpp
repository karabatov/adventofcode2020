#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/15

int solve(std::fstream &in) {
  const size_t turn{2020};
  std::vector<int> turns{};
  std::string line{};
  getline(in, line);
  std::istringstream ss{line};
  std::string num{};
  while (getline(ss, num, ',')) {
    turns.emplace_back(std::stoi(num));
  }
  for (size_t i = turns.size() - 1; i < turn; i++) {
    const auto found = std::find(turns.rbegin() + 1, turns.rend(), turns[i]);
    if (found == turns.rend()) {
      turns.push_back(0);
    } else {
      const auto idx = turns.rend() - found - 1;
      turns.push_back(i - idx);
    }
  }
  return turns[turn - 1];
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day15.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
