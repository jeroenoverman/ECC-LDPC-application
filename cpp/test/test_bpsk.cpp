#include "catch.hpp"

#include <iostream>
#include <cstring>
using namespace std;

#include "bpsk.h"

int test_bin_samples[10] = {0, 1, 0, 1, 1, 0, 1, 0, 0, 0};
double test_bpsk_samples[10] = {1, -1, 1, -1, -1, 1, -1, 1, 1, 1};

#define CMP_DELTA(v1, v2, d) (abs((v1)-(v2)) <= (d))

TEST_CASE("BPSK Channel")
{
    int test_bin_samples_out[10];
    double test_bpsk_samples_out[10];

    BPSK::encode(test_bpsk_samples_out, test_bin_samples, 10);
    for (int i=0; i<10; i++) {
        REQUIRE(CMP_DELTA(test_bpsk_samples_out[i], test_bpsk_samples[i], 0.0001) == true);
    }

    BPSK::decode(test_bin_samples_out, test_bpsk_samples_out, 10);
    for (int i=0; i<10; i++) {
        REQUIRE(test_bin_samples_out[i] == test_bin_samples[i]);
    }
}

