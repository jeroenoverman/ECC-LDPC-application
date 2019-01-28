#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "LDPC_app_base.h"

TEST_CASE("Alist name parsing")
{
    LDPC_app_base ab;

    vector<string> files = {"H_n648-z27-r5_6.alist", "H_n648-z27-r1_2.alist", "aa"};
    ab.add_alist_files(files);
    //ab.print_specs();

    vector<struct h_matrix> *matrices = ab.getMatrices();
    REQUIRE((matrices->at(0)).N == 648);
    REQUIRE((matrices->at(0)).Z == 27);
    REQUIRE((matrices->at(0)).R == 5.0/6.0);

    REQUIRE((matrices->at(1)).N == 648);
    REQUIRE((matrices->at(1)).Z == 27);
    REQUIRE((matrices->at(1)).R == 1.0/2.0);
}

TEST_CASE("BER Simulation avg app")
{
    LDPC_app_base ab;
    vector<string> files = {"H_n648-z27-r1_2.alist", "H_n648-z27-r5_6.alist"};
    ab.add_alist_files(files);

    vector<double> SNRdb_list {-5, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 5, 7, 10, 11, 12, 14, 16};

    // 5 runs per SNR, 8 iterations per belief prop decoding
    LDPC_info ldpc_info_r1_2;
    ab.run_bersim_app(ldpc_info_r1_2, SNRdb_list, 10, 8, ab.getMatrix("H_n648-z27-r1_2.alist"));
    ldpc_info_r1_2.print();

    LDPC_info ldpc_info_r5_6;
    ab.run_bersim_app(ldpc_info_r5_6, SNRdb_list, 10, 8, ab.getMatrix("H_n648-z27-r5_6.alist"));
    ldpc_info_r5_6.print();

    REQUIRE(true == true);
}
