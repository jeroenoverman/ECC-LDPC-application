#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>
#include <fstream>

#include "awgn.h"

TEST_CASE("AWGN channel")
{
    double signal[17] = {-1, 1, 1, 1, -1, -1, -1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1};
    double awgn_signal[17];

    AWGN awgn;
    awgn.apply(awgn_signal, signal, 17, 5);

    // Write the result to a csv
    std::ofstream myfile;

    myfile.open ("test_awgn.csv");
    for (int i=0; i<17; i++) {
        myfile << i << ", " << signal[i] << ", " << awgn_signal[i] << ",\n";
    }

    myfile.close();
}

