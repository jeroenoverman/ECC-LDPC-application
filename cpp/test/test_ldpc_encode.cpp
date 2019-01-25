#include "catch.hpp"

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


#include "alist.h"
#include "LDPC_encode.h"

// H = 324x648 ==> M=324 N=648
#include "test_H.h"

// 324
#include "test_U.h"

TEST_CASE("LDPC Encoding")
{
    SimpleMatrix sm_h(324, 648, (double *)test_H);

    AlistMatrix al_h;
    al_h.simple2alist(&sm_h);

    int *encoded_msg = new int[648];
    LDPC_encode::encode(encoded_msg, test_U, &al_h);

#if 0
    cout << "Codeword: [" << endl;
    for (int i=0; i<648; i++) {
        cout << encoded_msg[i] << ", ";
    }
    cout << "]" << endl;
#endif

    for (int i=0; i<324; i++) {
        REQUIRE(test_U[i] == encoded_msg[i]);
    }

    int *decoded_msg = new int[324];
    LDPC_encode::decode(decoded_msg, encoded_msg, &al_h);
    for (int i=0; i<324; i++) {
        REQUIRE(test_U[i] == decoded_msg[i]);
    }
    delete decoded_msg;

    delete encoded_msg;
}

TEST_CASE("LDPC Encoding with alist")
{
    AlistMatrix al("H_n648-z27-r1_2.alist");

    int *encoded_msg = new int[al.getN()];
    LDPC_encode::encode(encoded_msg, test_U, &al);

#if 0
    cout << "Codeword: [" << endl;
    for (int i=0; i<al.getN(); i++) {
        cout << encoded_msg[i] << ", ";
    }
    cout << "]" << endl;
#endif

    for (int i=0; i<al.getK(); i++) {
        REQUIRE(test_U[i] == encoded_msg[i]);
    }

    /* Compare */
    SimpleMatrix sm_h(324, 648, (double *)test_H);

    AlistMatrix al_h;
    al_h.simple2alist(&sm_h);

    int *encoded_msg_cmp = new int[648];
    LDPC_encode::encode(encoded_msg_cmp, test_U, &al_h);

    REQUIRE(al.getN() == al_h.getN());
    REQUIRE(al.getM() == al_h.getM());

    for (int i=0; i<al.getN(); i++) {
        REQUIRE(encoded_msg_cmp[i] == encoded_msg[i]);
    }

    delete encoded_msg;
    delete encoded_msg_cmp;

}
