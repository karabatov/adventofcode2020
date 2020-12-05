#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

// https://adventofcode.com/2020/day/4#part2

int solve(std::fstream &in) {
  int valid{0};
  std::array<bool, 7> found{};
  const std::array<std::regex, 7> fields{
      std::regex{"byr:(19[2-9][0-9]|200[0-2])"},
      std::regex{"iyr:(201[0-9]|2020)"},
      std::regex{"eyr:(202[0-9]|2030)"},
      std::regex{"hgt:((1[5-8][0-9]|19[0-3])cm|(59|6[0-9]|7[0-6])in)"},
      std::regex{"hcl:#([0-9a-f]){6}"},
      std::regex{"ecl:(amb|blu|brn|gry|grn|hzl|oth)"},
      std::regex{"pid:[0-9]{9}\\b"}};

  std::string line{};
  while (getline(in, line)) {
    if (line.empty()) {
      auto sum{0};
      for (size_t i = 0; i < found.size(); i++) {
        if (found[i]) sum++;
        found[i] = false;
      }
      if (sum == found.size())
        valid++;

      continue;
    }

    for (size_t i = 0; i < fields.size(); i++) {
      found[i] = std::regex_search(line, fields[i]) || found[i];
    }
  }
  return valid;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day4.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
