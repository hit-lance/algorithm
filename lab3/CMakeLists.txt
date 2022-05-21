cmake_minimum_required(VERSION 3.10)

project(lab3)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)
find_package(ortools CONFIG REQUIRED)

add_compile_options(-Wno-psabi)

set(set_cover greedy_set_cover_solver.cpp ilp_set_cover_solver.cpp)

add_executable(main main.cpp ${set_cover})
target_link_libraries(main ortools::ortools)

add_executable(benchmark benchmark.cpp ${set_cover})
target_link_libraries(benchmark benchmark::benchmark ortools::ortools)
