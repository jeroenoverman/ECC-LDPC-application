#ifndef AWGN_H__
#define AWGN_H__

#include <functional>
#include <iostream>
#include <iterator>
#include <random>

class AWGN {
    double _Eb_N0_dB = 10;

    public:
        //AWGN();
        //AWGN(double snr);
        void apply(double *dst_signal, double *src_signal, int size, double Eb_N0_dB);
        void apply(double *dst_signal, double *src_signal, int size) {
            apply(dst_signal, src_signal, size, _Eb_N0_dB);
        }
};

#endif /* AWGN_H__ */
