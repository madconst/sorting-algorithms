#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

static unsigned max_depth;
static unsigned min_elements;

template <class T>
void insertion_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
    if (begin == end) {
        return;
    }
    for (auto i = begin + 1; i != end; ++i) {
        auto j = i;
        while (j != begin) {
            if (*(j-1) > *j) {
                std::swap(*(j - 1), *j);
                --j;
            } else break;
        }
    }
}

template <class T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, unsigned depth = 0)
{
    if (std::distance(begin, end) < min_elements || depth > max_depth) {
        insertion_sort<unsigned>(begin, end);
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

    quick_sort<T>(begin, pivot, depth + 1);
    quick_sort<T>(pivot, end, depth + 1);
}

int main(int argc, char* argv[])
{
    std::string source_file("unsorted.data");
    if (argc > 1) {
        source_file = argv[1];
        std::cout << "Reading data from " << source_file << std::endl;
    }

    // Read data:
    auto data = read_values<unsigned>(source_file.c_str());

    // Calculate integer log2(data_size):
    size_t data_size = data.size();
    while (data_size >>= 1) { min_elements++; }
    max_depth = 2 * min_elements;

    // Start sorting:
    clock_t t0 = clock();
    quick_sort<unsigned>(data.begin(), data.end());
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    // Output result:
    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    // Save to file:
    write_values<unsigned>("quick_sort+insertion_sort.sorted", data);
}