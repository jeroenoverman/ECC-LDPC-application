#include <iostream>
#include <regex>
#include <cstring>
#include <time.h>

#include "alist.h"
#include "bpsk.h"
#include "awgn.h"
#include "LDPC_encode.h"
#include "LDPC_beliefprop.h"
#include "LDPC_bitflip.h"
#include "LDPC_app_base.h"
#include "LDPC_info.h"

using namespace std;

void LDPC_app_base::add_alist_files(vector<string> alist_files) {
    for (auto file : alist_files) {
        struct h_matrix hm;

        hm.alist_file = file;
        hm.name = regex_replace(file, regex(".alist"), "");
        if (detect_alist_specs(hm.name, hm)) {
            h_matrices.push_back(hm);
        } else {
            cout << "An error occured parsing alist file: " << file << endl;
        }
    }
}

int LDPC_app_base::detect_alist_specs(string alist_file, struct h_matrix &hm) {
    string N_str, Z_str, R1_str, R2_str;

    regex r("n([0-9]+)-z([0-9]+)-r([0-9]+)_([0-9]+)");
    smatch match;

    if(!std::regex_search(alist_file, match, r)) {
        return 0;
    }

    // Full match + N + Z + R1 + R2
    if (match.size() != 4+1) {
        return 0;
    }

    N_str   = match[1];
    Z_str   = match[2];
    R1_str  = match[3];
    R2_str  = match[4];

    hm.N = stoi(N_str);
    hm.Z = stoi(Z_str);
    hm.R = (double)(stoi(R1_str)) / (double)(stoi(R2_str));

    hm.K = (int)(hm.R * hm.N);
    hm.M = hm.N - hm.K;

    return 1;
}

struct h_matrix *LDPC_app_base::getMatrix(string alist_file) {
    for (size_t i=0; i<h_matrices.size(); i++) {
        if (h_matrices[i].alist_file == alist_file) {
            return &h_matrices[i];
        }
    }
    return NULL;
}

// Generate random binary input signal
// Generate BPSK signal
// Encode using the specified LDPC matrix
// Apply AWGN with different SNR 'runs' times and take the avg over the runs
//      Decode using the specified LDPC matrix
//      Decode BPSK signal
//      Compute BER
// Return avg BER per SNR over 'runs'
void LDPC_app_base::run_bersim_app(LDPC_info &ldpc_info, vector<double> &SNRdb_list, int runs, int bp_iter, struct h_matrix *hm) {

    if (hm == NULL) {
        cout << "No H Matrix" << endl;
        return;
    }

    /* Create LDPC object using the specified alist file */
    AlistMatrix al(hm->alist_file);
    int info_size = al.getK();
    int code_size = al.getN();

    //cout << "Info size: " << info_size << endl;
    //cout << "Code size: " << code_size << endl;

    /* Fill the LDPC info object */
    ldpc_info.N = al.getN();
    ldpc_info.M = al.getM();
    ldpc_info.R = al.getR();
    ldpc_info.name = hm->name;
    ldpc_info.alist_file = hm->alist_file;

    /* Allocate required memory for the different steps */
    int *r_bin_signal = new int[info_size];
    int *encoded_msg = new int[code_size];

    /* Generate random binary signal of 1 block (K size) */
    auto myrand = std::bind(std::uniform_int_distribution<int>{0, 1},
            std::mt19937(static_cast<std::mt19937::result_type>(time(nullptr))));

    for (int i=0; i<info_size; i++) {
        r_bin_signal[i] = myrand();
    }

    /* Apply LDPC code */
    LDPC_encode::encode(encoded_msg, r_bin_signal, &al);

    for (auto snr_db : SNRdb_list) {
        //cout << "SNR: " << snr_db << endl;
        double ber_avg = 0;
        double ber_avg_bf = 0;
        double ber_avg_no_ecc = 0;

        /* Send over AWGN with BPSK modulation for different SNR */
        for (int run = 0; run < runs; run++) {
            //cout << "\tRUN: " << run << endl;

            /* BPSK encoding */
            double *encoded_msg_bpsk = new double[code_size];
            BPSK::encode(encoded_msg_bpsk, encoded_msg, code_size);

            /* Send over AWGN channel */
            double *encoded_msg_bpsk_received_no_bp = new double[code_size];
            AWGN::apply(encoded_msg_bpsk_received_no_bp, encoded_msg_bpsk, code_size, snr_db);

            /* BPSK decoding WITHOUT Belief Prop (for demo comparison) */
            /* The message is the first 'info_size' bits of the codeword */
            int *decoded_msg_no_bp =  new int[code_size];
            BPSK::decode(decoded_msg_no_bp, encoded_msg_bpsk_received_no_bp, code_size);
            double ber_no_ecc = BPSK::ber(r_bin_signal, decoded_msg_no_bp, info_size);

            /* Run LDPC Bit Flipping */
            LDPC_BitFlip bf(&al, decoded_msg_no_bp);
            //int bfiter = bf.run();
            bf.run();
            int *decoded_msg_bf = bf.result();
            double ber_bf = BPSK::ber(r_bin_signal, decoded_msg_bf, info_size);
            //cout << "BF iter: " << bfiter << " BER: " << ber_bf << endl;

            /* Run LDPC belief propagation */
            double *encoded_msg_bpsk_received;
            int msg_size;
            LDPC_BeliefProp bp(&al, encoded_msg_bpsk_received_no_bp);
            bp.run(bp_iter);
            encoded_msg_bpsk_received = bp.getResult(&msg_size);

            /* BPSK decoding with Belief Prop */
            int *decoded_msg = new int[info_size];
            BPSK::decode(decoded_msg, encoded_msg_bpsk_received, info_size);
            double ber = BPSK::ber(r_bin_signal, decoded_msg, info_size);

            ber_avg += ber;
            ber_avg_bf += ber_bf;
            ber_avg_no_ecc += ber_no_ecc;

            //cout << "\t\tBER: " << ber << " total: " << ber_avg << endl;

            /* Cleanup */
            delete [] encoded_msg_bpsk;
            delete [] encoded_msg_bpsk_received_no_bp;
            delete [] decoded_msg_no_bp;
            delete [] decoded_msg;
        }
        ber_avg = ber_avg/runs;
        ber_avg_bf = ber_avg_bf/runs;
        ber_avg_no_ecc = ber_avg_no_ecc/runs;
        //cout << "\tAVG BER: " << ber_avg << endl;

        /* Add an entry for the SNR */
        BER_entry_t be;
        be.BER = ber_avg;
        be.BER_bf = ber_avg_bf;
        be.BER_no_ecc = ber_avg_no_ecc;
        be.BER_no_ecc_theoretical = BPSK::ber_theoretical(snr_db);
        ldpc_info.add_entry(snr_db, be);
    }

    delete [] r_bin_signal;
    delete [] encoded_msg;
}

void LDPC_app_base::run_data_app(LDPC_info &ldpc_info,
        int *data_out_bp, int *data_out_bf, int *data_out_raw, vector<iter_entry_t> &iter_data_out, int *data_in,
        int size, double snr_db, int bp_iter, struct h_matrix *hm) {

    if (hm == NULL) {
        cout << "No H Matrix" << endl;
        return;
    }

    /* Create LDPC object using the specified alist file */
    AlistMatrix al(hm->alist_file);
    int info_size = al.getK();
    int code_size = al.getN();

    int blocks = size/info_size;
    int rest = size%info_size;

    if (rest) {
        ++blocks;
    }

    int *data_ptr = data_in;

    double ber_total = 0;
    double ber_bf_total = 0;
    double ber_no_ecc_total = 0;

    double bf_iter_total = 0;
    double bp_iter_total = 0;

    cout << "Blocks: " << blocks << " Rest: " << rest << endl;

    for (int i=0; i<blocks; i++) {

        /* Copy data int bufer */
        int *data_buffer = new int[info_size];

        int idx = i*info_size;
        int size_bytes;
        if (rest && (i == blocks-1)) {
            // The last block if partial
            size_bytes = sizeof(data_in[0])*rest;
            //memset(data_buffer, 0, ((info_size-rest) * sizeof(data_in[0])));
            memset(data_buffer, 0, sizeof(data_in[0])*info_size);
            memcpy(data_buffer, data_ptr, size_bytes);
            //cout << "Last block i: " << i << endl;
        } else {
            // The whole blocks
            size_bytes = sizeof(data_in[0])*info_size;
            memcpy(data_buffer, data_ptr, size_bytes);
            //cout << "Block i: " << i << endl;
        }
        //cout << "Size bytes: " << size_bytes << endl;

        /* Apply LDPC code */
        int *encoded_msg = new int[code_size];
        LDPC_encode::encode(encoded_msg, data_buffer, &al);

        /* BPSK encoding */
        double *encoded_msg_bpsk = new double[code_size];
        BPSK::encode(encoded_msg_bpsk, encoded_msg, code_size);

        /* Send over AWGN channel */
        double *encoded_msg_bpsk_received_no_bp = new double[code_size];
        AWGN::apply(encoded_msg_bpsk_received_no_bp, encoded_msg_bpsk, code_size, snr_db);

        /* BPSK decoding WITHOUT Belief Prop (for demo comparison) */
        /* The message is the first 'info_size' bits of the codeword */
        int *decoded_msg_no_bp =  new int[code_size];
        BPSK::decode(decoded_msg_no_bp, encoded_msg_bpsk_received_no_bp, code_size);
        double ber_no_ecc = BPSK::ber(data_buffer, decoded_msg_no_bp, info_size);

        /* Run LDPC Bit Flipping */
        LDPC_BitFlip bf(&al, decoded_msg_no_bp);

        /* Run the Bit Flip iterations */
        //int bf_niter = bf.run(bp_iter);
        int bf_niter = 0;
        bool bf_iter_done = false;
        for (int i=0; i<bp_iter; i++) {
            if (!bf_iter_done) {
                if (bf.iterate() == 0) {
                    bf_iter_done = true;
                    bf_niter = i+1;
                }

            }
            // Fill iter_data_out
            for (iter_entry_t &ie : iter_data_out) {
                if (ie.iteration == i+1) {
                    memcpy(&ie.data_out_bf[idx], bf.result(), size_bytes);
                }
            }
        }
        if (bf_niter == 0) {
            bf_niter = bp_iter;
        }


        int *decoded_msg_bf = bf.result();
        double ber_bf = BPSK::ber(data_buffer, decoded_msg_bf, info_size);
        //cout << "BF iter: " << bfiter << " BER: " << ber_bf << endl;

        /* Run LDPC belief propagation */
        double *encoded_msg_bpsk_received;
        int msg_size;
        LDPC_BeliefProp bp(&al, encoded_msg_bpsk_received_no_bp);

        /* Run the Belief Prop iterations */
        //int bp_niter = bp.run(bp_iter);
        int bp_niter = 0;
        bool bp_iter_done = false;
        for (int i=0; i<bp_iter; i++) {
            if (!bp_iter_done) {
                if (bp.iterate() == 0) {
                    bp_iter_done = true;
                    bp_niter = i+1;
                }
            }
            // Fill iter_data_out
            for (iter_entry_t &ie : iter_data_out) {
                if (ie.iteration == i+1) {
                    int *decoded_msg_iter = new int[info_size];
                    BPSK::decode(decoded_msg_iter, bp.getResult(), info_size);
                    memcpy(&ie.data_out_bp[idx], decoded_msg_iter, size_bytes);
                    delete [] decoded_msg_iter;
                }
            }
        }
        if (bp_niter == 0) {
            bp_niter = bp_iter;
        }

        encoded_msg_bpsk_received = bp.getResult(&msg_size);

        /* BPSK decoding with Belief Prop */
        int *decoded_msg = new int[info_size];
        BPSK::decode(decoded_msg, encoded_msg_bpsk_received, info_size);
        double ber = BPSK::ber(data_buffer, decoded_msg, info_size);

        ber_total += ber;
        ber_bf_total += ber_bf;
        ber_no_ecc_total += ber_no_ecc;

        bf_iter_total += bf_niter;
        bp_iter_total += bp_niter;

        /* Copy decoded bits to the output */
        memcpy(&data_out_bp[idx], decoded_msg, size_bytes); // Belief Prop
        memcpy(&data_out_bf[idx], decoded_msg_bf, size_bytes); // Bit Flip
        memcpy(&data_out_raw[idx], decoded_msg_no_bp, size_bytes); // Raw

        /* Next block */
        data_ptr = &data_ptr[info_size];

        /* Free data */
        delete [] data_buffer;
        delete [] encoded_msg;
        delete [] encoded_msg_bpsk;
        delete [] encoded_msg_bpsk_received_no_bp;
        delete [] decoded_msg_no_bp;
        delete [] decoded_msg;

        //cout << "Ber: " << ber << " Ber bf: " << ber_bf << " Ber no ecc: " << ber_no_ecc << endl;
    }

    ber_total = ber_total/blocks;
    ber_bf_total = ber_bf_total/blocks;
    ber_no_ecc_total = ber_no_ecc_total/blocks;

    bf_iter_total = bf_iter_total/blocks;
    bp_iter_total = bp_iter_total/blocks;

    /* Add an entry for the SNR */
    BER_entry_t be;
    be.BER = ber_total;
    be.BER_bf = ber_bf_total;
    be.BER_no_ecc = ber_no_ecc_total;
    be.BER_no_ecc_theoretical = BPSK::ber_theoretical(snr_db);
    be.bf_iter_avg = bf_iter_total;
    be.bp_iter_avg = bp_iter_total;
    ldpc_info.add_entry(snr_db, be);

    cout << "BF iter avg: " << bf_iter_total << " BP iter avg: " << bp_iter_total << endl;
}
