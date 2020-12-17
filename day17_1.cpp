#include <chrono>
#include <execution>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// https://adventofcode.com/2020/day/17

struct Cube {
  int x, y, z;
  bool active{false};

  constexpr bool At(const int xx, const int yy, const int zz) const {
    return xx == x && yy == y && zz == z;
  }
};

using Space = std::vector<Cube>;

bool active(const Space &space, const int x, const int y, const int z) {
  const auto found =
      std::find_if(std::execution::par, space.begin(), space.end(),
                   [&](const Cube &c) { return c.At(x, y, z); });
  if (found != space.end()) {
    return found->active;
  }

  return false;
}

int neighbors(const Space &space, const int x, const int y, const int z) {
  int sum{0};
  for (int ix = x - 1; ix <= x + 1; ix++) {
    for (int iy = y - 1; iy <= y + 1; iy++) {
      for (int iz = z - 1; iz <= z + 1; iz++) {
        if (ix == x && iy == y && iz == z)
          continue;
        sum += active(space, ix, iy, iz) ? 1 : 0;
      }
    }
  }
  return sum;
}

void fill_neighbors(Space &space) {
  const auto s = space.size();
  for (size_t j = 0; j < s; j++) {
    const Cube c = space[j];
    for (int ix = c.x - 1; ix <= c.x + 1; ix++) {
      for (int iy = c.y - 1; iy <= c.y + 1; iy++) {
        for (int iz = c.z - 1; iz <= c.z + 1; iz++) {
          if (ix == c.x && iy == c.y && iz == c.z)
            continue;
          if (std::find_if(std::execution::par, space.begin(), space.end(),
                           [&](const Cube &c) { return c.At(ix, iy, iz); }) ==
              space.end())
            space.push_back(Cube{ix, iy, iz});
        }
      }
    }
  }
}

int solve(std::fstream &in) {
  Space space{};

  std::string line{};
  int iy{0};
  while (getline(in, line)) {
    for (int ix = 0; ix < line.size(); ix++) {
      Cube cube{ix, iy, 0};
      cube.active = line[ix] == '#';
      space.push_back(cube);
    }
    iy++;
  }
  for (int turn = 0; turn < 6; turn++) {
    fill_neighbors(space);
    Space next{};
    for (const auto &c : space) {
      const auto n = neighbors(space, c.x, c.y, c.z);

      Cube cube{c.x, c.y, c.z};
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
