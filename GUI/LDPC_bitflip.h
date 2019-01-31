#ifndef LDPC_BITFLIP_H__
#define LDPC_BITFLIP_H__

#include "alist.h"

class LDPC_BitFlip {
    public:
        AlistMatrix *H;
        int *correct_codeword;
        int *codeword;

        LDPC_BitFlip(AlistMatrix *pcm_h, int *cw) {
            H = pcm_h;
            codeword = cw;

            correct_codeword = new int[H->getN()];
            for (int i=0; i<H->getN(); i++) {
                correct_codeword[i] = codeword[i];
            }
        }

        ~LDPC_BitFlip() {
            delete [] correct_codeword;
        }

        int iterate();
        int run(int iterations = 20);
        int *result() {
            return correct_codeword;
        }

};

#endif /* LDPC_BITFLIP_H__ */
