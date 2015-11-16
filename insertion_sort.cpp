#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

template <class T>
void insertion_sort(std::vector<T>& v)
{
    if (v.begin() == v.end()) {
        return;
    }
    
    for (auto i = v.begin() + 1; i != v.end(); ++i) {
        auto j = i;
        while (j != v.begin()) {
            if (*(j-1) > *j) {
                std::iter_swap(j - 1, j);
                --j;
            } else break;
        }
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
    insertion_sort<unsigned>(data);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("insertion_sort.sorted", data);
}