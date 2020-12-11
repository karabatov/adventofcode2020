#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/11#part2

bool find_first(std::vector<bool> &mem, std::vector<bool> &floor, int from,
                std::function<int(int)> next, std::function<bool(int)> cond) {
  int it = next(from);
  while (cond(it)) {
    if (floor[it]) {
      it = next(it);
      continue;
    }
    return mem[it];
  }
  return false;
}

constexpr bool first(int i, int row) { return i % row == 0; }

constexpr bool last(int i, int row) { return (i + 1) % row == 0; }

int solve(std::fstream &in) {
  std::array<std::vector<bool>, 3> mem{};
  size_t cur{0};
  size_t next{1};
  int row{0};
  std::string line{};
  while (getline(in, line)) {
    row = line.size();
    for (const auto &c : line) {
      mem[cur].push_back(false);
      mem[next].push_back(false);
      mem[2].push_back(c == '.');
    }
  }
  std::array<bool, 8> adj{};
  do {
    for (int i = 0; i < mem[cur].size(); i++) {
      if (mem[2][i])
        continue;

      const auto size = mem[cur].size();
      adj[0] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p - row - 1; },
          [&](int p) { return !first(i, row) && p >= 0 && !last(p, row); });
      adj[1] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p - row; },
          [&](int p) { return p >= 0; });
      adj[2] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p - row + 1; },
          [&](int p) { return !last(i, row) && p >= 0 && !first(p, row); });
      adj[3] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p - 1; },
          [&](int p) { return !first(i, row) && p >= 0 && !last(p, row); });
      adj[4] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p + 1; },
          [&](int p) { return !last(i, row) && p < size && !first(p, row); });
      adj[5] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p + row - 1; },
          [&](int p) { return !first(i, row) && p < size && !last(p, row); });
      adj[6] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p + row; },
          [&](int p) { return p < size; });
      adj[7] = find_first(
          mem[cur], mem[2], i, [&](int p) { return p + row + 1; },
          [&](int p) { return !last(i, row) && p < size && !first(p, row); });

      const auto count = std::count(adj.begin(), adj.end(), true);
      if (!mem[cur][i] && count == 0) {
        mem[next][i] = true;
      } else if (mem[cur][i] && count >= 5) {
        mem[next][i] = false;
      } else {
        mem[next][i] = mem[cur][i];
      }
    }

    cur = 1 - cur;
    next = 1 - next;
  } while (mem[cur] != mem[next]);
  return std::count(mem[cur].begin(), mem[cur].end(), true);
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day11.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
