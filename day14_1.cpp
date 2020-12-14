#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>

// https://adventofcode.com/2020/day/14

uint64_t solve(std::fstream &in) {
  const size_t base{36};
  std::regex r_mask{"^mask = ([X01]{36})$"};
  std::regex r_mem{"^mem\\[(\\d+)\\] = (\\d+)$"};
  std::unordered_map<int, uint64_t> memory{};
  std::string mask{};
  std::string line{};
  while (getline(in, line)) {
    std::smatch r_match;
    if (std::regex_search(line, r_match, r_mask)) {
      mask = r_match.str(1);
    } else if (std::regex_search(line, r_match, r_mem)) {
      const auto location = std::stoi(r_match.str(1));
      auto next = std::bitset<base>{std::stoull(r_match.str(2))};
      for (size_t i = 0; i < mask.size(); i++) {
        switch (mask[i]) {
        case '0':
          next.set(base - i - 1, false);
          break;
        case '1':
          next.set(base - i - 1, true);
          break;
        default:
          break;
        }
      }
      memory[location] = next.to_ullong();
    } else {
      throw std::invalid_argument("Unknown command.");
    }
  }
  uint64_t sum{0};
  for (const auto &v : memory) {
    sum += v.second;
  }
  return sum;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day14.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
