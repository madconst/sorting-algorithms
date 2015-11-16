#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

template <class T>
void selection_sort(std::vector<T>& v)
{
    for (auto i = v.begin(); i != v.end(); ++i) {
        auto smallest = i;
        for (auto j = i + 1; j != v.end(); ++j) {
            if (*j < *smallest) {
                smallest = j;
            }
        }
        std::iter_swap(i, smallest);
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
    selection_sort<unsigned>(data);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("selection_sort.sorted", data);
}