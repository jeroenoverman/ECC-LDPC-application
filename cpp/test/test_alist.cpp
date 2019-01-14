#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>

#include "alist.h"
#include "LDPC_beliefprop.h"

TEST_CASE("Simple Matrix")
{

    double simple_mat[] =
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
    double exmat[] =
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

    double *smmat = sm.getMatrix();
    double *sm2mat = sm2->getMatrix();

    for (int i=0; i<(16*8); i++) {
        REQUIRE(sm2mat[i] == smmat[i]);
    }
}


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

#if 1
TEST_CASE("Belief Propagation")
{
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


    // ITER 2 //

    bp.step_1();

    cout << "";
    cout << "Iter 2 beliefMat after step 1" << endl;
    bp.beliefMat->print();
    bp.beliefMat->alist2simple_M()->print();

    bp.step_2();

    cout << "";
    bp.print_sumvec();
    cout << "Iter 2 beliefMat after step 2" << endl;
    bp.beliefMat->print();
    bp.beliefMat->alist2simple_M()->print();

}
#endif
