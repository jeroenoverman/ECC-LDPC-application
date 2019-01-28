#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>
#include <vector>

#include "alist.h"
#include "bpsk.h"
#include "awgn.h"
#include "LDPC_encode.h"
#include "LDPC_bitflip.h"


// Belief Prop. test
double ml_H[] = {
1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
};

int ml_Y[] = {
    1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

TEST_CASE("BitFlip")
{
    SimpleMatrix sm_h(15, 20, ml_H);
    AlistMatrix al_h;
    al_h.simple2alist(&sm_h);

    //al_h.print();
    LDPC_BitFlip bf(&al_h, ml_Y);

    int iter = bf.run(5);
    int *new_codeword = bf.result();

    REQUIRE(iter == 4);

#if 0
    cout << "Completed BF in " << iter << " iterations" << endl;
    cout << "Orig codeword: [" << endl;
    for (int i=0; i<20; i++) {
        cout << ml_Y[i] << ", ";
    }
    cout << "]" << endl;

    cout << "New codeword: [" << endl;
    for (int i=0; i<20; i++) {
        cout << new_codeword[i] << ", ";
    }
    cout << "]" << endl;
#endif

    for (int i=0; i<20; i++) {
        // Should be the all zero codeword
        REQUIRE(new_codeword[i] == 0);
    }

}

// 324
#include "test_U.h"
TEST_CASE("BitFlip Large H without AWGN")
{
    AlistMatrix al("H_n648-z27-r1_2.alist");

    int *encoded_msg = new int[al.getN()];
    int *encoded_msg_cmp = new int[al.getN()];

    //al.print();

    LDPC_encode::encode(encoded_msg, test_U, &al);

    for (int i=0; i<al.getN(); i++) {
        encoded_msg_cmp[i] = encoded_msg[i];
    }

#if 0
    cout << "Msg size: " << al.getN() << endl;
    cout << "Msg: [" << endl;
    for (int i=0; i<al.getN(); i++) {
        cout << encoded_msg[i] << ", ";
    }
    cout << "]" << endl;
#endif

    encoded_msg[2] = (encoded_msg[2]+1)%2;
    encoded_msg[8] = (encoded_msg[8]+1)%2;

#if 0
    cout << "Msg with error: [" << endl;
    for (int i=0; i<al.getN(); i++) {
        cout << encoded_msg[i] << ", ";
    }
    cout << "]" << endl;
#endif

    /* Run belief prop */
    LDPC_BitFlip bf(&al, encoded_msg);
    int iter = bf.run();
    int *result = bf.result();

    REQUIRE(iter == 2);

    //cout << "Completed BF in " << iter << " iterations" << endl;

#if 0
    cout << "Result: [" << endl;
    for (int i=0; i<al.getN(); i++) {
        cout << result[i] << ", ";
    }
    cout << "]" << endl;
#endif

    for (int i=0; i<al.getN(); i++) {
        //REQUIRE(encoded_msg_cmp[i] == result[i]);
        if (encoded_msg_cmp[i] != result[i]) {
            cout << "Unequal at idx: " << i << endl;
        }
        REQUIRE(encoded_msg_cmp[i] == result[i]);
    }


    delete encoded_msg;

}

TEST_CASE("BitFlip Large H with AWGN")
{
    AlistMatrix al("H_n648-z27-r1_2.alist");
    vector<double> SNRdb_table {-5, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8};

    int info_size = 324;
    int *r_bin_signal = new int[info_size];

    /* Generate random binary signal of 1 block (K size) */
    auto myrand = std::bind(std::uniform_int_distribution<int>{0, 1},
            std::mt19937(std::random_device{}()));

    for (int i=0; i<info_size; i++) {
        r_bin_signal[i] = myrand();
    }

    for (auto snr : SNRdb_table) {

        int *encoded_msg = new int[al.getN()];
        LDPC_encode::encode(encoded_msg, r_bin_signal, &al);

        /* BPSK encoding */
        double *encoded_msg_flt =  new double[al.getN()];
        BPSK::encode(encoded_msg_flt, encoded_msg, al.getN());

        /* Put through AWGN channel */
        double *encoded_msg_flt_awgn = new double[al.getN()];
        AWGN::apply(encoded_msg_flt_awgn, encoded_msg_flt, al.getN(), snr);

        int *decoded_msg_no_bp =  new int[al.getN()];
        BPSK::decode(decoded_msg_no_bp, encoded_msg_flt_awgn, al.getN());

        double ber_no_bp = BPSK::ber(r_bin_signal, decoded_msg_no_bp, al.getK());

        /* Run BitFlip prop */
        LDPC_BitFlip bf(&al, decoded_msg_no_bp);
        int iter = bf.run();

        //cout << "Completed BF in " << iter << " iterations" << endl;

        int *result = bf.result();

        double ber_bf = BPSK::ber(encoded_msg, result, al.getN());

        printf("SNR: %1.2f\tBER w/o bf: %1.8f\tBER w bf(%d): %1.8f\n",
                snr, ber_no_bp, iter, ber_bf);

        delete encoded_msg_flt;
        delete encoded_msg_flt_awgn;
        delete encoded_msg;
        delete decoded_msg_no_bp;
    }

}
