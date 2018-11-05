#include "catch.hpp"

#include "alist.h"

//TEST_CASE( "1: All test cases reside in other .cpp files (empty)", "[multi-file:1]" ) {
//}
//
//int Factorial( int number ) {
////   return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
// return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
//}
//
//TEST_CASE( "2: Factorial of 0 is 1 (fail)", "[multi-file:2]" ) {
//    REQUIRE( Factorial(0) == 1 );
//}
//
//TEST_CASE( "2: Factorials of 1 and higher are computed (pass)", "[multi-file:2]" ) {
//    REQUIRE( Factorial(1) == 1 );
//    REQUIRE( Factorial(2) == 2 );
//    REQUIRE( Factorial(3) == 6 );
//    REQUIRE( Factorial(10) == 3628800 );
//}


TEST_CASE("Simple Matrix") {

    int simple_mat[] =
    {
        1, -1, 2,
        1, -3, 1
    };

    SimpleMatrix sm(3, 2, simple_mat);

    REQUIRE(sm.getM() == 2);
    REQUIRE(sm.getN() == 3);
    REQUIRE(sm.getMatrix() == simple_mat);
}
