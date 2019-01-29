#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>
#include <vector>

#include "alist.h"
#include "bpsk.h"
#include "awgn.h"
#include "LDPC_encode.h"
#include "LDPC_beliefprop.h"


// Belief Prop. test
double ml_H[] = {
    1,1,0,1,0,0,0,
    0,1,1,0,1,0,0,
    0,0,1,1,0,1,0,
    0,0,0,1,1,0,1,
    1,0,0,0,1,1,0,
    0,1,0,0,0,1,1,
    1,0,1,0,0,0,1,
};

double ml_L[] = {
    +0.9, +0.1, +0.3, +0.8, +1.0, -0.2, -0.3
};

TEST_CASE("Belief Propagation")
{
#if 0
    cout << "Starting beliefe propegation" << endl;

    SimpleMatrix sm_h(7, 7, ml_H);
    sm_h.print();

    AlistMatrix al_h;
    al_h.simple2alist(&sm_h);
    cout << "H matrix" << endl;
    al_h.print();
    al_h.alist2simple_M()->print();

    LDPC_BeliefProp bp(&al_h, ml_L);

    cout << "Initial belfiefMat" << endl;
    bp.beliefMat->print();
    bp.beliefMat->alist2simple_M()->print();

    bp.step_1();

    cout << "";
    cout << "Iter 1 beliefMat after step 1" << endl;
    bp.beliefMat->print();
    bp.beliefMat->alist2simple_M()->print();

    bp.step_2();

    cout << "";
    bp.print_sumvec();
    cout << "Iter 1 beliefMat after step 2" << endl;
    bp.beliefMat->print();
    bp.beliefMat->alist2simple_M()->print();
#endif

    SimpleMatrix sm_h(7, 7, ml_H);
    AlistMatrix al_h;

    al_h.simple2alist(&sm_h);
    LDPC_BeliefProp bp(&al_h, ml_L);

    bp.run(2);
    //bp.finalize();

    // Check correctness result
    int result_size;
    double *result;
    result = bp.getResult(&result_size);
    int *result_int = new int[result_size];

    BPSK::decode(result_int, result, result_size);

    for (int i=0; i<result_size; i++) {
        REQUIRE(result_int[i] == 0);
    }

    /* Check correctness final matrix after 2 iterations */
    // Compare matrix generated using Matlab
    const double compare_mat[7][3] =
        {{0.3, 0.0, 0.2}, {0.3, -0.2, 0.8}, {0.5, 0.6, 0.4}, {0.4, 0.1, -0.1}, {-0.2, -0.1, 0.0}, {0.1, 0.7, 0.8}, {0.7, 1.0, 0.2}};

#define CMP_DELTA(v1, v2, d) (abs((v1)-(v2)) <= (d))

    AlistMatrix *belief_mat = bp.getBeliefMat();
    for (int i=0; i<belief_mat->getN(); i++) {
        for (int j=0; j<belief_mat->num_nlist[i]; j++) {
            //cout << "BM: " << *belief_mat->nlist[i][j].value << " COMP: " << compare_mat[i][j] << endl;
            REQUIRE(CMP_DELTA(*belief_mat->nlist[i][j].value, compare_mat[i][j], 0.0001) == true);
        }
    }

}

// 324
#include "test_U.h"
TEST_CASE("Belief Large H without AWGN")
{
    AlistMatrix al("H_n648-z27-r1_2.alist");
    int *encoded_msg = new int[al.getN()];
    LDPC_encode::encode(encoded_msg, test_U, &al);

    /* BPSK encoding */
    double *encoded_msg_flt =  new double[al.getN()];
    BPSK::encode(encoded_msg_flt, encoded_msg, al.getN());

#if 1
    /* Modify some variables in the msg */
    encoded_msg_flt[3] = -1*encoded_msg_flt[3];
    encoded_msg_flt[8] = -1*encoded_msg_flt[8];
#endif

#if 0
    cout << "Msg: [" << endl;
    for (int i=0; i<al.getN(); i++) {
        cout << encoded_msg_flt[i] << ", ";
    }
    cout << "]" << endl;
#endif

    /* Run belief prop */
    LDPC_BeliefProp bp(&al, encoded_msg_flt);
    bp.run(2);

    int result_size;
    double *result;
    result = bp.getResult(&result_size);

    REQUIRE(result_size == al.getN());

    int *decoded_msg =  new int[al.getN()];
    BPSK::decode(decoded_msg, result, al.getN());

#if 0
    cout << "Result: [" << endl;
    for (int i=0; i<result_size; i++) {
        cout << result[i] << ", ";
        REQUIRE(encoded_msg[i] == decoded_msg[i]);
    }
    cout << "]" << endl;
#endif

    delete encoded_msg_flt;
    delete encoded_msg;
    delete decoded_msg;

}

TEST_CASE("Belief Large H with AWGN")
{
    const int bp_it = 8;

    AlistMatrix al("H_n648-z27-r1_2.alist");
    vector<double> SNRdb_table {-5, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3};

    for (auto snr : SNRdb_table) {

        int *encoded_msg = new int[al.getN()];
        LDPC_encode::encode(encoded_msg, test_U, &al);

        /* BPSK encoding */
        double *encoded_msg_flt =  new double[al.getN()];
        BPSK::encode(encoded_msg_flt, encoded_msg, al.getN());

        /* Put through AWGN channel */
        double *encoded_msg_flt_awgn = new double[al.getN()];
        AWGN::apply(encoded_msg_flt_awgn, encoded_msg_flt, al.getN(), snr);

        int *decoded_msg_no_bp =  new int[al.getN()];
        BPSK::decode(decoded_msg_no_bp, encoded_msg_flt_awgn, al.getN());

        double ber_no_bp = BPSK::ber(encoded_msg, decoded_msg_no_bp, al.getN());

        /* Run belief prop */
        LDPC_BeliefProp bp(&al, encoded_msg_flt_awgn);
        bp.run(bp_it);

        int result_size;
        double *result;
        result = bp.getResult(&result_size);

        REQUIRE(result_size == al.getN());

        int *decoded_msg =  new int[al.getN()];
        BPSK::decode(decoded_msg, result, al.getN());

        double ber_bp = BPSK::ber(encoded_msg, decoded_msg, al.getN());

        printf("SNR: %1.2f\tBER w/o bp: %1.8f\tBER w bp(%d): %1.8f\n",
                snr, ber_no_bp, bp_it, ber_bp);

        delete encoded_msg_flt;
        delete encoded_msg_flt_awgn;
        delete encoded_msg;
        delete decoded_msg_no_bp;
        delete decoded_msg;
    }

}
