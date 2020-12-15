#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

// https://adventofcode.com/2020/day/15#part2

struct Pair {
  int one{-1}, two{-1};

  bool HasBoth() { return one != -1; }
  int Diff() { return two - one; }
  void Push(int num) {
    one = two;
    two = num;
  }
};

int solve(std::fstream &in) {
  const int turn{30000000};
  std::unordered_map<int, Pair> turns;
  std::string line{};
  getline(in, line);
  std::istringstream ss{line};
  std::string num{};
  int idx{0};
  int prev{0};
  while (getline(ss, num, ',')) {
    prev = std::stoi(num);
    turns[prev].Push(idx);
    idx++;
  }
  while (idx < turn) {
    auto &tp1 = turns[prev];
    if (tp1.HasBoth()) {
      prev = tp1.Diff();
    } else {
      prev = 0;
    }

    auto &tp2 = turns[prev];
    tp2.Push(idx);
    idx++;
  }
  return prev;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day15.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
