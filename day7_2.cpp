#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

// https://adventofcode.com/2020/day/7#part2

struct Bag {
  size_t count{0};
  size_t color{0};
};

size_t solve(std::fstream &in) {
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
        bags.emplace(s_out, Bag{std::stoull(m_in.str(1)),
                                std::hash<std::string>{}(m_in.str(2))});
        l_begin = m_in[0].second;
      }
    }
  }
  std::function<size_t(size_t)> find_contained;
  find_contained = [&bags, &find_contained](size_t color) -> size_t {
    size_t count{1};
    auto er = bags.equal_range(color);
    for (auto &i = er.first; i != er.second; i++) {
      count += i->second.count * find_contained(i->second.color);
    }
    return count;
  };
  return find_contained(std::hash<std::string>{}("shiny gold")) - 1;
}

int main() {
  std::fstream in_file;
  in_file.open("input/day7.txt", std::ios::in);
  if (in_file.is_open()) {
    std::cout << solve(in_file) << '\n';
  }
  in_file.close();
}
