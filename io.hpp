#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

template <class T>
std::vector<T> read_values(const char* filename = "unsorted.bin")
{
    std::ifstream fs;
    fs.open(filename, std::ios::in | std::ios::binary);
    if (!fs.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
    }
    std::vector<T> result;
    T number;
    std::cout << "Reading file" << std::endl;
    while (fs.read(reinterpret_cast<char*>(&number), sizeof(T))) {
        std::cout << "Read: " << number << std::endl;
        result.push_back(number);
    }
    return result;
}

template <class T>
void write_values(const char* filename, const std::vector<T> values)
{
    std::fstream fs;
    fs.open(filename, std::fstream::out);
    std::ostream_iterator<T> out_iterator(fs, " ");
    std::copy(values.begin(), values.end(), out_iterator);
    fs.close();
}
