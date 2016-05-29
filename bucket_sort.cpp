#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <cassert>
#include <limits>
#include "io.hpp"

static const size_t BUCKET_SIZE = 70;

template <class T>
static double normalized_position(T value)
{
    T min = std::numeric_limits<T>::lowest();
    T max = std::numeric_limits<T>::max();
    return static_cast<double>(value - min) / (max - min);
}

template <class T>
void bucket_sort(typename std::vector<T>& data)
{
    const size_t num_of_buckets = data.size() / BUCKET_SIZE + 1;
    const size_t average_BUCKET_SIZE = data.size() / num_of_buckets;
    std::vector<std::vector<T>> buckets(num_of_buckets, std::vector<T>());
    // Reserve space for buckets to minimize memory reallocations:
    for (size_t i = 0; i < num_of_buckets; ++i) {
        buckets[i].reserve(average_BUCKET_SIZE);
    }

    // Put numbers into corresponding buckets:
    for (size_t i = 0; i < data.size(); ++i) {
        double pos = normalized_position(data[i]);
        size_t bucket_number = pos * num_of_buckets;
        assert(bucket_number < num_of_buckets);
        auto& bucket = buckets[bucket_number];
        bucket.push_back(data[i]);
        // Swap down the inserted value to make the vector sorted:
        size_t j = bucket.size() - 1;
        while (j > 0 && bucket[j] < bucket[j-1]) {
            std::swap(bucket[j-1], bucket[j]);
            --j;
        }
    }

    // Put sorted numbers into the source vector:
    size_t k = 0;
    for (size_t i = 0; i < num_of_buckets; ++i) {
        for (size_t j = 0; j < buckets[i].size(); ++j) {
            data[k++] = buckets[i][j];
        }
    }
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
    bucket_sort<unsigned>(data);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("bucket_sort.sorted", data);
}
