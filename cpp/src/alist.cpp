#include <iostream>
#include <map>

#include "alist.h"

using namespace std;

SimpleMatrix::SimpleMatrix(int n, int m, int *mat)
{
    N = n;
    M = m;
    matrix = mat;
    matrix_delete = false;
}

SimpleMatrix::SimpleMatrix(int n, int m)
{
    N = n;
    M = m;
    matrix = new int[n*m];
    matrix_delete = true;
}

SimpleMatrix::~SimpleMatrix()
{
    if (matrix_delete) {
        delete matrix;
    }
}

//void matrix_simple_print(simple_matrix *sm)
void SimpleMatrix::print()
{
    int r, c;
    cout << "N: " << N << endl;
    cout << "M: " << M << endl;

    for (r=0; r<M; r++) {
        for (c=0; c<N; c++) {
            //cout << "(" << r*(sm->N)+c << ")" << sm->matrix[r*(sm->N)+c] << " ";
            cout << matrix[r*N+c] << " ";
        }
        cout << endl;
    }
}

/////////
/////////
/////////

AlistMatrix::AlistMatrix(AlistMatrix &clone)
{
    M = clone.M;
    N = clone.N;
    GF = clone.GF;

    biggest_num_n = clone.biggest_num_n;
    biggest_num_m = clone.biggest_num_m;

    num_nlist = new int[N];
    num_mlist = new int[M];

    values = new alistval_t[biggest_num_n * biggest_num_m];

    // Map the value pointers between the N and M list
    // so that changing a value in the Nlist is reflected in the M list
    map <alistval_t *, alistval_t *> tmp_ptr_map;

    copy(clone.values,
            clone.values + (biggest_num_n * biggest_num_m),
            values);

    // Num N list
    for (int i=0; i<clone.N; i++) {
        num_nlist[i] = clone.num_nlist[i];
    }

    // Num M list
    for (int i=0; i<M; i++) {
        num_mlist[i] = clone.num_mlist[i];
    }

    // Build N and M lists
    nlist = new alist_entry*[N];
    for (int i=0; i<N; i++) {
        nlist[i] = new alist_entry[num_nlist[i]];
    }
    mlist = new alist_entry*[M];
    for (int i=0; i<M; i++) {
        mlist[i] = new alist_entry[num_mlist[i]];
    }

    int cntn = 0;
    // N list
    for (int i=0; i<N; i++) {
        for (int j=0; j<num_nlist[i]; j++) {
            nlist[i][j].idx = clone.nlist[i][j].idx;

            tmp_ptr_map[clone.nlist[i][j].value] = &values[cntn];

            nlist[i][j].value = &values[cntn];
            *nlist[i][j].value = *clone.nlist[i][j].value;

            cntn++;
        }
    }

    // M list
    for (int i=0; i<M; i++) {
        for (int j=0; j<num_mlist[i]; j++) {
            mlist[i][j].idx = clone.mlist[i][j].idx;

            mlist[i][j].value = tmp_ptr_map[clone.mlist[i][j].value];
        }
    }
}

void AlistMatrix::clear()
{
    biggest_num_n = 0;
    biggest_num_m = 0;

    // N list
    for (int i=0; i<N; i++) {
        for (int j=0; j<num_nlist[i]; j++) {
            *nlist[i][j].value = 0;
        }
    }

    // M list
    //for (int i=0; i<M; i++) {
    //    for (int j=0; j<num_mlist[i]; j++) {
    //        *mlist[i][j].value = 0;;
    //    }
    //}
}

//static void
//matrix_simple_biggest_nm(simple_matrix *sm, int *bn, int *bn_list, int *bm, int *bm_list)
#define IDX_MAT_ARRAY(c_, r_, N_)  (r_*N_+c_)
void AlistMatrix::simple_matrix_biggest_nm(SimpleMatrix *sm)
{
    int ncnt = 0, mcnt = 0;
    int r, c;

    int n = sm->getN();
    int m = sm->getM();
    int *matrix = sm->getMatrix();

    biggest_num_n = 0;
    biggest_num_m = 0;

    // Biggest N
    for (c=0; c<n; c++) {
        for (r=0; r<m; r++) {
            int val = matrix[IDX_MAT_ARRAY(c,r,n)];
            //cout << IDX_MAT_ARRAY(c,r,n) << "|";
            if (val != 0) {
                ncnt++;
                //cout << "VAL:[" << val <<"]";
            }
        }
        //cout << "N cnt: " << ncnt << endl;
        if (ncnt > biggest_num_n) {
            biggest_num_n = ncnt;
        }

        num_nlist[c] = ncnt;
        ncnt = 0;
    }

    // Biggest M
    for (r=0; r<m; r++) {
        for (c=0; c<n; c++) {
            int val = matrix[IDX_MAT_ARRAY(c,r,n)];
            //cout << IDX_MAT_ARRAY(c,r,n) << "|";
            if (val != 0) {
                mcnt++;
                //cout << "VAL:[" << val <<"]";
            }
        }
        //cout << "M cnt: " << mcnt << endl;
        if (mcnt > biggest_num_m) {
            biggest_num_m = mcnt;
        }
        num_mlist[r] = mcnt;
        mcnt = 0;
    }
}

//static void
//matrix_simple_nm_list(simple_matrix *sm, alist_entry **nlist, alist_entry **mlist)
void AlistMatrix::simple_matrix_nm_list(SimpleMatrix *sm)
{
    int r, c;

    int n = sm->getN();
    int m = sm->getM();

    int ncnt = 0, mcnt = 0;
    int *matrix = sm->getMatrix();

    // Map the value pointers between the N and M list
    // so that changing a value in the Nlist is reflected in the M list
    map <int, alistval_t *> tmp_ptr_map;
    int values_cnt;

    values_cnt = 0;
    // Loop N
    for (c=0; c<n; c++) {
        for (r=0; r<m; r++) {
            int idx = IDX_MAT_ARRAY(c,r,n);
            int val = matrix[idx];
            //cout << r+ m*c << "|";
            if (val != 0) {
                nlist[c][ncnt].idx = r+1;

                nlist[c][ncnt].value = &values[values_cnt];
                tmp_ptr_map[idx] = &values[values_cnt];
                // Only set the actual value once here, not in M
                *nlist[c][ncnt].value = val;

                ncnt++;
                values_cnt++;
                //cout << "VAL:[" << val <<"]";
            }
        }
        //cout << "N cnt: " << ncnt << endl;
        ncnt = 0;
    }

    // Loop M
    for (r=0; r<m; r++) {
        for (c=0; c<n; c++) {
            int idx = IDX_MAT_ARRAY(c,r,n);
            int val = matrix[idx];
            //cout << c*m+ r << "|";
            if (val != 0) {
                mlist[r][mcnt].idx = c+1;
                mlist[r][mcnt].value = tmp_ptr_map[idx];
                mcnt++;
                //cout << "VAL:[" << val <<"]";
            }
        }
        //cout << "M cnt: " << mcnt << endl;
        mcnt = 0;
    }
}


//void matrix_simple2alist(simple_matrix *sm, alist_matrix *al, int q)
void AlistMatrix::simple2alist(SimpleMatrix *sm)
{
    N = sm->getN();
    M = sm->getM();

    // Biggest number of entries n and m
    num_nlist = new int[N];
    num_mlist = new int[M];

    simple_matrix_biggest_nm(sm);

    // Actual storage of the values, nodes hold pointers
    values = new alistval_t[biggest_num_n * biggest_num_m];


    // Build N and M lists
    nlist = new alist_entry*[N];
    for (int i=0; i<N; i++) {
        nlist[i] = new alist_entry[num_nlist[i]];
    }
    mlist = new alist_entry*[M];
    for (int i=0; i<M; i++) {
        mlist[i] = new alist_entry[num_mlist[i]];
    }

    simple_matrix_nm_list(sm);

    return;
}

// Alist to Simple Matrix using the M list (meant for testing)
SimpleMatrix * AlistMatrix::alist2simple_M(void)
{
    SimpleMatrix *sm = new SimpleMatrix(N, M);
    int *mat = sm->getMatrix();

    int r, c;

    for (r=0; r<M; r++) {
        //cout << "Entries: " << entries << endl;
        int entry = 0;
        for (c=0; c<N; c++) {
            int idx = r*N+c;

            if (mlist[r][entry].idx-1 == c) {
                //cout << "Entry: " << entry << " ";
                mat[idx] = *mlist[r][entry].value;
                ++entry;
            } else {
                mat[idx] = 0;
            }
        }
        cout << endl;
    }

#if 0
    cout << "M list: " << endl;
    for (int i=0; i<M; i++) {
        for (int j=0; j<num_mlist[i]; j++) {
            //cout << al->mlist[i][j].idx << ",";
            cout << mlist[i][j].idx << "(" << *mlist[i][j].value << "),";
        }
        cout << endl;
    }
    cout << endl;
#endif

    return sm;

}

// Alist to Simple Matrix using the N list (meant for testing)
SimpleMatrix * AlistMatrix::alist2simple_N(void)
{
    return NULL;
}


void AlistMatrix::print()
{
    cout << "N: " << N << endl;
    cout << "M: " << M << endl;
    cout << "GF: " << GF << endl;

    cout << "Biggest N: " << biggest_num_n << endl;
    cout << "Biggest M: " << biggest_num_m << endl;

    cout << "Num N list: ";
    for (int i=0; i<N; i++) {
        cout << num_nlist[i] << "|";
    }
    cout << endl;

    cout << "Num M list: ";
    for (int i=0; i<M; i++) {
        cout << num_mlist[i] << "|";
    }
    cout << endl;


    cout << "N list: " << endl;
    for (int i=0; i<N; i++) {
        for (int j=0; j<num_nlist[i]; j++) {
            //cout << al->nlist[i][j].idx << ",";
            cout << nlist[i][j].idx << "(" << *nlist[i][j].value << "),";
        }
        cout << endl;
    }
    cout << endl;

    cout << "M list: " << endl;
    for (int i=0; i<M; i++) {
        for (int j=0; j<num_mlist[i]; j++) {
            //cout << al->mlist[i][j].idx << ",";
            cout << mlist[i][j].idx << "(" << *mlist[i][j].value << "),";
        }
        cout << endl;
    }
    cout << endl;
}

//void AlistMatrix::prettyPrint()
//{
//}

//// Multiplication
//void alist_times_cvector_sparse_mod2
//( alist_matrix *a , unsigned char *x , unsigned char *y ) {
//  int n , m , i ;
//  int *nlist ;
//
//  for ( m = 1 ; m <= a->M ; m++ ) {
//    y[m] = 0 ;
//  }
//  for ( n = 1 ; n <= a->N ; n++ ) {
//    if ( x[n] ) {
//      nlist = a->nlist[n] ;
//      for ( i = a->num_nlist[n] ; i >= 1 ; i -- ) {
//          y[ nlist[i] ] ^= 1 ;
//      }
//    }
//  }
//}

void AlistMatrix::Mul(int *vector, int *result)
{
    alist_entry *nlist_p;

    // Clear the result
    for (int m=0; m < M; m++) {
        result[m] = 0;
    }

    for (int n=0; n < N; n++) {
        if (vector[n]) {
            nlist_p = nlist[n];
            for (int i = num_nlist[n]-1; i >= 0; i--) {
                cout << "----------" << endl;
                cout << "i: " << i << endl;
                cout << "nlist_p[i].idx " << nlist_p[i].idx << endl;
                cout << ".value " << *nlist_p[i].value << endl;
                cout << "n: " << n << endl;
                cout << "vector[n] " << vector[n] << endl;
                cout << "Result[" << nlist_p[i].idx-1 << "]= " << vector[n] * (*nlist_p[i].value) << endl;
                cout << endl;

                result[nlist_p[i].idx-1] += vector[n] * (*nlist_p[i].value);
            }
        }
    }
}
