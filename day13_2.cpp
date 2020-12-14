#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// From https://raw.githubusercontent.com/sercantutar/infint/master/InfInt.h
#include "inf_int.hpp"

// https://adventofcode.com/2020/day/13#part2

// From
// https://literateprograms.org/extended_euclidean_algorithm__c_plus_plus_.html
void extended_euclidean(InfInt a, InfInt b, InfInt &gcd, InfInt &x, InfInt &y) {
  x = 0, y = 1;
  InfInt u = 1, v = 0, m, n, q, r;
  gcd = b;
  while (a != 0) {
    q = gcd / a;
    r = gcd % a;
    m = x - u * q;
    n = y - v * q;
    gcd = a;
    a = r;
    x = u;
    y = v;
    u = m;
    v = n;
  }
}

InfInt solve(std::fstream &in) {
  std::string line{};
  getline(in, line);
  getline(in, line);
  std::istringstream ss(line);
  std::string bus{};
  std::vector<std::pair<InfInt, InfInt>> buses{};
  size_t idx{0};
  while (getline(ss, bus, ',')) {
    if (bus == "x") {
      idx++;
      continue;
    }
    buses.push_back({idx, std::stoll(bus)});
    idx++;
  }
  for (size_t i = 0; i < buses.size() - 1; i++) {
    auto &b1{buses[i]};
    auto &b2{buses[i + 1]};

    InfInt gcd{0}, x{0}, y{0};
    extended_euclidean(b1.second, b2.second, gcd, x, y);
    InfInt result = b1.first * y * b2.second + b2.first * x * b1.second;
    while (result < 0) {
      result += b1.second * b2.second;
    }
    b2.second *= b1.second;
    b2.first = result % b2.second;
  }
  return buses.back().second - buses.back().first;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day13.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
