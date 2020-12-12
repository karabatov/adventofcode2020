#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// https://adventofcode.com/2020/day/12

struct Point {
  int x, y;
};

enum class Cmd { n, s, e, w, l, r, f };

struct Order {
  Cmd cmd;
  int count;
};

class Direction {
private:
  int deg_{90};

  void Wrap() {
    while (deg_ < 0) {
      deg_ += 360;
    }
    deg_ %= 360;
  }

public:
  void TurnLeft(int degrees) {
    deg_ -= degrees;
    Wrap();
  }
  void TurnRight(int degrees) {
    deg_ += degrees;
    Wrap();
  }
  Cmd GetDirection() {
    switch (deg_) {
    case 0:
      return Cmd::n;
    case 90:
      return Cmd::e;
    case 180:
      return Cmd::s;
    case 270:
      return Cmd::w;
    default:
      throw std::invalid_argument("Invalid angle.");
    }
  }
};

class Ship {
  Point pos_{0, 0};
  Direction dir_{};

public:
  int Distance() { return pos_.x + pos_.y; }

  void Follow(Order order) {
    switch (order.cmd) {
    case Cmd::n:
      pos_.y -= order.count;
      break;
    case Cmd::s:
      pos_.y += order.count;
      break;
    case Cmd::e:
      pos_.x += order.count;
      break;
    case Cmd::w:
      pos_.y -= order.count;
      break;
    case Cmd::l:
      dir_.TurnLeft(order.count);
      break;
    case Cmd::r:
      dir_.TurnRight(order.count);
      break;
    case Cmd::f:
      Follow(Order{dir_.GetDirection(), order.count});
      break;
    }
  }
};

int solve(std::fstream &in) {
  Ship ship{};

  std::string line{};
  while (getline(in, line)) {
    Cmd cmd{Cmd::n};
    switch (line[0]) {
    case 'N':
      cmd = Cmd::n;
      break;
    case 'S':
      cmd = Cmd::s;
      break;
    case 'E':
      cmd = Cmd::e;
      break;
    case 'W':
      cmd = Cmd::w;
      break;
    case 'L':
      cmd = Cmd::l;
      break;
    case 'R':
      cmd = Cmd::r;
      break;
    case 'F':
      cmd = Cmd::f;
      break;
    default:
      throw std::invalid_argument("Unknown command.");
    }
    int count = std::stoi(line.substr(1, line.size() - 1));
    ship.Follow(Order{cmd, count});
  }
  return ship.Distance();
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day12.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
