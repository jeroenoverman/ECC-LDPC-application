#include <iostream>

#include "alist.h"

using namespace std;

#if 0
// N = 12, M = 16
int exmat[12*16] = 
{
 0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,
 0,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0,
 0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,
 0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,
 0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,
 1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,
 0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,
 0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,
 1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,
 0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,
 0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,
 1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,
};
#endif

int exmat[] = 
{
0,  0,  0,  27, 0,  0,  1,  0,  0,  36, 0,  0,  0,  0,  0,  49,
0,  0,  0,  60, 45, 0,  0,  0,  32, 0,  0,  0,  0,  0,  23, 0,
0,  6,  0,  0,  0,  21, 56, 0,  0,  0,  0,  0,  0,  47, 0,  0,
32, 0,  0,  0,  0,  0,  0,  23, 0,  0,  60, 0,  0,  0,  0,  45,
0,  0,  52, 0,  0,  0,  0,  0,  61, 0,  26, 0,  0,  11, 0,  0,
39, 0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  24, 0,  0,  11, 0,
0,  36, 0,  0,  45, 0,  0,  10, 0,  0,  0,  0,  58, 0,  0,  0,
0,  0,  62, 0,  0,  0,  0,  0,  0,  12, 0,  53, 27, 0,  0,  0,
};

int simple_mat[] = 
{
1, -1, 2,
1, -3, 1
};

int main()
{
    
    //SimpleMatrix sm(16,8,exmat);
    SimpleMatrix sm(3,2,simple_mat);
    
    sm.print();
    cout << endl;
    
    AlistMatrix al;
    al.simple2alist(&sm);
    al.print();
    
    //int vector[] = {2,1,0};
    //int vector_res[] = {0, 0};
    //al.Mul(vector, vector_res);
    //
    //SimpleMatrix res(1, 2, vector_res);
    //cout << endl;
    //res.print();
    //cout << endl;
    
    // Clone AlistMatrix
    cout << "Origional AlistMatrix" << endl;
    al.print();
    cout << "Cloned AlistMatrix" << endl;
    AlistMatrix clone(al);
    clone.print();
    cout << "Cleared cloned AlistMatrix" << endl;
    clone.clear();
    clone.print();
    
    cout << "Origional AlistMatrix" << endl;
    al.print();
}
