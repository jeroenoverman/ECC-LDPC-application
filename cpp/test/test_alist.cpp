#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>

#include "alist.h"

TEST_CASE("Simple Matrix")
{

    int simple_mat[] =
    {
        1, -1, 2,
        1, -3, 1
    };

    SimpleMatrix sm(3, 2, simple_mat);

    REQUIRE(sm.getM() == 2);
    REQUIRE(sm.getN() == 3);
    REQUIRE(sm.getMatrix() == simple_mat);
}

TEST_CASE("Simple Matrix to Alist Matrix")
{
    int exmat[] =
    {
        0,  0,  0,  27, 0,  0,  1,  0,  0,  36, 0,  0,  0,  0,  0,  49,
        0,  0,  0,  60, 45, 0,  0,  0,  32, 0,  0,  0,  0,  0,  23, 0,
        0,  6,  0,  0,  0,  21, 56, 0,  0,  0,  0,  0,  0,  47, 0,  0,
        32, 0,  0,  0,  0,  0,  0,  23, 0,  0,  60, 0,  0,  0,  0,  45,
        0,  0,  52, 0,  0,  0,  0,  0,  61, 0,  26, 0,  0,  11, 0,  0,
        39, 0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  24, 0,  0,  11, 0,
        0,  36, 0,  0,  45, 0,  0,  10, 0,  0,  0,  0,  58, 0,  0,  0,
        0,  0,  62, 0,  0,  0,  0,  0,  0,  12, 0,  53, 27, 0,  0,  0,
    };

    SimpleMatrix sm(16, 8, exmat);

    //sm.print();
    cout << endl << endl;

    AlistMatrix al;
    al.simple2alist(&sm);
    //al.print();

    SimpleMatrix *sm2 = al.alist2simple_M();
    //sm2->print();

    REQUIRE(sm.getMatrix() == exmat);

    int *smmat = sm.getMatrix();
    int *sm2mat = sm2->getMatrix();

    for (int i=0; i<(16*8); i++) {
        REQUIRE(sm2mat[i] == smmat[i]);
    }
}

