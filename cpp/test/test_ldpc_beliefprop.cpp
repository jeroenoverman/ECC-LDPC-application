#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>

#include "alist.h"
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
    bp.finalize();

    // Check correctness result
    int result_size;
    int *result;
    result = bp.getResult(&result_size);
    for (int i=0; i<result_size; i++) {
        REQUIRE(result[i] == 0);
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
        cout << endl;
    }
    cout << endl;

}
