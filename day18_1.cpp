#include <chrono>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

// https://adventofcode.com/2020/day/18

enum class Op { add, mul };

struct State {
  size_t num{0};
  Op op{Op::add};

  void Eat(const size_t next) {
    switch (op) {
    case Op::add:
      num += next;
      break;
    case Op::mul:
      num *= next;
      break;
    }
  }
};

size_t eval(std::string &line) {
  std::stack<State> stack{};
  State state{};
  for (const auto &c : line) {
    switch (c) {
    case ' ':
      continue;
    case '+':
      state.op = Op::add;
      break;
    case '*':
      state.op = Op::mul;
      break;
    case '(':
      stack.push(state);
      state = State();
      break;
    case ')':
      stack.top().Eat(state.num);
      state = stack.top();
      stack.pop();
      break;
    default:
      state.Eat(c - 48);
      break;
    }
  }
  return state.num;
}

size_t solve(std::fstream &in) {
  size_t sum{0};
  std::string line{};
  while (getline(in, line)) {
    sum += eval(line);
  }
  return sum;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day18.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
