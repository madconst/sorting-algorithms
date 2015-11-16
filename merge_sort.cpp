#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

/* Bottom-up implementation of the merge sort algorithm */

template <class T>
void merge_two_ranges(typename std::vector<T>& from, typename std::vector<T>& to, 
    size_t range1_begin, size_t range2_begin, size_t range2_end)
{
    size_t range1_i = range1_begin;
    size_t range2_i = range2_begin;
    for (size_t out_i = range1_begin; out_i < range2_end; ++out_i) {
        if (range1_i == range2_begin) {
            to[out_i] = from[range2_i];
            ++range2_i;
        } else if (range2_i == range2_end) {
            to[out_i] = from[range1_i];
            ++range1_i;
        } else if (from[range1_i] < from[range2_i]) {
            to[out_i] = from[range1_i];
            ++range1_i;
        } else {
            to[out_i] = from[range2_i];
            ++range2_i;
        }
    }
}

template <class T>
void merge_sort(typename std::vector<T>& data)
{
    std::vector<unsigned> buffer(data.size());
    size_t end = data.size();
    for (size_t size = 1; size < data.size(); size *= 2) {
        size_t range_i;
        for (range_i = 0; range_i < data.size(); range_i += 2 * size) {
            // Merge every 2 ranges into buffer:
            // data:[range_i, range_i+size), data:[range_i+size, range_i+2*size) => buffer:[range_i, range_i+2*size)
            size_t range2_begin = std::min(range_i + size, end);
            size_t range2_end = std::min(range_i + 2 * size, end);
            merge_two_ranges(data, buffer, range_i, range2_begin, range2_end);
        }
        std::swap(data, buffer);
    }
}

int main(int argc, char* argv[])
{
    std::string source_file("unsorted.data");
    if (argc > 1) {
        source_file = argv[1];
        std::cout << "Reading data from " << source_file << std::endl;
    }
    auto data = read_values<unsigned>(source_file.c_str());
    clock_t t0 = clock();
    merge_sort<unsigned>(data);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("merge_sort.sorted", data);
}
