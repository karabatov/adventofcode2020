#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

// https://adventofcode.com/2020/day/4

enum class Token { Key, Value };

int solve(std::fstream &in) {
  const std::unordered_map<std::string, size_t> keys{
      {"byr", 0}, {"iyr", 1}, {"eyr", 2}, {"hgt", 3},
      {"hcl", 4}, {"ecl", 5}, {"pid", 6}};
  int valid{0};
  std::array<int, 7> fields{};
  char c{0}, prev_c{0};
  std::string key{};
  Token tok{Token::Key};
 
  while (!in.eof()) {
    in.get(c);
    switch (c) {
    case ':': {
      tok = Token::Value;
      if (keys.find(key) != keys.end()) {
        fields[keys.at(key)] = 1;
      }
      break;
    }

    case '\n':
      if (prev_c == '\n') {
        auto sum{0};
        for (size_t i = 0; i < fields.size(); i++) {
          sum += fields[i];
          fields[i] = 0;
        }
        key.clear();
        tok = Token::Key;
        if (sum == fields.size())
          valid++;
      } else {
        tok = Token::Key;
        key.clear();
      }
      break;

    case ' ':
      key.clear();
      tok = Token::Key;
      break;

    default:
      if (tok == Token::Key)
        key.push_back(c);
    }

    prev_c = c;
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
