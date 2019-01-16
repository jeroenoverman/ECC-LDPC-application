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
