#include "catch.hpp"

#include <iostream>
#include <random>
using namespace std;

#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "bpsk.h"
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

#if 0
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
#endif

TEST_CASE("Data app") {
    LDPC_app_base ab;

    vector<string> files = {"H_n648-z27-r1_2.alist"};
    ab.add_alist_files(files);
    LDPC_info ldpc_info;

    /* Random data instead of image of 2 blocks + 42 in size */
    int size = 324*2+42;
    int *r_bin_signal = new int[size];

    /* Generate random binary signal of 1 block (K size) */
    auto myrand = std::bind(std::uniform_int_distribution<int>{0, 1},
            std::mt19937(std::random_device{}()));

    for (int i=0; i<size; i++) {
        r_bin_signal[i] = myrand();
    }

    /* Return data */
    int *data_out_bp = new int[size];
    int *data_out_bf = new int[size];
    int *data_out_raw = new int[size];

    /* Apply and reconstruct */
    ab.run_data_app(ldpc_info,
            data_out_bp, data_out_bf, data_out_raw, r_bin_signal,
            size, 3, 12, ab.getMatrix("H_n648-z27-r1_2.alist"));

    ldpc_info.print();

#if 0
    double ber_bp   = BPSK::ber(r_bin_signal, data_out_bp, size);
    double ber_bf   = BPSK::ber(r_bin_signal, data_out_bf, size);
    double ber_raw  = BPSK::ber(r_bin_signal, data_out_raw, size);
    cout << "BER bp: " << ber_bp << " BER bf: " << ber_bf << " BER raw: " << ber_raw << endl;
#endif

    delete [] r_bin_signal;
    delete [] data_out_bp;
    delete [] data_out_bf;
    delete [] data_out_raw;
}
