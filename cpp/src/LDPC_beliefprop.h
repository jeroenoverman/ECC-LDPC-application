#ifndef LDPC_BELIEFPROP_H__
#define LDPC_BELIEFPROP_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "alist.h"

class LDPC_BeliefProp {
    /* Constants */
    static const int DEFAULT_ITERATIONS = 3;

    int n_iterations = DEFAULT_ITERATIONS; // Maximum number of iterations
    int completed_iterations = 0;

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

    void prepare(); // Preperations before first step 1
    void step_1(); // Do step 1
    void step_2(); // Do step 2
    void iterate(); // Do a whole iteration
    void run(int iterations = 0); // Do n itterations (whole decode process)

    void incrIterations() {completed_iterations++;};

    void finalize();
    int translate(double); // Translate belief prop to binary

#if 0
    int * getResult(int *result_size = NULL) {
        if (result_size != NULL)
            *result_size = H->getN();
        return result;
    }
#endif
    double * getResult(int *result_size = NULL) {
        if (result_size != NULL)
            *result_size = H->getN();
        return beliefMat_sumvec;
    }

    AlistMatrix * getBeliefMat() {
        return beliefMat;
    }

    double * getSumVec(int *sumvec_size = NULL) {
        if (sumvec_size != NULL)
            *sumvec_size = H->getN();
        return beliefMat_sumvec;
    }

    void print_sumvec(void);
    void print_result(void);

    private:
    void init();
};

#endif /* LDPC_BELIEFPROP_H__ */
