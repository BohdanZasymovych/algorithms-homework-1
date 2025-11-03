cmake_minimum_required(VERSION 4.0)
project(homework_1)

set(CMAKE_CXX_STANDARD 20)


add_executable(compare_operations_count benchmarks/compare_operations_count.cpp src/student_base_1.cpp src/student_base_2.cpp src/student_base_3.cpp)

add_executable(compare_memory_usage benchmarks/compare_memory_usage.cpp src/student_base_1.cpp src/student_base_2.cpp src/student_base_3.cpp)

add_executable(compare_sorting_time benchmarks/compare_sorting_time.cpp src/student_base_sort.cpp)
