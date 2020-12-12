# CMakeList.txt : CMake project for adventofcode2020, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("adventofcode2020")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_executable (day1_1 "day1_1.cpp")
add_executable (day1_2 "day1_2.cpp")
add_executable (day2_1 "day2_1.cpp")
add_executable (day2_2 "day2_2.cpp")
add_executable (day3_1 "day3_1.cpp")
add_executable (day3_2 "day3_2.cpp")
add_executable (day4_1 "day4_1.cpp")
add_executable (day4_2 "day4_2.cpp")
add_executable (day5_1 "day5_1.cpp")
add_executable (day5_2 "day5_2.cpp")
add_executable (day6_1 "day6_1.cpp")
add_executable (day6_2 "day6_2.cpp")
add_executable (day7_1 "day7_1.cpp")
add_executable (day7_2 "day7_2.cpp")
add_executable (day8_1 "day8_1.cpp")
add_executable (day8_2 "day8_2.cpp")
add_executable (day9_1 "day9_1.cpp")
add_executable (day9_2 "day9_2.cpp")
add_executable (day10_1 "day10_1.cpp")
add_executable (day10_2 "day10_2.cpp")
add_executable (day11_1 "day11_1.cpp")
add_executable (day11_2 "day11_2.cpp")
add_executable (day12_1 "day12_1.cpp")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/input" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")