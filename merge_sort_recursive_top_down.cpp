#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

template <class T>
void merge_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    size_t size = std::distance(begin, end);
    if (size < 2) {
        return;
    }

    auto divide_point = begin + size / 2;

    merge_sort<T>(begin, divide_point);
    merge_sort<T>(divide_point, end);

    std::vector<T> tmp(size);
    // Merge the two ranges into tmp:
    auto lo_it = begin;
    auto hi_it = divide_point;
    for (auto it = tmp.begin(); it != tmp.end(); ++it) {
        if (lo_it == divide_point) {
            *it = *hi_it;
            ++hi_it;
        } else  if (hi_it == end) {
            *it = *lo_it;
            ++lo_it;
            continue;
        } else if (*lo_it < *hi_it) {
            *it = *lo_it;
            ++lo_it;
        } else {
            *it = *hi_it;
            ++hi_it;
        }
    }
    std::copy(tmp.begin(), tmp.end(), begin);
}

int main(int argc, char* argv[])
{
    std::string source_file("unsorted.bin");
    if (argc > 1) {
        source_file = argv[1];
        std::cout << "Reading data from " << source_file << std::endl;
    }
    auto data = read_values<unsigned>(source_file.c_str());
    clock_t t0 = clock();
    merge_sort<unsigned>(data.begin(), data.end());
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("merge_sort_recursive_top_down.sorted", data);
}
