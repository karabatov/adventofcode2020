#include <chrono>
#include <execution>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// https://adventofcode.com/2020/day/17#part2

struct Cube {
  int x, y, z, w;
  bool active{false};
};

using Space = std::vector<Cube>;
using Map = std::unordered_map<
    int, std::unordered_map<
             int, std::unordered_map<int, std::unordered_map<int, size_t>>>>;

int neighbors(const Space &space, Map &map, const int x, const int y,
              const int z, const int w) {
  int sum{0};
  for (int ix = x - 1; ix <= x + 1; ix++) {
    for (int iy = y - 1; iy <= y + 1; iy++) {
      for (int iz = z - 1; iz <= z + 1; iz++) {
        for (int iw = w - 1; iw <= w + 1; iw++) {
          if (ix == x && iy == y && iz == z && iw == w)
            continue;
          if (map[ix][iy][iz].find(iw) == map[ix][iy][iz].end()) {
            continue;
          }
          sum += space[map.at(ix).at(iy).at(iz).at(iw)].active ? 1 : 0;
        }
      }
    }
  }
  return sum;
}

void fill_neighbors(Space &space, Map &map) {
  const auto s = space.size();
  for (size_t j = 0; j < s; j++) {
    const Cube c = space[j];
    for (int ix = c.x - 1; ix <= c.x + 1; ix++) {
      for (int iy = c.y - 1; iy <= c.y + 1; iy++) {
        for (int iz = c.z - 1; iz <= c.z + 1; iz++) {
          for (int iw = c.w - 1; iw <= c.w + 1; iw++) {
            if (ix == c.x && iy == c.y && iz == c.z && iw == c.w)
              continue;
            if (map[ix][iy][iz].find(iw) != map[ix][iy][iz].end()) {
              continue;
            }
            space.push_back(Cube{ix, iy, iz, iw});
            map[ix][iy][iz][iw] = space.size() - 1;
          }
        }
      }
    }
  }
}

int solve(std::fstream &in) {
  Space space{};
  Map map{};

  std::string line{};
  int iy{0};
  size_t idx{0};
  while (getline(in, line)) {
    for (int ix = 0; ix < line.size(); ix++) {
      Cube cube{ix, iy, 0, 0};
      cube.active = line[ix] == '#';
      space.push_back(cube);
      map[ix][iy][0][0] = idx;
      idx++;
    }
    iy++;
  }
  for (int turn = 0; turn < 6; turn++) {
    fill_neighbors(space, map);
    Space next{};
    for (const auto &c : space) {
      const auto n = neighbors(space, map, c.x, c.y, c.z, c.w);

      Cube cube{c.x, c.y, c.z, c.w};
      if (c.active) {
        cube.active = n == 2 || n == 3;
      } else {
        cube.active = n == 3;
      }

      next.push_back(cube);
    }
    space = next;
  }
  int sum{0};
  for (const auto &c : space) {
    sum += c.active ? 1 : 0;
  }
  return sum;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day17.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
