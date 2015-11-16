#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "io.hpp"

template <class T>
void sift_down(std::vector<T>& v, unsigned start, unsigned end)
{
    unsigned root = start;
    unsigned left_child = 2 * root + 1;
    while (left_child < end) {
        unsigned greatest = root;
        // Find the greatest among parent, 1st child and 2nd child
        if (v[left_child] > v[root]) {
            greatest = left_child;
        }
        if (left_child + 1 < end && v[left_child + 1] > v[greatest]) {
            greatest = left_child + 1;
        }
        if (greatest == root) {
            return;
        } else {
            std::swap(v[root], v[greatest]);
            root = greatest;
            left_child = 2 * root + 1;
        }
    }
}

template <class T>
void heapify(std::vector<T>& v)
{
    unsigned last_parent = (v.size() - 2) / 2;
    for (int i = last_parent; i >= 0; --i) {
        sift_down(v, i, v.size());
    }
}

template <class T>
void heap_sort(std::vector<T>& v)
{
    heapify(v);
    unsigned last = v.size() - 1;
    while (last > 0) {
        std::swap(v[0], v[last]);
        sift_down(v, 0, last);
        --last;
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
    heap_sort<unsigned>(data);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("heap_sort.sorted", data);
}
