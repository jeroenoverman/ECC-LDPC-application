#ifndef AWGN_H__
#define AWGN_H__

#include <functional>
#include <iostream>
#include <iterator>
#include <random>

// SNR = mean/stddev

class AWGN {
    //double mean = 0.0;
    //double stddev = 0.1;
    double _Eb_N0_dB = 10;

    double comp_stddev(double *data, int size);
    double comp_var(double *data, int size);

    public:
        //AWGN();
        //AWGN(double snr);
        void apply(double *data, int size, double Eb_N0_dB);
        void apply(double *data, int size) {
            apply(data, size, _Eb_N0_dB);
        }

};

#endif /* AWGN_H__ */
