#ifndef LDPC_ENCODE_H__
#define LDPC_ENCODE_H__

#include "alist.h"

class LDPC_encode {

    public:
        static void encode(int *codeword, int *msg, AlistMatrix *H);
        static void decode(int *msg, int *codeword, AlistMatrix *H);

};

#endif /* LDPC_ENCODE_H__ */
