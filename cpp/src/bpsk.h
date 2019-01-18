#ifndef BPSK_H__
#define BPSK_H__
/*
 * BPSK channel
 *
 * Encode:
 *  1 => -1
 *  0 => +1
 *
 * Decode:
 *  -1 => 1
 *   1 => 0
 *   0 == ? (Now we set it to 1)
 */

class BPSK {
    public:
        static void encode(double *bpsk_samples, int *bin_samples, int n);
        static void decode(int *bin_samples, double *bpsk_samples, int n);
        static double ber(int *bin_samples1, int *bin_samples2, int n);
        static double ber_theoretical(double snr);
};

#endif /* BPSK_H__ */
