#ifndef LDPC_BELIEFPROP_H__
#define LDPC_BELIEFPROP_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "alist.h"

class LDPC_BeliefProp {
    int n_iterations; // Maximum number of iterations

    double *L; // Likelehood vector

    public:
    /* Public for debugging */
    AlistMatrix *H; // Parity check matrix (should become alist)
    AlistMatrix *beliefMat; // Belief matrix (should become alist)
    double *beliefMat_sumvec; // Sum of column and L (vector)
    int *result;

    LDPC_BeliefProp(AlistMatrix *pcm_h, double *likelihood);
    ~LDPC_BeliefProp();

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

    void finalize();
    int translate(double); // Translate belief prop to binary

    void print_sumvec(void);
    void print_result(void);

    private:
    void init();
};

#endif /* LDPC_BELIEFPROP_H__ */
