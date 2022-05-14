cmake_minimum_required(VERSION 3.10)

project(lab1)

find_package(benchmark REQUIRED)

add_compile_options(-Wno-psabi)

add_executable(main main.cpp enumerate_convex_hull_solver.cpp graham_convex_hull_solver.cpp divide_convex_hull_solver.cpp)

target_link_libraries(main benchmark::benchmark)