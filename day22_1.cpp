#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>

// https://adventofcode.com/2020/day/22

uint64_t solve(std::fstream &in) {
  std::deque<uint64_t> p1{};
  std::deque<uint64_t> p2{};
  bool use2{false};

  std::string line{};
  getline(in, line);
  while (getline(in, line)) {
    if (line.empty()) {
      use2 = true;
      getline(in, line);
      continue;
    }

    auto &q = use2 ? p2 : p1;
    q.push_back(std::stoull(line));
  }

  while (p1.size() > 0 && p2.size() > 0) {
    if (p1.front() > p2.front()) {
      p1.push_back(p1.front());
      p1.push_back(p2.front());
    } else {
      p2.push_back(p2.front());
      p2.push_back(p1.front());
    }
    p1.pop_front();
    p2.pop_front();
  }

  uint64_t score{0};
  uint64_t coeff{1};
  auto &q = p1.empty() ? p2 : p1;
  while (q.size() > 0) {
    score += coeff * q.back();
    coeff++;
    q.pop_back();
  }
  return score;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day22.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
