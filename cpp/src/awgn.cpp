//http://www.dsplog.com/2007/08/05/bit-error-probability-for-bpsk-modulation/
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <complex>

#include "awgn.h"

//https://www.gaussianwaves.com/2015/06/how-to-generate-awgn-noise-in-matlaboctave-without-using-in-built-awgn-function/
//https://nl.mathworks.com/matlabcentral/fileexchange/25922-ber-of-bpsk-in-awgn-channel?s_tid=mwa_osa_a
void AWGN::apply(double *dst_signal, double *src_signal, int size, double Eb_N0_dB) {
    /* Setup RNG */
    auto randn = std::bind(std::normal_distribution<double>{0.0, sqrt(1.0)}, // mean 0, var 1
            std::mt19937(std::random_device{}()));

    // SNR = Eb_N0 + 3 + 10log10(k)
    //double snr = Eb_N0_dB + 3 + 10*log10(size);
    // Eb/N0 = SNR => 1/N0 = SNR => N0 = 1/SNR
    double snr = Eb_N0_dB;
    double lin_snr = pow(10, (snr/10));

    /* Compute symbol energy */
#if 0 /* Is always 1 for BPSK */
    double sum = 0.0;
    for (int i=0; i<size; i++) {
        sum += pow(abs(src_signal[i]), 2);
    }
    double Eb = sum/size;
#endif
    const double Eb = 1;
    double N0 = Eb/lin_snr;

    /* Add noise, input is real */
    double noiseSigma = sqrt(N0);
    for (int i=0; i<size; i++) {
        dst_signal[i] = src_signal[i] + noiseSigma * randn();
    }
}

