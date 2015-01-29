//
//  main.cpp
//  practice_2
//
//  Created by Luke Lloyd-Jones on 29/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#include <iostream>
#include "Vector.hpp"
// #include "Vector.cpp"







/************************************************************************
 ************************************************************************
 **                                                                    **
 **            Chapter 10 - Classes for Linear Algebra                 **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

// Develop classes that allow us to perform linear algebra calculations
// Develop a class of vectors called Vector, Matrix, LinearSystem. The
// vector and matrix classes will include constructors and destructors
// that handle memory management. We will overload the assignment,
// addition, subtraction and multiplication operators.

// Let's try and use some of the elements of the vector class

int main(int argc, char* argv[])
{
    // Declare some instance of the vector class

    Vector x(5);
    Vector y(5);
    Vector z(5);
    Vector c(5);

    x[0] = 0.01; x[1] = 0.02; x[2] = 0.03; x[3] = 0.04; x[4] = 0.05;
    y[0] = 0.01; y[1] = 0.02; y[2] = 0.03; y[3] = 0.04; y[4] = 0.05;
    z[0] = 0.01; z[1] = 0.02; z[2] = 0.03; z[3] = 0.04; z[4] = 0.05;

    c = x + y;
    y = c - z;
   
    std::cout << c[0] << "\t" << c[1] << "\t"  << c[2] << "\t"  << c[3] << "\t" << c[4] << "\n";
    std::cout << y[0] << "\t" << y[1] << "\t"  << y[2] << "\t"  << y[3] << "\t" << y[4] << "\n";
    
    double k = 5.0;
    
    y = y*k;
    
    std::cout << y[0] << "\t" << y[1] << "\t"  << y[2] << "\t"  << y[3] << "\t" << y[4] << "\n";
    z.CalculateNorm(2);
    return 0;
}



