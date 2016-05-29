#include <fstream>
#include <iostream>
#include <random>

static const char filename[] = "unsorted.data";

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Generates 'unsorted.data' file with N random integers." << std::endl;
		std::cout << "N can be in scientific notation. e.g., 1E6." << std::endl;
		std::cout << "Usage: " << std::endl;
		std::cout << argv[0] << " N" << std::endl;
		exit(0);
	}

	unsigned nvalues = std::stod(argv[1]);

    std::fstream fs;
    fs.open(filename, std::fstream::out);

    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<unsigned int> dist;

    for (unsigned int i = 0; i < nvalues; ++i) {
        fs << dist(re) << " ";
    }

    fs.close();

    return 0;
}
