#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// https://adventofcode.com/2020/day/12#part2

struct Point {
  int x, y;
};

enum class Cmd { n, s, e, w, l, r, f };

struct Order {
  Cmd cmd;
  int count;
};

class Ship {
  Point pos_{0, 0};
  Point wp_{0, 0};

  void MoveToWaypoint(int times) {
    while (times > 0) {
      pos_.x += wp_.x;
      pos_.y += wp_.y;
      times--;
    }
  }

public:
  Ship(int x, int y) : wp_{x, y} {}

  int Distance() { return std::abs(pos_.x) + std::abs(pos_.y); }

  void Follow(Order order) {
    switch (order.cmd) {
    case Cmd::n:
      wp_.y += order.count;
      break;
    case Cmd::s:
      wp_.y -= order.count;
      break;
    case Cmd::e:
      wp_.x += order.count;
      break;
    case Cmd::w:
      wp_.x -= order.count;
      break;
    case Cmd::l:
      switch (order.count) {
      case 90:
        wp_ = Point{-wp_.y, wp_.x};
        break;
      case 180:
        wp_ = Point{-wp_.x, -wp_.y};
        break;
      case 270:
        wp_ = Point{wp_.y, -wp_.x};
        break;
      default:
        throw std::invalid_argument("Invalid angle.");
      }
      break;
    case Cmd::r:
      switch (order.count) {
      case 90:
        wp_ = Point{wp_.y, -wp_.x};
        break;
      case 180:
        wp_ = Point{-wp_.x, -wp_.y};
        break;
      case 270:
        wp_ = Point{-wp_.y, wp_.x};
        break;
      default:
        throw std::invalid_argument("Invalid angle.");
      }
      break;
    case Cmd::f:
      MoveToWaypoint(order.count);
      break;
    }
  }
};

int solve(std::fstream &in) {
  Ship ship{10, 1};

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
