#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/8#part2

enum class Do { nop, acc, jmp };

struct Op {
  Do op;
  int arg;
};

class Console {
  int acc{0};
  std::vector<Op> ops{};
  std::set<size_t> ran_ops{};

  void Reset() {
    acc = 0;
    ran_ops.clear();
  }

public:
  void Load(Op op) { ops.push_back(op); }

  int Run() {
    Reset();
    size_t idx{0};
    while (idx >= 0 && idx < ops.size()) {
      if (ran_ops.find(idx) != ran_ops.end())
        return -1;
      ran_ops.insert(idx);
      switch (ops[idx].op) {
      case Do::nop:
        idx++;
        break;
      case Do::acc:
        acc += ops[idx].arg;
        idx++;
        break;
      case Do::jmp:
        idx += ops[idx].arg;
        break;
      }
    }
    return acc;
  }

  int RunWithFix() {
    int res{-1};
    for (size_t i = 0; i < ops.size(); i++) {
      switch (ops[i].op) {
      case Do::nop:
        ops[i].op = Do::jmp;
        res = Run();
        ops[i].op = Do::nop;
        break;
      case Do::jmp:
        ops[i].op = Do::nop;
        res = Run();
        ops[i].op = Do::jmp;
        break;
      default:
        break;
      }
      if (res > 0)
        return res;
    }
    return res;
  }
};

Op op_from_line(std::string &line) {
  const auto op = line.substr(0, 3);
  const auto arg = std::stoi(line.substr(4, line.size() - 4));
  if (op == "nop")
    return Op{Do::nop, arg};
  if (op == "acc")
    return Op{Do::acc, arg};
  if (op == "jmp")
    return Op{Do::jmp, arg};

  throw std::invalid_argument(op);
}

size_t solve(std::fstream &in) {
  Console console;

  std::string line{};
  while (getline(in, line)) {
    console.Load(op_from_line(line));
  }

  return console.RunWithFix();
}

int main() {
  std::fstream in_file;
  in_file.open("input/day8.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
