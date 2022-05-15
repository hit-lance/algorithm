cmake_minimum_required(VERSION 3.10)

project(lab1)

set(CMAKE_CXX_STANDARD 14)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

add_compile_options(-Wno-psabi)

set(CONVEX_HULL enumerate_convex_hull_solver.cpp graham_convex_hull_solver.cpp divide_convex_hull_solver.cpp)

enable_testing()

add_executable(convex_hull_test convex_hull_test.cpp ${CONVEX_HULL})
target_link_libraries(convex_hull_test ${GTEST_BOTH_LIBRARIES})

include(GoogleTest)
gtest_discover_tests(convex_hull_test)

add_executable(benchmark benchmark.cpp ${CONVEX_HULL})
target_link_libraries(benchmark benchmark::benchmark)
