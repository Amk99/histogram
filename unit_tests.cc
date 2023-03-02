#include "classes.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void test_vector_class() {

    // make sure vector class is reading x,y,z values and computing magnitude and axis correctly

    vector_class fv(3.0, 4.0, 0.0);  
    assert(fv.x == 3.0);
    assert(fv.y == 4.0);
    assert(fv.z == 0.0);
    assert(fv.magnitude() == 5.0);
    assert(fv.transverse() == 5.0);
    std::cout << "vector_class working!!"<< std::endl;
    }

// make sure fourvector class is reading energy values correctly
void test_four_vector() {
  FourVector fv(3.0, 4.0, 0.0, 4.0);
  assert(fv.energy == 4.0);
  std::cout << "FourVector class working!!"<< std::endl;
}

// make sure data is read correctly from the input file
void test_reader() {
    Reader reader;
    std::vector<FourVector> data = reader.readData("testdata.txt"); 
    assert(data.size() == 3);
    assert(data[0].getX() == 1.0);
    assert(data[0].getY() == 2.0);
    assert(data[0].getZ() == 3.0);
    assert(data[0].getE() == 6.0);
    assert(data[1].getX() == -1.0);
    assert(data[1].getY() == 6.0);
    assert(data[1].getZ() == 5.0);
    assert(data[1].getE() == 8.0);
    assert(data[2].getX() == 10000.0);
    assert(data[2].getY() == -10000.0);
    assert(data[2].getZ() == 10000.0);
    assert(data[2].getE() == 10000.0);
    std::cout << "Reader class Working!!" << std::endl;

}

// make sure data is being dumped into output file correctly
void test_output(){
    std::vector<double> bins = {1, 2, 3, 4, 5}; 
    int num_bins = 5;
    double min_val = 0.0;
    double max_val = 10.0;

    output_histogram(bins, num_bins, min_val, max_val);

    std::ifstream input_file("hist.txt");
    assert(input_file.is_open());
    double bin_center, bin_count;
    int count = 0;
    for (int i = 0; i < num_bins; i++) {
        input_file >> bin_center >> bin_count;
        assert(bin_center == min_val + (i + 0.5) * (max_val - min_val) / num_bins);
        assert(bin_count == bins[i]);
        count += bins[i];
    }
    std::cout << "Output class Working!!" << std::endl;

}



int main() {
    test_reader();
    test_vector_class();
    test_four_vector();
    test_output();
  return 0;
}