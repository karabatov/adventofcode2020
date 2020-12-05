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

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/input" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")