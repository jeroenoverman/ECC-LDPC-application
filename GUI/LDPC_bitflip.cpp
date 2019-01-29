#include <vector>
#include <iostream>
#include "LDPC_bitflip.h"

using namespace std;

/* MATLAB code
    s_n = [];
    for j = 1:size(H,1)
        tmp = mod(sum(y .* H(j,:)), 2);
        s_n = [s_n tmp];
    end

    % If s_n == all zero, we are done
    if sum(s_n) == 0
        break;
    end

    f_n = [];
    for i = 1:size(H,2)
        tmp = sum(transpose(s_n) .* H(:,i));
        f_n = [f_n tmp];
    end

    % Find index of largest sums
    m = max(f_n);
    idx = find(f_n == m);
    for mm = idx
        y(mm) = mod(y(mm)+1,2);
    end

*/

int LDPC_BitFlip::iterate() {

    /* Step 1 */
    int *s_vec = new int[H->getM()];
    int s_vec_sum;

    s_vec_sum = 0;
    for (int row=0; row<H->getM(); row++) {
        int sum = 0;
        for (int col=0; col<H->num_mlist[row]; col++) {
            int idx = H->mlist[row][col].idx-1;
            //cout << "Idx: " << idx << endl;
            sum += correct_codeword[idx];
        }
        //cout << "Sum: " << sum << endl;
        int tmp = sum % 2;
        s_vec[row] = tmp;
        s_vec_sum += tmp;
    }

#if 0
    // print s_n
    cout << "S_N: [";
    for (int i=0; i<H->getM(); i++) {
        cout << s_vec[i] << ", ";
    }
    cout << "]" << endl;
    cout << "Sum s_n: " << s_vec_sum << endl;
#endif

    /* If the sum of sumvec == 0, we are done */
    if (s_vec_sum == 0) {
        return 0;
    }

    /* Step 2 */
    int *f_vec = new int[H->getN()];
    // The index of the latgest sum entries in the vector */
    vector<int> f_vec_max_idx;
    int f_vec_current_max = 0;

    for (int col=0; col<H->getN(); col++) {
        int sum = 0;
        for (int row=0; row<H->num_nlist[col]; row++) {
            int idx = H->nlist[col][row].idx-1;
            sum += s_vec[idx];
        }
        f_vec[col] = sum;

        /* Save the indexes of the maximums */
        if (sum > f_vec_current_max) {
            // The new max
            f_vec_current_max = sum;
            f_vec_max_idx.clear();
            f_vec_max_idx.push_back(col);
        } else if (sum == f_vec_current_max) {
            f_vec_max_idx.push_back(col);
        }
    }

#if 0
    // print f_n
    cout << "F_N: [";
    for (int i=0; i<H->getN(); i++) {
        cout << f_vec[i] << ", ";
    }
    cout << "]" << endl;
    cout << "Max f_n: " << f_vec_current_max << endl;
    cout << "F_N max idx vector: [";
    for (int i=0; i<f_vec_max_idx.size(); i++) {
        cout << f_vec_max_idx.at(i) << ", ";
    }
    cout << "]" << endl;
#endif

    /* Step 3 */
    /* Flip the bits with the largest sum */
    for (auto idx : f_vec_max_idx) {
        //cout << "Mod idx: " << idx << endl;
        correct_codeword[idx] = (correct_codeword[idx]+1)%2;
    }

    delete [] s_vec;
    delete [] f_vec;

    return 1;
}

int LDPC_BitFlip::run(int iterations) {
    int iter=0;
    for (iter=0; iter<iterations; iter++) {
        if (iterate() == 0) {
            iter++;
            break;
        }
    }

    return iter;
}
