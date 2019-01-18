#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>
#include <fstream>
#include <random>
#include <complex>

#include "bpsk.h"
#include "awgn.h"

#define SIGNAL_SIZE 100000

#define CMP_DELTA(v1, v2, d) (abs((v1)-(v2)) <= (d))
#define N_CMP_SNR_THBER 10
const double SNR_LIN_CMP[N_CMP_SNR_THBER] = {1,1.258925411794167,1.584893192461114,1.995262314968880,2.511886431509580,3.162277660168380,3.981071705534972,5.011872336272722,6.309573444801933,7.943282347242816};
const double BER_TH_CMP[N_CMP_SNR_THBER] = {0.078649603525143,0.056281951976541,0.037506128358926,0.022878407561085,0.012500818040738,0.005953867147779,0.002388290780933,7.726748153784444e-04,1.909077740759931e-04,3.362722841961749e-05};

TEST_CASE("BER Theoretical")
{
    int snr;

    for (snr = 0; snr < N_CMP_SNR_THBER; snr++) {
        double th_ber = BPSK::ber_theoretical((double)snr);
        double snr_lin = AWGN::snr_db2lin((double)snr);
        //std::cout << "SNR: " << snr << " SNR_L: " << snr_lin << " TH_BER: " << th_ber << std::endl;

        REQUIRE(CMP_DELTA(snr_lin, SNR_LIN_CMP[snr], 0.000001) == true);
        REQUIRE(CMP_DELTA(th_ber, BER_TH_CMP[snr], 0.000001) == true);
    }
}

int *random_binary_signal(int size) {
    auto myrand = std::bind(std::uniform_int_distribution<int>{0, 1},
            std::mt19937(std::random_device{}()));

    int *r_int_signal = new int[SIGNAL_SIZE];
    for (int i=0; i<SIGNAL_SIZE; i++) {
        r_int_signal[i] = myrand();
    }

    return r_int_signal;
}


TEST_CASE("AWGN channel BER")
{
    const int n_samples = 100000;

    int *r_bin_signal;

    r_bin_signal = random_binary_signal(n_samples);

    double *r_signal = new double[n_samples];
    BPSK::encode(r_signal, r_bin_signal, n_samples);

    /* Do for different SNR */
    std::vector<double> SNRdb_table;
    std::vector<double> BER_table;
    std::vector<double> BERth_table;

    for (int i=0; i<10; i++) {
        SNRdb_table.push_back((double)i);
    }

    /* Reserve space for processing */
    double *snr_signal = new double[n_samples];
    int *decode_signal = new int[n_samples];

    /* For every SNR */
    for (auto snr_db : SNRdb_table) {
        /* Put through AWGN channel */
        AWGN::apply(snr_signal, r_signal, n_samples, snr_db);

        /* Decode */
        BPSK::decode(decode_signal, snr_signal, n_samples);

        /* Compute BER */
        // Sample ber
        double ber = BPSK::ber(r_bin_signal, decode_signal, n_samples);
        BER_table.push_back(ber);
        // Theoretical ber
        double ber_th = BPSK::ber_theoretical(snr_db);
        BERth_table.push_back(ber_th);

        //std::cout << "SNR: " << snr_db << "\tBER_th: " << ber_th << "\tBER: " << ber << std::endl;

        // After 5dB we need a lot more samples or runs
        if (snr_db <= 5) {
            REQUIRE(CMP_DELTA(ber, ber_th, 0.2*ber_th) == true);
        }

    }

    /* Cleanup */
    delete r_bin_signal;
    delete r_signal;
    delete snr_signal;
    delete decode_signal;
}

#if 0
TEST_CASE("AWGN channel")
{
    /* Generate a random signal */

    // RNG
    auto myrand = std::bind(std::uniform_int_distribution<int>{0, 1},
            std::mt19937(std::random_device{}()));

    int *r_int_signal = new int[SIGNAL_SIZE];
    for (int i=0; i<SIGNAL_SIZE; i++) {
        r_int_signal[i] = myrand();
    }

    double *r_signal = new double[SIGNAL_SIZE];
    BPSK::encode(r_signal, r_int_signal, SIGNAL_SIZE);

    // Add AWGN noise with different SNR
    double *snr1_signal = new double[SIGNAL_SIZE];
    double *snr5_signal = new double[SIGNAL_SIZE];
    double *snr10_signal = new double[SIGNAL_SIZE];
    double *snr15_signal = new double[SIGNAL_SIZE];
    double *snr20_signal = new double[SIGNAL_SIZE];

    AWGN awgn;

    awgn.apply(snr1_signal, r_signal, SIGNAL_SIZE,  1);
    awgn.apply(snr5_signal, r_signal, SIGNAL_SIZE,  5);
    awgn.apply(snr10_signal, r_signal, SIGNAL_SIZE, 10);
    awgn.apply(snr15_signal, r_signal, SIGNAL_SIZE, 15);
    awgn.apply(snr20_signal, r_signal, SIGNAL_SIZE, 20);

    /* Decode the signals */
    int *decode_signal = new int[SIGNAL_SIZE];

    BPSK::decode(decode_signal, snr1_signal, SIGNAL_SIZE);
    double snr1_ber = BPSK::ber(r_int_signal, decode_signal, SIGNAL_SIZE);

    BPSK::decode(decode_signal, snr5_signal, SIGNAL_SIZE);
    double snr5_ber = BPSK::ber(r_int_signal, decode_signal, SIGNAL_SIZE);

    BPSK::decode(decode_signal, snr10_signal, SIGNAL_SIZE);
    double snr10_ber = BPSK::ber(r_int_signal, decode_signal, SIGNAL_SIZE);

    BPSK::decode(decode_signal, snr15_signal, SIGNAL_SIZE);
    double snr15_ber = BPSK::ber(r_int_signal, decode_signal, SIGNAL_SIZE);

    BPSK::decode(decode_signal, snr20_signal, SIGNAL_SIZE);
    double snr20_ber = BPSK::ber(r_int_signal, decode_signal, SIGNAL_SIZE);

    //BER_th=(1/2)*erfc(sqrt(SNR));
#define TH_BER(snr_) ((0.5)*erfc(sqrt( pow(10, (snr_/10.0)) )))

    std::cout << "BER=>" << std::endl;
    std::cout << "\tSNR=1\t" << snr1_ber    << "\tTH:\t" << TH_BER(1.0) << std::endl;
    std::cout << "\tSNR=5\t" << snr5_ber    << "\tTH:\t" << TH_BER(5.0) << std::endl;
    std::cout << "\tSNR=10\t" << snr10_ber  << "\tTH:\t" << TH_BER(10.0) << std::endl;
    std::cout << "\tSNR=15\t" << snr15_ber  << "\tTH:\t" << TH_BER(15.0) << std::endl;
    std::cout << "\tSNR=20\t" << snr20_ber  << "\tTH:\t" << TH_BER(20.0) << std::endl;

    // Write the result to a csv
    std::ofstream myfile;

    myfile.open ("test_awgn.csv");
    for (int i=0; i<SIGNAL_SIZE; i++) {
        myfile << i << ", " << r_signal[i] <<
            ", " << snr1_signal[i] <<
            ", " << snr5_signal[i] <<
            ", " << snr10_signal[i] <<
            ", " << snr15_signal[i] <<
            ", " << snr20_signal[i] <<
            ",\n";
    }

    /* Cleanup */
    myfile.close();
    delete r_int_signal;
    delete r_signal;
    delete snr1_signal;
    delete snr5_signal;
    delete snr10_signal;
    delete snr15_signal;
    delete snr20_signal;
    delete decode_signal;
}
#endif

