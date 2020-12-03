#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

// https://adventofcode.com/2020/day/3#part2

struct Slope {
  int h_step, v_step;
  size_t h_idx{0}, v_idx{0};
  int trees{0};
};

std::int64_t solve(std::fstream &in) {
  std::array<Slope, 5> slopes{Slope{1, 1}, Slope{3, 1}, Slope{5, 1},
                              Slope{7, 1}, Slope{1, 2}};
  int num_lines{0};
  std::string line;
  while (getline(in, line)) {
    for (auto &s : slopes) {
      if (num_lines != s.v_idx)
        continue;
      if (line[s.h_idx] == '#') {
        s.trees++;
      }
      s.v_idx += s.v_step;
      s.h_idx = (s.h_idx + s.h_step) % line.size();
    }
    num_lines++;
  }
  return std::transform_reduce(slopes.begin(), slopes.end(), 1ll,
                               std::multiplies(),
                               [](Slope s) -> std::int64_t { return s.trees; });
}

int main() {
  std::fstream in_file;
  in_file.open("input/day3.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
