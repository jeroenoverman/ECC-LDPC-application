
// Belief propagation test program for LDPC codes
// Using Alist matrix format

#include <iostream>
#include <vector>
#include <cmath>
#include "alist.h"

using namespace std;


class LDPC_BeliefProp {
    int n_iterations; // Maximum number of iterations
    
    double *L; // Likelehood vector
    
    public:
        /* Public for debugging */
        AlistMatrix *H; // Parity check matrix (should become alist)
        AlistMatrix *beliefMat; // Belief matrix (should become alist)
        double *beliefMat_sumvec; // Sum of column and L (vector)
        
        LDPC_BeliefProp(AlistMatrix *pcm_h, double *likelihood);
        
        void setIterations(int it) {
            n_iterations = it;
        }
        
        void setParityCheckMatrix() {
        }
        
        void prepare(); // Preperations before first step 1
        void step_1(); // Do step 1
        void step_2(); // Do step 2
        void iterate(); // Do a whole iteration
        void run(); // Do n itterations (whole decode process)
        
    private:
        void init();
};

LDPC_BeliefProp::LDPC_BeliefProp(AlistMatrix *pcm_h, double *likelihood) {
    H = pcm_h;
    L = likelihood;
    n_iterations = 2;
    
    init(); // Allocate space
}


void LDPC_BeliefProp::init() {
    beliefMat = new AlistMatrix(*H); // TODO Make able to init alist empty
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
            
            *entry->value = beliefMat_sumvec[sumvec_idx] - *entry->value;
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

int ml_H[] = {
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

int main() 
{
    cout << "Starting beliefe propegation" << endl;
    
    SimpleMatrix sm_h(7, 7, ml_H);
    AlistMatrix al_h;
    al_h.simple2alist(&sm_h);
    LDPC_BeliefProp bp(&al_h, ml_L);
    
    cout << "Initial belfiefMat" << endl;
    bp.beliefMat->print();
    
    bp.step_1();
    
    cout << "H matrix" << endl;
    bp.H->print();
    cout << "After step 1" << endl;
    bp.beliefMat->print();
    

    return 1;

}
