
// Belief propagation test program for LDPC codes
// Using Alist matrix format

#include <iostream>
#include <vector>
#include <cmath>
#include "alist.h"

#include "LDPC_beliefprop.h"

using namespace std;

LDPC_BeliefProp::LDPC_BeliefProp(AlistMatrix *pcm_h, double *likelihood) {
    H = pcm_h;
    L = likelihood;
    n_iterations = 2;

    init(); // Allocate space
}

void LDPC_BeliefProp::init() {
    int m, n, bn_m, bn_n;

    m = H->getM();
    n = H->getN();
    bn_m = H->getBiggestNumM();
    bn_n = H->getBiggestNumN();

    beliefMat = new AlistMatrix(*H);
    beliefMat->clear();
    beliefMat_sumvec = new double[H->getN()];
    prepare();
}

/*
 * Initial preparations for iteration 1
 */
void LDPC_BeliefProp::prepare() {
    copy(L, L + H->getN(), beliefMat_sumvec); // sumvec = L
}

/*
 * Step 1: Var -> Check
 *  sumvec - column elements
 */
void LDPC_BeliefProp::step_1() {
#if 0
    int n_col = H->getN();
    int m_row = H->getM();
    // Loop column entries in H (For each column (variable vector)
    for (int col = 0; col < n_col; col++) {
        // Loop row entries in H for current variable vector
        // (Subtract Belief Entry from sumvec (L in first iteration)
        for (int row = 0; row < m_row; row++) {
            //beliefMat[current_location] -= beliefMat_sumvec[n_columna];
        }
    }
#endif
    /*
     * Loop the row entry elements, so step trough the matrix left->right top->bottom (lines)
     */
    int n_col = H->getN();

    for (int n=0; n<n_col; n++) {
        // Loop the actual entries (columns)
        for (int m=0; m<H->num_nlist[n]; m++) {
            int sumvec_idx = beliefMat->nlist[n][m].idx - 1;
            alist_entry *entry = &beliefMat->nlist[n][m];
            cout << "IDX-1=" << sumvec_idx << " sumvec[n]=" << beliefMat_sumvec[n] << " old value=" << *entry->value;
            *entry->value = beliefMat_sumvec[n] - *entry->value;
            cout << " new value=" << *entry->value << endl;
        }
    }
}

//https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#ifdef STEP2
/*
 * Step 2: Check -> Var
 */
void LDPC_BeliefProp::step_2() {

    // Loop row entries in H (For each check vector)
    for () {
        vector<double> Lnew_vec;
        // Loop column entries in H (For each variable entry in check vector)
        for () {
            double minv = 99999;
            int signv = 1;
            // Loop the column entries and combine
            for () {
                // Don't include current entry
                if (current_entry != loop_entry) {
                    int tmpval = abs(current_value);
                    if (tmpval < minv) {
                        minv = tmpval;
                    }
                    signv = signv * sgn(current_value);
                }
            }
            Lnew_vec.push_back(signv * minv);
        }

        // Assign the new likelehoods
        // Loop the column entries in H
        for () {
            //beliefMat[row,col_entry] = Lnew_vec(new_entry);
        }
    }

    // Sum and est
}
#endif /*STEP2*/

void LDPC_BeliefProp::iterate() {

}

void LDPC_BeliefProp::run() {

}
