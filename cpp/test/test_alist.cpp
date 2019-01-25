#include "catch.hpp"

#include <iostream>
using namespace std;

#include <cstring>
#include <fstream>

#include "alist.h"

TEST_CASE("Simple Matrix")
{

    double simple_mat[] =
    {
        1, -1, 2,
        1, -3, 1
    };

    SimpleMatrix sm(2, 3, simple_mat);

    REQUIRE(sm.getM() == 2);
    REQUIRE(sm.getN() == 3);
    REQUIRE(sm.getMatrix() == simple_mat);
}

double exmat[] =
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


TEST_CASE("Simple Matrix to Alist Matrix")
{
    SimpleMatrix sm(8, 16, exmat);

    //sm.print();
    //cout << endl << endl;

    AlistMatrix al;
    al.simple2alist(&sm);
    //al.print();

    SimpleMatrix *sm2 = al.alist2simple_M();
    //sm2->print();

    REQUIRE(sm.getMatrix() == exmat);

    double *smmat = sm.getMatrix();
    double *sm2mat = sm2->getMatrix();

    for (int i=0; i<(16*8); i++) {
        REQUIRE(sm2mat[i] == smmat[i]);
    }
}

void compare_alist(AlistMatrix &al, AlistMatrix &al_cmp)
{
    REQUIRE(al.getN() == al_cmp.getN());
    REQUIRE(al.getM() == al_cmp.getM());

    REQUIRE(al.getBiggestNumN() == al_cmp.getBiggestNumN());
    REQUIRE(al.getBiggestNumM() == al_cmp.getBiggestNumM());

    for (int i=0; i<al.getN(); i++) {
        REQUIRE(al.num_nlist[i] == al_cmp.num_nlist[i]);
    }

    for (int i=0; i<al.getM(); i++) {
        REQUIRE(al.num_mlist[i] == al_cmp.num_mlist[i]);
    }

    for (int i=0; i<al.getN(); i++) {
        for (int j=0; j<al.num_nlist[i]; j++) {
            REQUIRE(al.nlist[i][j].idx == al.nlist[i][j].idx);
        }
    }

    for (int i=0; i<al.getM(); i++) {
        for (int j=0; j<al.num_mlist[i]; j++) {
            REQUIRE(al.mlist[i][j].idx == al.mlist[i][j].idx);
        }
    }

}

const string alist_txt_file = \
"16\n"
"8\n"
"2\n"
"4\n"
"2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2\n"
"4 4 4 4 4 4 4 4\n"
"4 6\n"
"3 7\n"
"5 8\n"
"1 2\n"
"2 7\n"
"3 6\n"
"1 3\n"
"4 7\n"
"2 5\n"
"1 8\n"
"4 5\n"
"6 8\n"
"7 8\n"
"3 5\n"
"2 6\n"
"1 4\n"
"4 7 10 16\n"
"4 5 9 15\n"
"2 6 7 14\n"
"1 8 11 16\n"
"3 9 11 14\n"
"1 6 12 15\n"
"2 5 8 13\n"
"3 10 12 13\n";


TEST_CASE("Read alist from file")
{
    /* Generate the test alist file */
    ofstream myfile("gen-alist-test.txt");
    REQUIRE(myfile.is_open());
    if (myfile.is_open())
    {
        myfile << alist_txt_file;
        myfile.close();
    }
    else cout << "Unable to open file";

    AlistMatrix al("gen-alist-test.txt");
    //al.print();

    // Compare matrix
    SimpleMatrix sm(8, 16, exmat);
    AlistMatrix al_cmp;
    al_cmp.simple2alist(&sm);

    /* Test all entries */
    compare_alist(al, al_cmp);

}

// H = 324x648 ==> M=324 N=648
#include "test_H.h"

TEST_CASE("Read large alist from file")
{
    /* Comparison matrix */
    SimpleMatrix sm_h(324, 648, (double *)test_H);
    AlistMatrix al_h;
    al_h.simple2alist(&sm_h);

    /* Alist from file */
    AlistMatrix al("H_n648-z27-r1_2.alist");

    compare_alist(al, al_h);
}
