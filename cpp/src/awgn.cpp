/* https://stackoverflow.com/questions/32889309/adding-gaussian-noise */
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <complex>

#include "awgn.h"

void AWGN::apply(double *data, int size, double Eb_N0_dB) {
    /* Setup RNG */
    auto dist = std::bind(std::uniform_real_distribution<double>{0.0,1.0},
                          std::mt19937(std::random_device{}()));

    /* I don't think the complex result is needed */
#ifdef COMPLEX_COMP
    std::complex<double> *awgn_signal = new std::complex<double>[size];

    /* Add white gaussian noise, 0dB variance */
    for (int i=0; i<size; i++) {
        double t = 1/sqrt(2);
        std::complex<double> n(t*dist(), t*dist());
        awgn_signal[i] = data[i] + pow(10, (-1.0 * Eb_N0_dB / 20)) * n;

        /* Extract the real part */
        data[i] = awgn_signal[i].real();
    }
    delete awgn_signal;
#else
    /* Add white gaussian noise, 0dB variance */
    for (int i=0; i<size; i++) {
        double n = 1/sqrt(2)*dist();
        data[i] = data[i] + pow(10, (-1.0 * Eb_N0_dB / 20)) * n;
    }
#endif
}

double AWGN::comp_var(double *data, int size) {
    double mean;
    double var;
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    mean = sum/size;

    for (int i = 0; i < size; i++) {
        var += pow(data[i] - mean, 2);

    }

    return var/size;
}

double AWGN::comp_stddev(double *data, int size) {
    return sqrt(comp_var(data, size));
}

