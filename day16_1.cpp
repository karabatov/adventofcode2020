#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/16

struct Range {
  int l1, r1, l2, r2;

  Range(int l1, int r1, int l2, int r2) : l1(l1), r1(r1), l2(l2), r2(r2) {}
  bool Has(const int num) const {
    return (l1 <= num && r1 >= num) || (l2 <= num && r2 >= num);
  }
};

int solve(std::fstream &in) {
  const std::regex r_field{"^([a-z ]+): ((\\d+)-(\\d+)) or ((\\d+)-(\\d+))$"};
  std::vector<Range> fields{};
  int error_rate{0};

  std::string line{};
  std::smatch f_match;
  while (getline(in, line)) {
    if (line.empty()) {
      getline(in, line);
      getline(in, line);
      getline(in, line);
      getline(in, line);
    } else if (std::regex_search(line, f_match, r_field)) {
      fields.emplace_back(std::stoi(f_match.str(3)), std::stoi(f_match.str(4)),
                          std::stoi(f_match.str(6)), std::stoi(f_match.str(7)));
    } else {
      std::istringstream ss{line};
      std::string num{};
      while (getline(ss, num, ',')) {
        const auto item = std::stoi(num);
        size_t fail{0};
        for (const auto &r : fields) {
          if (!r.Has(item)) {
            fail++;
          }
        }
        if (fail == fields.size())
          error_rate += item;
      }
    }
  }
  return error_rate;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day16.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
