#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

// https://adventofcode.com/2020/day/7

struct Bag {
  int count{0};
  size_t color{0};
};

int solve(std::fstream &in) {
  const std::regex r_outside("(^[a-z]+ [a-z]+)");
  const std::regex r_inside("(\\d+) ([a-z]+ [a-z]+) bags?");

  std::multimap<size_t, Bag> bags;
  std::string line{};
  while (getline(in, line)) {
    std::smatch m_out;
    if (std::regex_search(line, m_out, r_outside)) {
      const auto s_out = std::hash<std::string>{}(m_out.str(0));
      std::smatch m_in;
      auto l_begin = line.cbegin();
      while (std::regex_search(l_begin, line.cend(), m_in, r_inside)) {
        bags.emplace(std::hash<std::string>{}(m_in.str(2)),
                     Bag{std::stoi(m_in.str(1)), s_out});
        l_begin = m_in[0].second;
      }
    }
  }
  std::set<size_t> colors;
  std::function<void(size_t)> find_containing;
  find_containing = [&bags, &colors, &find_containing](size_t color) {
    auto er = bags.equal_range(color);
    for (auto &i = er.first; i != er.second; i++) {
      colors.insert(i->second.color);
      find_containing(i->second.color);
    }
  };
  find_containing(std::hash<std::string>{}("shiny gold"));
  return colors.size();
}

int main() {
  std::fstream in_file;
  in_file.open("input/day7.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
