#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// https://adventofcode.com/2020/day/13

int wait_minutes(const int depart, const int bus) {
  return bus - (depart % bus);
}

int solve(std::fstream &in) {
  std::string line{};
  getline(in, line);
  const int depart{std::stoi(line)};
  getline(in, line);
  std::istringstream ss(line);
  std::string bus{};
  int nearest_bus{depart};
  while (getline(ss, bus, ',')) {
    if (bus == "x")
      continue;
    const int next_bus{std::stoi(bus)};
    if (wait_minutes(depart, next_bus) < wait_minutes(depart, nearest_bus)) {
      nearest_bus = next_bus;
    }
  }
  return nearest_bus * wait_minutes(depart, nearest_bus);
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
