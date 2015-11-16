#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "io.hpp"

int cmp(const void* a, const void* b)
{
    unsigned arg1 = *static_cast<const unsigned*>(a);
    unsigned arg2 = *static_cast<const unsigned*>(b);
    if (arg1 < arg2) { return -1; }
    if (arg1 > arg2) { return 1; }
    return 0;
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
    std::qsort(&data[0], data.size(), sizeof(unsigned), cmp);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("qsort.sorted", data);
}