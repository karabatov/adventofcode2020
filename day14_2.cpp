#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// https://adventofcode.com/2020/day/14#part2

void gen_locations(std::vector<std::string> &locations, std::string mask,
                   size_t idx) {
  if (idx == mask.size()) {
    locations.push_back(mask);
    return;
  }
  if (mask[idx] == 'X') {
    mask[idx] = '1';
    gen_locations(locations, mask, idx + 1);
    mask[idx] = '0';
    gen_locations(locations, mask, idx + 1);
    return;
  }
  gen_locations(locations, mask, idx + 1);
}

uint64_t solve(std::fstream &in) {
  const size_t base{36};
  std::regex r_mask{"^mask = ([X01]{36})$"};
  std::regex r_mem{"^mem\\[(\\d+)\\] = (\\d+)$"};
  std::unordered_map<uint64_t, uint64_t> memory{};
  std::string mask{};
  std::vector<std::string> locations{};
  std::string line{};
  while (getline(in, line)) {
    std::smatch r_match;
    if (std::regex_search(line, r_match, r_mask)) {
      mask = r_match.str(1);
    } else if (std::regex_search(line, r_match, r_mem)) {
      const auto location = std::bitset<base>{std::stoull(r_match.str(1))};
      const auto next = std::stoull(r_match.str(2));

      auto loc_mask = mask;
      for (size_t i = 0; i < base; i++) {
        if (loc_mask[i] == '0') {
          loc_mask[i] = location[base - i - 1] ? '1' : '0';
        }
      }

      locations.clear();
      gen_locations(locations, loc_mask, 0);
      for (const auto &loc : locations) {
        auto new_loc = std::bitset<base>{loc};
        memory[new_loc.to_ullong()] = next;
      }
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
