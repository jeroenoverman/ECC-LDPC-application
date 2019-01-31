
// Belief propagation test program for LDPC codes
// Using Alist matrix format

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include "alist.h"
#include "bpsk.h"

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
            alist_entry *entry = &beliefMat->nlist[n][m];
            //int sumvec_idx = beliefMat->nlist[n][m].idx - 1;
            //cout << "IDX-1=" << sumvec_idx << " sumvec[n]=" << beliefMat_sumvec[n] << " old value=" << *entry->value;
            *entry->value = beliefMat_sumvec[n] - *entry->value;
            //cout << " new value=" << *entry->value << endl;
        }
    }
}

//https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
//template <typename T> int sgn(T val) {
//    return (T(0) < val) - (val < T(0));
//}
#define sgn(val) ((0.0 < val) - (val < 0.0))

/*
 * Step 2: Check -> Var
 */
int LDPC_BeliefProp::step_2() {

    // Loop row entries in H (For each check vector)
    for (int m = 0; m < H->getM(); m++) {
        double *Lnew_vec = new double[H->num_mlist[m]];
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
        delete [] Lnew_vec;
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

    // If the codeword is valid, return 1 (no more iterations needed)
    if (check_codeword()) {
        return 0;
    }
    return 1;
}

int LDPC_BeliefProp::check_codeword() {
    int valid_codeword = 1;

    int *decoded_codeword = new int[H->getN()];

    BPSK::decode(decoded_codeword, beliefMat_sumvec, H->getN());

    for (int m=0; m<H->getM(); m++) {
        int sum = 0;
        for(int n=0; n < H->num_mlist[m]; n++) {
            int idx = H->mlist[m][n].idx-1;
            sum += decoded_codeword[idx];
        }

        /* All sums should be zero in mod 2 for the codeword to be correct (parity) */
        if ((sum % 2) == 1) {
            valid_codeword = 0;
            break;
        }
    }

    delete [] decoded_codeword;

    return valid_codeword;
}

int LDPC_BeliefProp::iterate() {
    incrIterations();
    step_1();
    return step_2();
}

int LDPC_BeliefProp::run(int iterations) {
    completed_iterations = 0;
    for (int i=0; i<(iterations ? iterations : n_iterations); i++) {
        if (iterate() == 0) {
            break;
        }
    }
    return completed_iterations;
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
