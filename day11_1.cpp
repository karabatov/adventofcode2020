#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/11

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

      const auto first = i % row == 0;
      const auto last = (i + 1) % row == 0;
      adj[0] = !first && i - row - 1 >= 0 ? mem[cur][i - row - 1] : false;
      adj[1] = i - row >= 0 ? mem[cur][i - row] : false;
      adj[2] = !last && i - row + 1 >= 0 ? mem[cur][i - row + 1] : false;
      adj[3] = !first && i - 1 >= 0 ? mem[cur][i - 1] : false;
      adj[4] = !last && i + 1 < mem[cur].size() ? mem[cur][i + 1] : false;
      adj[5] = !first && i + row - 1 < mem[cur].size() ? mem[cur][i + row - 1]
                                                       : false;
      adj[6] = i + row < mem[cur].size() ? mem[cur][i + row] : false;
      adj[7] = !last && i + row + 1 < mem[cur].size() ? mem[cur][i + row + 1]
                                                      : false;

      const auto count = std::count(adj.begin(), adj.end(), true);
      if (!mem[cur][i] && count == 0) {
        mem[next][i] = true;
      } else if (mem[cur][i] && count >= 4) {
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
