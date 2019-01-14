
// Belief propagation test program for LDPC codes
// Using Alist matrix format

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include "alist.h"

#include "LDPC_beliefprop.h"

using namespace std;

LDPC_BeliefProp::LDPC_BeliefProp(AlistMatrix *pcm_h, double *likelihood) {
    H = pcm_h;
    L = likelihood;
    init(); // Allocate space
}

LDPC_BeliefProp::~LDPC_BeliefProp() {
    delete beliefMat;
    delete beliefMat_sumvec;
    delete result;
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
    result = new int[H->getN()];
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

/*
 * Step 2: Check -> Var
 */
void LDPC_BeliefProp::step_2() {

    // Loop row entries in H (For each check vector)
    for (int m = 0; m < H->getM(); m++) {
        double Lnew_vec[H->num_mlist[m]];
        // Loop column entries in H (For each variable entry in check vector)
        for (int midx = 0; midx < H->num_mlist[m]; midx++) {
            double minv = std::numeric_limits<double>::max();
            int signv = 1;
            // Loop the column entries and combine
            for (int midx_cmp = 0; midx_cmp < H->num_mlist[m]; midx_cmp++) {
                // Don't include current entry
                if (midx != midx_cmp) {
                    alist_entry *entry = &beliefMat->mlist[m][midx_cmp];
                    //double cval = H->mlist[m][midx_cmp];
                    double cval_abs = abs(*entry->value);
                    if (cval_abs < minv) {
                        minv = cval_abs;
                    }
                    signv = signv * sgn(*entry->value);
                }
            }
            Lnew_vec[midx] = signv * minv;
        }

        // Assign the new likelehoods
        // Loop the column entries in H
        for (int midx = 0; midx < H->num_mlist[m]; midx++) {
            //beliefMat[row,col_entry] = Lnew_vec(new_entry);
            *beliefMat->mlist[m][midx].value = Lnew_vec[midx];
        }
    }

    // Sum and est
    // sumvec is sum of column (N list) and L
    int n_col = H->getN();
    for (int n = 0; n < n_col; n++) {
        // sum the N list
        double n_sum = 0;
        for (int nidx = 0; nidx < H->num_nlist[n]; nidx++) {
            n_sum += *beliefMat->nlist[n][nidx].value;
        }

        beliefMat_sumvec[n] = n_sum + L[n];
    }

}

void LDPC_BeliefProp::iterate() {
    step_1();
    step_2();
    incrIterations();
}

void LDPC_BeliefProp::run(int iterations) {
    for (int i=0; i<(iterations ? iterations : n_iterations); i++) {
        iterate();
    }
}

void LDPC_BeliefProp::finalize(void) {
    for (int i=0; i<H->getN(); i++) {
        result[i] = translate(beliefMat_sumvec[i]);
    }
}

/* TODO: what should happen if the value is exactly zero? */
int LDPC_BeliefProp::translate(double ll) {
    if (ll < 0)
        return 1;
    else
        return 0;
}

void LDPC_BeliefProp::print_sumvec(void) {
    int i;
    cout << "Sum Vector: [";
    for (i=0; i<H->getN()-1; i++) {
        cout << beliefMat_sumvec[i] << ", ";
    }
    cout << beliefMat_sumvec[i] << "]" << endl;
}

void LDPC_BeliefProp::print_result(void) {
    int i;
    cout << "Result: [";
    for (i=0; i<H->getN()-1; i++) {
        cout << result[i] << ", ";
    }
    cout << result[i] << "]" << endl;
}
