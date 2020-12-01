# CMakeList.txt : CMake project for adventofcode2020, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("adventofcode2020")

# Add source to this project's executable.
add_executable (day1_1 "day1_1.cpp")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/input" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")