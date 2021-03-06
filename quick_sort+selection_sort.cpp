#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

template <class T>
void selection_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    for (auto i = begin; i != end; ++i) {
        auto smallest = i;
        for (auto j = i + 1; j != end; ++j) {
            if (*j < *smallest) {
                smallest = j;
            }
        }
        std::iter_swap(i, smallest);
    }
}

template <class T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    if (std::distance(begin,end) < 50) {
        selection_sort<unsigned>(begin, end);
        return;
    }

    // Choose pivot:
    auto pivot = begin + std::distance(begin, end) / 2;

    // Partition the range across the chosen pivot in 2 stages:
    // 1. Partition the lower range: [begin, pivot)
    auto upper_bound = pivot;
    for (auto i = begin; i < upper_bound;) {
        // If the value is higher than the pivot, swap it to
        // the end of the lower range:
        if (*i > *pivot) {
            --upper_bound;
            std::swap(*i, *upper_bound);
        } else {
            ++i;
        }
    }
    // All swapped values are > then pivot, so skip them when sorting higher range:
    auto higher_range_begin = pivot + 1;
    // Place the pivot before the upper bound:
    std::swap(*pivot, *upper_bound);
    pivot = upper_bound;

    // 2. Partition the higher range: [pivot, end)
    auto lower_bound = pivot;
    for (auto i = higher_range_begin; i != end; ++i) {
        // If the value is lower than the pivot, swap it to
        // the beginning of the range:
        if (*i < *pivot) {
            std::swap(*i, *(lower_bound + 1));
            ++lower_bound;
        }
    }
    std::swap(*pivot, *lower_bound);
    pivot = lower_bound;

    quick_sort<T>(begin, pivot);
    quick_sort<T>(pivot, end);
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
    quick_sort<unsigned>(data.begin(), data.end());
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("quick_sort+selection_sort.sorted", data);
}