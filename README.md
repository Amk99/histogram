## Histogram Generator in C++

A simple Histogram generator in C++.It can read a data from input file where each line contains a fourvector of x,y,z components of momentum and energy.It can generate
distributions of pT, pX, pY, pZ, energy and mass. Where mass is calculated as sqrt(E<sup>2</sup> - x<sup>2</sup> - y<sup>2</sup> - z<sup>2</sup>).

### Steps to use
 -Fork this repo <br>
 -Clone repo<br>
 -cd to cloned repo<br>
 -on command line:
```
g++ hist.cc -o hist
./hist <datafile> <distribution_name> <num_bins> <min_val> <max_val>
```
output file named hist.txt will be generted.

#### To run tests
```
g++ unit_tests.cc -o test
./test
```
