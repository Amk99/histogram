
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include "classes.h"


int main(int argc, char* argv[]) {
    // check for proper useage
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " datafile distribution_name num_bins min_val max_val" << std::endl;
        return 1;
    }

    std::string datafile = argv[1];
    std::string distribution_name = argv[2];
    int num_bins = std::stoi(argv[3]);
    double min_val = std::stod(argv[4]);
    double max_val = std::stod(argv[5]);


    // read the data and convert into fourvector class
    Data data;
    data.read(datafile); 

    // create the distribution
    auto bins = data.distribution(distribution_name, num_bins, min_val, max_val);

    // dump data into output file
    output_histogram(bins, num_bins, min_val, max_val);

    return 0;
}