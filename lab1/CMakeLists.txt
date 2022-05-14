cmake_minimum_required(VERSION 3.10)

project(lab1)

find_package(benchmark CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_compile_options(-Wno-psabi)

set(CONVEX_HULL enumerate_convex_hull_solver.cpp graham_convex_hull_solver.cpp divide_convex_hull_solver.cpp)

enable_testing()

add_executable(convex_hull_test convex_hull_test.cpp ${CONVEX_HULL})
target_link_libraries(convex_hull_test gtest_main gtest)

include(GoogleTest)
gtest_discover_tests(convex_hull_test)

add_executable(benchmark benchmark.cpp ${CONVEX_HULL})
target_link_libraries(benchmark benchmark::benchmark)
