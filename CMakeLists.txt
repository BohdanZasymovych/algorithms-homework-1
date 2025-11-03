cmake_minimum_required(VERSION 4.0)
project(homework_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework_1 main.cpp src/student_base_1.cpp src/student_base_2.cpp src/student_base_3.cpp src/student_base_sort.cpp)

add_executable(test_operations benchmarks/count_operations.cpp src/student_base_1.cpp src/student_base_2.cpp src/student_base_3.cpp)
add_executable(test_memory benchmarks/test_memory_usage.cpp src/student_base_1.cpp src/student_base_2.cpp src/student_base_3.cpp)
add_executable(test_sorting benchmarks/compare_sorting.cpp src/student_base_sort.cpp)
