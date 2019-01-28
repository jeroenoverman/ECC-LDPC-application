#ifndef LDPC_APP_BASE_H__
#define LDPC_APP_BASE_H__

#include <string>
#include <vector>

#include "LDPC_info.h"

class LDPC_app_base {

    private:
        std::vector<struct h_matrix> h_matrices;

    public:
        void add_alist_files(std::vector<std::string> alist_files);
        int detect_alist_specs(std::string alist_file, struct h_matrix &hm);
        struct h_matrix *getMatrix(std::string alist_file);

        std::vector<struct h_matrix> *getMatrices() {return &h_matrices;};

        // Run the BER simulation for the specified h_matrix using a random input
        void run_bersim_app(LDPC_info &ldpc_info,
                std::vector<double> &SNRdb_list, int runs, int bp_iter, struct h_matrix *hm);

        void print_specs() {
            for (auto spec : h_matrices) {
                std::cout << "Alist File: " << spec.alist_file <<
                    " name: " << spec.name <<
                    " N: " << spec.N <<
                    " M: " << spec.M <<
                    " Z: " << spec.Z <<
                    " K: " << spec.K <<
                    " R: " << spec.R << std::endl;
            }
        };

};

#endif /* LDPC_APP_BASE_H__ */
