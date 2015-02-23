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


// Solve using Gradient Descent


Matrix PosDefSymmLinearSystem::Solve()
{
    // Get the private element size
    
    int Size = GetSize();
    
    std::cout << "Get size done" << "\n";
    
    // Define the initial guess
    
    Matrix x0(Size, 1);
    double eps = 10e-6;
    
    std::cout << "Initial guess done" << "\n";
    
    // Introduce a reference to make it readable
    
    Matrix rA = GetInputMatrix();
    Matrix rb = GetInputVector();
    
    std::cout << "Get input matrix and vector done" << "\n";
    
    // Test for symmetry A=A^T
    
    Matrix t_rA = Transpose(rA);
    for (int i = 1; i <= Size; i++ )
    {
        for(int j = 1; i <= Size; j++)
        {
            assert(rA(i, j) == t_rA(j, i));
        }
    }
    
    std::cout << "Check symmetry done" << "\n";
    
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
