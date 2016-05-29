#include <fstream>
#include <iostream>
#include <random>

static const char filename[] = "unsorted.bin";

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Generates 'unsorted.bin' file with N random integers." << std::endl;
		std::cout << "N can be in scientific notation. e.g., 1E6." << std::endl;
		std::cout << "Usage: " << std::endl;
		std::cout << argv[0] << " N" << std::endl;
		exit(0);
	}

	unsigned nvalues = std::stod(argv[1]);

    std::ofstream fs;
    fs.open(filename, std::ios::out | std::ios::binary);

    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<unsigned int> dist;

    for (unsigned int i = 0; i < nvalues; ++i) {
        unsigned int number = dist(re);
        fs.write(reinterpret_cast<char*>(&number), sizeof(number));
    }

    fs.close();

    return 0;
}
