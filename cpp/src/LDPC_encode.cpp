#include "alist.h"
#include "LDPC_encode.h"

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


#if 0
void LDPC_encode::encode(int *codeword, int *msg, AlistMatrix *H) {

    cout << "M: " << H->getM() << endl;
    cout << "N: " << H->getN() << endl;

    int m = H->getM();
    int n = H->getN();

    /* Compute the gap */
    /* Gap is M - the index of the first non-zero entry in the last column */
    int g = H->nlist[n-1][0].idx;
    g = m - g;

    cout << "g: " << g << endl;

    /* Other variables: width_x and end_x */
    int wa = n-m;
    int wb = g;
    int ea = wa;
    int eb = wa + wb;
}
#endif

//void LDPC_encode::encode(std::vector<uint8_t> info_bits) {
void LDPC_encode::encode(int *codeword, int *msg, AlistMatrix *H) {
    // Does encoding by back substitution
    // Assumes a very specific structure on the partiy check matrix

    //H->print();

    int _M = H->getM();
    int _N = H->getN();
    int _K = _N/2;
    int _Z = 27;

#if 0
    cout << "M: " << _M << endl;
    cout << "N: " << _N << endl;
    cout << "K: " << _K << endl;
    cout << "Z: " << _Z << endl;

    cout << "Info: [" << endl;
    for (int i=0; i<_M; i++) {
        cout << msg[i] << ", ";
    }
    cout << "]" << endl;
#endif

    memset(codeword, 0, _N * sizeof(codeword[0]));
    memcpy(codeword, msg, _M * sizeof(msg[0]));

    std::vector<uint8_t > parity(_M, 0);

    for(int i_row = 0; i_row < _M; ++i_row) {
        for(int i_col = 0; i_col < H->num_mlist[i_row]; ++i_col) {
            if (H->mlist[i_row][i_col].idx-1 < _K)
                parity.at(i_row) += codeword[H->mlist[i_row][i_col].idx-1];
        }
        parity.at(i_row) = (uint8_t) (parity.at(i_row) % 2);
    }

    for (int i_col = 0; i_col < _Z; ++i_col) {
        for (int i_row = i_col; i_row < _M; i_row = i_row + _Z) {
            codeword[_K + i_col] += parity.at(i_row);
        }
        codeword[_K + i_col] = (uint8_t ) (codeword[_K + i_col] % 2);
    }

    for(int i_row = 0; i_row < _M; ++i_row) {
        for(int i_col = 0; i_col < H->num_mlist[i_row]; ++i_col) {
            if ((H->mlist[i_row][i_col].idx-1 >= _K) && (H->mlist[i_row][i_col].idx-1 < _K + _Z))
                parity.at(i_row) += codeword[H->mlist[i_row][i_col].idx-1];
        }
        parity.at(i_row) = (uint8_t) (parity.at(i_row) % 2);
    }


    for (int i_col = _K + _Z; i_col < _N; i_col = i_col + _Z  ) {
        for (int i_row = 0; i_row < _Z; ++i_row) {
            codeword[i_col + i_row] = parity.at(i_col + i_row - _K - _Z);
            parity.at(i_col + i_row - _K ) = (uint8_t) (( parity.at(i_col + i_row - _K) + parity.at(i_col + i_row - _K - _Z)) %2);
         }
    }
}

void LDPC_encode::decode(int *msg, int *codeword, AlistMatrix *H) {
    for (int i=0; i<H->getK(); i++) {
        msg[i] = codeword[i];
    }
}

