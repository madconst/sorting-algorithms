#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>

const char* default_filename = "unsorted.data";

template <class T>
std::vector<T> read_values(const char* filename = default_filename)
{
    std::fstream fs;
    fs.open(filename, std::fstream::in);
    std::vector<T> result;
    std::copy(
    	std::istream_iterator<T>(fs), 
    	std::istream_iterator<T>(), 
    	std::back_inserter(result)
    );
    fs.close();
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