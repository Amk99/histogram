// Import file for unit tests with class definitions
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>


// vector class which takes momentum values and does basic computations
class vector_class {
public:
    double x, y, z;
    
    // constructor
    vector_class(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {} 

    double magnitude() const {        
        return std::sqrt(x * x + y * y + z * z);
    }

    double transverse() const {
        return std::sqrt(x * x + y * y);
    }

    // calculate angle between two vectors
    double angle(const vector_class& other) const {     
        double dot = x * other.x + y * other.y + z * other.z;
        double mag = magnitude() * other.magnitude();
        return std::acos(dot / mag);
    }
};

// Four-vector class which inherits the vector_class
class FourVector : public vector_class {
public:
    double energy;

    FourVector(double x_, double y_, double z_, double energy_) : vector_class(x_, y_, z_), energy(energy_) {}

    // Accessors to access x,y,z values for testing
    double getE() const { return energy; }
    double getX() const { return x; }     
    double getY() const { return y; }
    double getZ() const { return z; }

    // calculate mass
    double mass() const {
        return std::sqrt(energy * energy - x * x - y * y - z * z);
    }
    // To extend any functionality new fuction can be added here
};


// Reader class to read data from input file
class Reader {
public:
    std::vector<FourVector> readData(std::string filename) {
        std::vector<FourVector> data; 
        std::ifstream file(filename); // open the file
        
        //make sure the file is valid
        if (!file.is_open()) {
            std::cerr << "Error: could not open file " << filename << std::endl;
            return data;
        }
        double x, y, z, E;
        while (file >> x >> y >> z >> E) {
            data.push_back(FourVector(x, y, z, E));  // Read the data from the file and convert into appropriate class
        }
        file.close();
        return data;
    }
}; 



// Data class
class Data {
private:
    std::vector<FourVector> four_vectors; // vector of fourvectors which inturn inherits the vectors class
    Reader reader; // create instance of reader class
public:
    void read(const std::string& filename) {
        four_vectors = reader.readData(filename); //read the data from input file and dump into vector of fourvector class
        }

    std::vector<double> distribution(const std::string& name, int num_bins, double min_val, double max_val) const {  // function to create the histograms
        std::vector<double> bins(num_bins);
        double bin_width = (max_val - min_val) / num_bins;
        for (const auto& fv : four_vectors) { 
            double val = 0.0;
            if (name == "pT") {
                val = fv.transverse();
            } else if (name == "pX") {
                val = fv.x;
            } else if (name == "pY") {
                val = fv.y;
            } else if (name == "pZ") {
                val = fv.z;
            } else if (name == "energy") {
                val = fv.energy;
            } else if (name == "mass") {
                val = fv.mass();
            } else {
                std::cerr << "Error: invalid distribution name '" << name << "'" << std::endl;
                exit(1);
            }
            if (val >= min_val && val < max_val) {
                int bin_index = static_cast<int>((val - min_val) / bin_width);
                bins[bin_index]++;
            }
        }
        for (auto& bin : bins) {
            bin /= four_vectors.size();
        }
        return bins;
    }
};



// Output system to dump histogram data into an outtput file
void output_histogram(const std::vector<double>& bins, int num_bins, double min_val, double max_val) {
    // calculate bin width
    double bin_width = (max_val - min_val) / num_bins;
    // creating output file
    std::ofstream output_file("hist.txt");
    for (int i = 0; i < num_bins; i++) {
        double bin_center = min_val + (i + 0.5) * bin_width;
        output_file << bin_center << " " << bins[i] << std::endl;
    }
    std::cout << "Histogram saved to 'hist.txt '"<< std::endl;
}

