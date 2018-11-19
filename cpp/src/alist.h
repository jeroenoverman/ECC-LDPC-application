#ifndef ALIST_H__
#define ALIST_H__

class SimpleMatrix {
    int N; // number of columns
    int M; // number of rows
    double *matrix;
    bool matrix_delete;

    public:
        SimpleMatrix(int m, int n, double *mat);
        SimpleMatrix(int m, int n);
        ~SimpleMatrix();

        int getM() {return M;}
        int getN() {return N;}
        double *getMatrix() {return matrix;}

        void print();
};

typedef double alistval_t;
typedef struct {
    int idx;
    alistval_t *value;
} alist_entry;


/*
 * Alist TODO
 *  - Get number of row entries
 */
class AlistMatrix {
    int M; // number of Rows
    int N; // number of Columns
    int GF; // Galois field q size
    int biggest_num_n; // biggest number of n entries
    int biggest_num_m; // biggest number of m entries

    alistval_t *values;

    public:
        alist_entry **nlist; // list of non zero coordinates of entries
        alist_entry **mlist; // list of non zero coordinates of entries
        int *num_nlist; // weight of each column n
        int *num_mlist; // weight of each row m

        AlistMatrix() {};
        AlistMatrix(int m, int n, int biggest_m, int biggest_n);
        AlistMatrix(AlistMatrix &clone);

        void alloc_values(void) {
            // should be the same as biggest_num_m * M
            values = new alistval_t[biggest_num_n * N];
        }
        void free_values(void){delete values;}

        // Setters
        void setGF(int q) {GF = q;}
        void setNM(int m, int n) {M = m; N = n;}
        //getters
        int getM() {return M;}
        int getN() {return N;}
        int getGF() {return GF;}
        int getBiggestNumM() {return biggest_num_m;}
        int getBiggestNumN() {return biggest_num_n;}

        void simple2alist(SimpleMatrix *sm);
        void print();
        void Mul(int *vector, int *result);

        void clear(); // Set all .value to zero. Keeps entries

        // Testing
        SimpleMatrix *alist2simple_N(void);
        SimpleMatrix *alist2simple_M(void);

    private:
        void simple_matrix_biggest_nm(SimpleMatrix *sm);
        void simple_matrix_nm_list(SimpleMatrix *sm);

};

#endif /* ALIST_H__ */
