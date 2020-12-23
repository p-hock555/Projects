#include <iostream>
#include <sstream>
#include "rational.h"
using namespace std;

/**
 * Your implementation of the Rational class must provide appropriate
 *  member and non-member functions such that the following program
 *	compiles and produces the correct output.
 */
int main()
{
    cout << "Constructor and insertion and extraction operators:" << endl;
    Rational r1;
    cout << r1 << endl; //r1 = 0/1
    Rational r2(4, -20);
    cout << r2 << endl; //r2 = -1/5
    Rational r3, r4, r5;
    int x = 2;
    std::stringstream ss("18 /-10 -14 / -6 2/4");
    ss >> r3 >> r4 >> r5; //overloading the >> operator allows us to do this
    // Should yield 3 Rationals: r3=-9/5, r4=7/3, and r5=1/2
    cout << r3 << " " << r4 << " " << r5 << endl; //overloading the >> operator allows us to do this 

    cout << "Addition checks: " << endl;
    cout << (r2 + r3) << endl; //-2/1
    cout << (x + r3) << endl; // 1/5
    cout << (r3 + x) << endl; // 1/5
    cout << "Multiplication checks: " << endl;
    cout << (r3 * r4) << endl; //-21/5
    cout << (6 * r4) << endl; // 14/1
    cout << (r4 * 6) << endl; // 14/1
    cout << "Exponentiation checks: " << endl;
    cout << (r5 ^ 3) << endl; //1/8
    cout << (r5 ^ -2) << endl; //4/1
    cout << (r3 ^ 0) << endl; //1/1

    Rational req1(2, 4), req2(4, 8), rne3(-4, 8);
    cout << "Equal checks: " << endl; 
    cout << (req1 == req2) << endl; //1
    cout << (req1 == rne3) << endl; //0 
    cout << "Not Equal checks: " << endl;
    cout << (req1 != req2) << endl; //0
    cout << (req1 != rne3) << endl; //1
    cout << "Less-than checks: " << endl;
    cout << (r3 < r4) << endl; //1
    cout << (req1 < req2) << endl; //0
    cout << (rne3 < req1) << endl; //1

    Rational r5c1 = r5, r5c2 = r5, r5c3 = r5, r5c4 = r5;
    cout << "Assignment checks: " << endl;
    cout << (r5c1 += rne3) << endl; //0/1
    cout << (r5c2 += 5) << endl; //11/2
    cout << (r5c3 *= r2) << endl; //-1/10
    cout << (r5c4 *= 3) << endl; //3/2

    Rational r6a(2,4), r6b(-4,8);
    cout << "Normalized 0 check: " << endl;
    cout << r6a + r6b << endl; //0/1

    return 0;
}
