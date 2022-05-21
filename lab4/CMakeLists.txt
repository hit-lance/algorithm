cmake_minimum_required(VERSION 3.10)

project(lab3)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)
find_package(ortools CONFIG REQUIRED)

add_compile_options(-Wno-psabi)

add_executable(main main.cpp quicksort.cpp)
target_link_libraries(main)

# add_executable(benchmark benchmark.cpp quicksort.cpp)
# target_link_libraries(benchmark benchmark::benchmark)
