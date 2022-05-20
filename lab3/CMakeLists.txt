cmake_minimum_required(VERSION 3.10)

project(lab3)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

add_compile_options(-Wno-psabi)

set(set_cover greedy_set_cover_solver.cpp ilp_set_cover_solver.cpp)

add_executable(main main.cpp ${set_cover})

# enable_testing()

# add_executable(set_cover_test set_cover_test.cpp ${set_cover})
# target_link_libraries(set_cover_test ${GTEST_BOTH_LIBRARIES})

# include(GoogleTest)
# gtest_discover_tests(set_cover_test)

# add_executable(benchmark benchmark.cpp ${set_cover})
# target_link_libraries(benchmark benchmark::benchmark)
