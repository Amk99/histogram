// Import file for unit tests with class definitions

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <cmath>


class vector_class {
public:
    double x, y, z;
    
    vector_class(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    double magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double transverse() const {
        return std::sqrt(x * x + y * y);
    }

    double angle(const vector_class& other) const {
        double dot = x * other.x + y * other.y + z * other.z;
        double mag = magnitude() * other.magnitude();
        return std::acos(dot / mag);
    }
};


class FourVector : public vector_class {
public:
    double energy;

    FourVector(double x_, double y_, double z_, double energy_) : vector_class(x_, y_, z_), energy(energy_) {}
        // Accessors
    double getE() const { return energy; }
    double getX() const { return x; } // define getX() function
    double getY() const { return y; }
    double getZ() const { return z; }

    double mass() const {
        return std::sqrt(energy * energy - x * x - y * y - z * z);
    }
};


class Reader {
public:
    std::vector<FourVector> readData(std::string filename) {
        std::vector<FourVector> data;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: could not open file " << filename << std::endl;
            return data;
        }
        double x, y, z, E;
        while (file >> x >> y >> z >> E) {
            data.push_back(FourVector(x, y, z, E));
        }
        file.close();
        return data;
    }
}; 

void output_histogram(const std::vector<double>& bins, int num_bins, double min_val, double max_val) {
    double bin_width = (max_val - min_val) / num_bins;
    std::ofstream output_file("test.txt");
    for (int i = 0; i < num_bins; i++) {
        double bin_center = min_val + (i + 0.5) * bin_width;
        output_file << bin_center << " " << bins[i] << std::endl;
    }
    std::cout << "Histogram saved to 'test.txt '"<< std::endl;
}
