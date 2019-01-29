#ifndef LDPC_INFO_H__
#define LDPC_INFO_H__

#include <vector>
#include <map>

struct h_matrix {
    std::string alist_file;
    std::string name;

    int N;
    int M;
    int Z;
    int K;
    double R;
};

typedef struct BER_entry{
    double BER;
    double BER_bf;
    double BER_no_ecc;
    double BER_no_ecc_theoretical;
} BER_entry_t;

class LDPC_info {

    private:
        std::map<double, BER_entry_t> SNRdb_list;

    public:
        std::string alist_file;
        std::string name;

        int N;
        int M;
        int K;
        double R;

        void add_entry(double snr, double ber, double ber_bf, double ber_no_ecc, double ber_no_ecc_th) {
            BER_entry_t be;
            be.BER = ber;
            be.BER_bf = ber_bf;
            be.BER_no_ecc = ber_no_ecc;
            be.BER_no_ecc_theoretical = ber_no_ecc_th;

            SNRdb_list[snr] = be;
        }

        void add_entry(double snr, BER_entry_t be) {
            SNRdb_list[snr] = be;
        }

        BER_entry_t get_entry(double snr) {
            return SNRdb_list[snr];
        }

        std::vector<double> get_snr_vec() {
            std::vector<double> snr_vec;
            for(std::map<double,BER_entry_t>::iterator it = SNRdb_list.begin(); it != SNRdb_list.end(); ++it) {
                snr_vec.push_back(it->first);
            }
            return snr_vec;
        }

        void print() {
            std::cout << "LDPC Info for: \"" << name << "\" N=" << N << ", M=" << M << ", R=" << R << std::endl;
            for (auto snr : get_snr_vec()) {
                BER_entry_t be = get_entry(snr);
                printf("SNR: %1.1f\t| BER (w/ bp): %1.8f\t| BER (w/ bf): %1.8f\t| BER (w/o bp): %1.8f\t| BER (th awgn): %1.8f\n",
                        snr, be.BER, be.BER_bf, be.BER_no_ecc, be.BER_no_ecc_theoretical);
            }
        }
};

#endif /* LDPC_INFO_H__ */
