#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

// https://adventofcode.com/2020/day/1#part2

int solve(std::fstream &in) {
  int i{0};
  // Array of previous 2020 - N.
  std::vector<int> rec1;
  // For each new M, store (2020 - N - M) -> (2020 - N).
  std::unordered_map<int, int> rec2;
  while (in >> i) {
    for (auto k : rec1) {
      if (k - i <= 0) continue;
      // i is (2020 - N - M) for current (2020 - N).
      if (rec2[i] == k) {
        return (2020 - k) * (k - i) * i;
      }
      rec2[k - i] = k;
    }
    rec1.emplace_back(2020 - i);
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
