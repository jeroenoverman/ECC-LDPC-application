#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>

#include "awgn.h"

TEST_CASE("AWGN channel")
{
    double signal[17] = {-1, 1, 1, 1, -1, -1, -1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1};

    AWGN awgn;
    awgn.apply(signal, 17, 5);
}

