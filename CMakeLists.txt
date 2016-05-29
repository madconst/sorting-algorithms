cmake_minimum_required (VERSION 2.6)
project (sorting-algorithms)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra -O2")

# Generator of random data:
add_executable (generate generate.cpp)

# std::sort:
add_executable (std_sort std_sort.cpp)

# qsort:
add_executable (qsort qsort.cpp)

# Selection sort:
add_executable (selection_sort selection_sort.cpp)

# Insertion sort:
add_executable (insertion_sort insertion_sort.cpp)

# Quick sort:
add_executable (quick_sort quick_sort.cpp)

# Quick sort + insertion sort:
add_executable (quick_sort+insertion_sort quick_sort+insertion_sort.cpp)

# Quick sort + selection sort:
add_executable (quick_sort+selection_sort quick_sort+selection_sort.cpp)

# Heap sort:
add_executable (heap_sort heap_sort.cpp)

# Merge sort:
add_executable (merge_sort merge_sort.cpp)

# Merge sort recursive top-down implementation:
add_executable (merge_sort_recursive_top_down merge_sort_recursive_top_down.cpp)

# Radix sort (base 16):
add_executable (radix_sort radix_sort.cpp)

# Flash sort:
add_executable (bucket_sort bucket_sort.cpp)
