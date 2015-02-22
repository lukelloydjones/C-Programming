//
//  PosDefSymmLinearSystem.cpp
//  practice_2
//
//  Created by Luke Lloyd-Jones on 19/02/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#include "PosDefSymmLinearSystem.hpp"
#include <cmath>
#include <cassert>


//// Copy matrix and vector so that original matrix and vector
//// specified are unchanged by Gaussian elimination
//PosDefSymmLinearSystem::PosDefSymmLinearSystem(const Matrix& A, const Matrix& b) : LinearSystem(A, b)
//{
//    // check matrix and vector are of compatible sizes
//    int local_size = A.GetNumberOfRows();
//    assert(A.GetNumberOfColumns() == local_size);
//    assert(b.GetNumberOfRows() == local_size);
//    
//    // set variables for linear system
//    mSize = local_size;
//    mpA = new Matrix(A);
//    mpb = new Matrix(b);
//}


// Solve using Gradient Descent


Matrix PosDefSymmLinearSystem::Solve()
{
    // Get the private element size
    
    int Size = GetSize();
    
    // Define the initial guess
    
    Matrix x0(Size, 1);
    double eps = 10e-6;
    
    // Introduce a reference to make it readable
    
    Matrix rA = GetInputMatrix();
    Matrix rb = GetInputVector();
    
    // Test for symmetry A=A^T
    
    for (int i = 0; i < Size; i++ )
    {
        for(int j = 0; i < Size; j++)
        {
            assert(rA(i, j) == rA(j, i));
        }
    }
    
    // Initialise difference
    
    Matrix r(Size, 1);
    Matrix r_old(Size, 1);
    r = rb - rA * x0;
    r_old = rb - rA * x0;
    
    // Initialise p, beta, lpha
    
    Matrix p(Size, 1);
    Matrix beta(1, 1);
    Matrix alpha(1, 1);
    Matrix x_new(Size, 1);
    
    // Begin the while loop
    
    while (r.CalculateNorm(2) >= eps)
    {
        
        beta  = Multiply(Transpose(r), r) / Multiply(Transpose(r_old), r_old);
        p = r + beta * p ;
        alpha = Multiply(Transpose(r), r) / (Multiply(Multiply(Transpose(p), rA), p));
        x_new = x0 + alpha*p;
        r_old = r;
        r = rb - rA*x_new;
        x0 = x_new;
    }
    
        
    return x_new;
}
