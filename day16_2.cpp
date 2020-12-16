#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// https://adventofcode.com/2020/day/16#part2

struct Range {
  int l1, r1, l2, r2;

  Range(int l1, int r1, int l2, int r2) : l1(l1), r1(r1), l2(l2), r2(r2) {}
  bool Has(const int num) const {
    return (l1 <= num && r1 >= num) || (l2 <= num && r2 >= num);
  }
};

auto find_single(const std::vector<std::set<size_t>> &guess) {
  return std::find_if(
      guess.begin(), guess.end(),
      [](const std::set<size_t> &elem) { return elem.size() == 1; });
}

size_t solve(std::fstream &in) {
  const std::regex r_field{"^([a-z ]+): ((\\d+)-(\\d+)) or ((\\d+)-(\\d+))$"};
  std::vector<Range> fields{};
  std::vector<int> ticket{};
  bool get_ticket{false};
  std::vector<std::set<size_t>> guess{};

  std::string line{};
  std::smatch f_match;
  while (getline(in, line)) {
    if (line.empty()) {
      continue;
    } else if (line == "your ticket:") {
      get_ticket = true;
    } else if (line == "nearby tickets:") {
      get_ticket = false;
    } else if (std::regex_search(line, f_match, r_field)) {
      fields.emplace_back(std::stoi(f_match.str(3)), std::stoi(f_match.str(4)),
                          std::stoi(f_match.str(6)), std::stoi(f_match.str(7)));
    } else {
      if (guess.empty()) {
        std::set<size_t> all;
        for (size_t i = 0; i < fields.size(); i++)
          all.insert(i);

        for (size_t i = 0; i < fields.size(); i++) {
          guess.push_back(all);
        }
      }
      bool ticket_invalid{false};
      std::istringstream ss{line};
      std::string num{};
      std::vector<int> near{};
      while (getline(ss, num, ',')) {
        const auto item = std::stoi(num);
        if (get_ticket)
          ticket.push_back(item);

        size_t fail{0};
        for (const auto &r : fields) {
          if (!r.Has(item))
            fail++;
        }
        ticket_invalid |= (fail == fields.size());

        near.push_back(item);
      }
      if (ticket_invalid)
        continue;

      for (size_t n = 0; n < near.size(); n++) {
        for (size_t i = 0; i < fields.size(); i++) {
          if (!fields[i].Has(near[n])) {
            guess[n].erase(i);
          }
        }
      }
    }
  }
  std::unordered_map<size_t, size_t> map{};
  auto single = find_single(guess);
  do {
    auto idx = single - guess.begin();
    size_t elem = *guess[idx].begin();
    map[elem] = idx;
    for (size_t i = 0; i < fields.size(); i++) {
      guess[i].erase(elem);
    }
    single = find_single(guess);
  } while (single != guess.end());
  size_t mul{1};
  for (size_t i = 0; i < 6; i++) {
    mul *= ticket[map[i]];
  }
  return mul;
}

int main() {
  const auto start = std::chrono::high_resolution_clock::now();

  std::fstream in_file;
  in_file.open("input/day16.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();

  const auto stop = std::chrono::high_resolution_clock::now();
  const auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time: " << duration.count() << " us\n";
}
