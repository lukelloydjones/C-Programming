//
//  main.cpp
//  practice_2
//
//  Created by Luke Lloyd-Jones on 29/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Exception.hpp"
#include "LinearSystem.hpp"







/************************************************************************
 ************************************************************************
 **                                                                    **
 **            Chapter 10 - Classes for Linear Algebra                 **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

// Section 10.7 - Excercises
// -------------------------

// Build a matrix class. Then build the linear system class


int main(int argc, char** argv)
{
    // Declare some instance of the vector class

    //Matrix X(2, 2);
    Vector b(2);
    Vector y(3);
    Matrix X(2,2);
    //Matrix Z(4,4);
    
    // Define the X matrix
    
    X(1, 1) = 1; X(1, 2) = 2; X(2, 1) = 3; X(2, 2) = 4;
    
    // Print an element of the X matrix
    
    //std::cout << X(1, 1) << "\n";
    
    // Define the b vector
    
    b(1) = 0.5; b(2) = 3.5;
    
    // Define a linear system
    
    LinearSystem Xb(X, b);
    
    Xb.Solve();
    std::cout << Xb.Solve() << "\n";
    
//    std::cout << b[1] << "\n";
//    std::cout << b.Read(0, b) << "\n";
//    b(2) = 2.5;
//    std::cout << b.Read(1, b) << "\n";
    
//    std::cout << b << "\n";
//    std::cout.flush();
//    std::cout << y << "\n";
//    try {
//        y=b;
//    } catch (Exception& error) {
//        error.PrintDebug();
//        std::cout << "LHS vector size " << y.GetSize()<< "\n";
//        std::cout << "RHS vector size " << b.GetSize()<< "\n";
//
//    }

    // Let the y vector be the product of b and X
    
    //y = b*X;
//    
//    // Define Y to be equal to k*X
//    
//    double k = 5.8;
//    
//    Y = X*k;
//    
//    std::cout << "y(1)" << "\t" << y.Read(0) << "\n";
//    
//    // Print some elements
//    
//    std::cout << y(1) << "\t" << y(2) << "\n";
//    std::cout << Y(1, 1) << "\t" << Y(2, 2) << "\n";
//    
//    // Do matrix multiplication element wise
//    
//    Z = Y * X;
//    
//    std::cout << Z(1, 1) << "\t" << Z(1, 2) << "\n";
//    std::cout << Z(2, 1) << "\t" << Z(2, 2) << "\n";
    
    // Do proper matrix multiplication
    
    // std::cout << X.CalculateDeterminant() << "\n";
}




// Develop classes that allow us to perform linear algebra calculations
// Develop a class of vectors called Vector, Matrix, LinearSystem. The
// vector and matrix classes will include constructors and destructors
// that handle memory management. We will overload the assignment,
// addition, subtraction and multiplication operators.

// Section 10.6 - Memory debugging tools
// -------------------------------------

// Memory leak is a problem

// Other memory related problems are. Watch out for allocating to many
// elements to a vector or not initialising elements

// Let's try and use some of the elements of the vector class

//int main(int argc, char* argv[])
//{
//    // Declare some instance of the vector class
//
//    Vector x(5);
//    Vector y(5);
//    Vector z(5);
//    Vector c(5);
//    
//    // Fill these vectors
//    
//    x[0] = 0.01; x[1] = 0.02; x[2] = 0.03; x[3] = 0.04; x[4] = 0.05;
//    y[0] = 0.01; y[1] = 0.02; y[2] = 0.03; y[3] = 0.04; y[4] = 0.05;
//    z[0] = 0.01; z[1] = 0.02; z[2] = 0.03; z[3] = 0.04; z[4] = 0.05;
//    
//    // Use the uniary - operator
//    
//    c = -x;
//    z = -z;
//    
//    std::cout << c[0] << "\t" << c[1] << "\t"  << c[2] << "\t"  << c[3] << "\t" << c[4] << "\n";
//    std::cout << y[0] << "\t" << y[1] << "\t"  << y[2] << "\t"  << y[3] << "\t" << y[4] << "\n";
//    
//    // Use the binary addition and subtraction operators
//    
//    c = x + y;
//    y = c - z;
//   
//    // Print some of the newly calculated elements
//    
//    std::cout << c[0] << "\t" << c[1] << "\t"  << c[2] << "\t"  << c[3] << "\t" << c[4] << "\n";
//    std::cout << y[0] << "\t" << y[1] << "\t"  << y[2] << "\t"  << y[3] << "\t" << y[4] << "\n";
//    
//    // Attempt to use the scalar multiplication 
//    double k = 5.0;
//    
//    // From the left hand side
//    
//    y =  k * y;
//    std::cout << y[0] << "\t" << y[1] << "\t"  << y[2] << "\t"  << y[3] << "\t" << y[4] << "\n";
//    
//    // From the right hand side
//    y = y * k;
//    std::cout << y[0] << "\t" << y[1] << "\t"  << y[2] << "\t"  << y[3] << "\t" << y[4] << "\n";
//    
//    // Calculate the norm of a vector
//    
//    z.CalculateNorm(2);
//    return 0;
//}



