#include <iostream>
#include <complex>
#include "bpsk.h"

void BPSK::encode(double *bpsk_samples, int *bin_samples, int n) {
    for (int i=0; i<n; i++) {
        if (bin_samples[i] > 0) {
            bpsk_samples[i] = -1.0;
        } else {
            bpsk_samples[i] = +1.0;
        }
    }
}

void BPSK::decode(int *bin_samples, double *bpsk_samples, int n) {
    for (int i=0; i<n; i++) {
        if (bpsk_samples[i] > 0) {
            bin_samples[i] = 0;
        } else {
            bin_samples[i] = 1;
        }
    }
}

double BPSK::ber(int *bin_samples1, int *bin_samples2, int n) {
    int err_cnt = 0;
    for (int i=0; i<n; i++) {
        if (bin_samples1[i] != bin_samples2[i])
            err_cnt++;
    }
    //std::cout << "errors: " << err_cnt << std::endl;
    return (double)err_cnt/(double)n;
}

double BPSK::ber_theoretical(double snr) {
    double snr_lin = pow(10.0, (snr/10.0));
    double th_ber = (0.5)*erfc(sqrt(snr_lin));
    return th_ber;
}
