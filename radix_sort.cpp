#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <cassert>
#include "io.hpp"

/* Gets i-th least-significant hex digit from the number.
   Example:
   get_digit(0xdeadbeef, 0) == 0xf
   get_digit(0xdeadbeef, 3) == 0xb
*/

template <class T>
static inline
T get_digit(T number, unsigned char i)
{
    const unsigned char digits_in_number = sizeof(T) * 2;
    number <<= (digits_in_number - i - 1) * 4; // clear all digits to the right
    number >>= (digits_in_number - 1) * 4; // place the digit to the right-most position
    return number;
}

/* Base 16 radix sort */
template <class T>
void radix_sort(typename std::vector<T>& data)
{
    std::vector<T> buffer(data.size(), 0);
    const unsigned char digits_in_number = sizeof(T) * 2;
    const unsigned char digits_exists = 16;
    for (unsigned char i = 0; i < digits_in_number; ++i) {
        // Count-sort based on i-th digit:
        std::vector<size_t> counters(digits_exists, 0);
        for (size_t j = 0; j < data.size(); ++j) {
            unsigned char ith_digit = get_digit(data[j], i);
            ++counters[ith_digit];
        }
        // Calculate counters partial sums:
        size_t numbers_less = 0;
        for (unsigned char j = 0; j < digits_exists; ++j) {
            counters[j] += numbers_less;
            numbers_less = counters[j];
        }
        // Place numbers into buffer in sorted order (sorted by i-th digit):
        for (size_t j = 0; j < data.size(); ++j) {
            // Start from the end:
            size_t k = data.size() - j - 1;
            unsigned char ith_digit = get_digit(data[k], i);
            // Which position in sorted vector must data[k] have? counters[ith_digit] - 1
            assert(counters[ith_digit] > 0);
            --counters[ith_digit];
            buffer[counters[ith_digit]] = data[k];
        }
        std::swap(data, buffer);
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
    radix_sort<unsigned>(data);
    clock_t t1 = clock();
    double spent = 1000 * static_cast<double>(t1 - t0) / CLOCKS_PER_SEC;

    std::cout << "Array size: " << data.size() << std::endl;
    std::cout << "Time spent: " << spent << " ms" << std::endl;

    write_values<unsigned>("radix_sort.sorted", data);
}
