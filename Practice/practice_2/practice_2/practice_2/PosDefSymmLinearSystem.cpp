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


Vector PosDefSymmLinearSystem::Solve()
{
    // Get the private element size
    
    int Size = GetSize();
    
    // Define the initial guess
    
    Vector x0(Size);
    double eps = 10e-6;
    
    // Introduce a reference to make it readable
    
    Matrix rA = GetInputMatrix();
    Vector rb = GetInputVector();
    
    // Test for symmetry
    
    for (int i = 0; i < Size; i++ )
    {
        for(int j = 0; i < Size; j++)
        {
            assert(rA(i, j) == rA(j, i));
        }
    }
    
    // Initialise difference
    
    Vector r(Size);
    Vector r_old(Size);
    r = rb - rA * x0;
    r_old = rb - rA * x0;
    
    // Initialise p and beta
    
    Vector p(Size);
    double beta = 0;
    
    
    // Begin the while loop
    
    while (r.CalculateNorm(2) >= eps)
    {
        
        beta = SumVector(r*r);
        
    }
    
    
    // forward sweep of Gaussian elimination
    for (int k=0; k<Size-1; k++)
    {
        // see if pivoting is necessary
        double max = 0.0;
        int row = -1;
        for (int i=k; i<Size; i++)
        {
            if (fabs(rA(i+1,k+1)) > max)
            {
                row = i;
                max=fabs(rA(i+1,k+1)); //NB bug in published version
            }
        }
        assert(row >= 0); //NB bug in published version
        
        // pivot if necessary
        if (row != k)
        {
            // swap matrix rows k+1 with row+1
            for (int i=0; i<Size; i++)
            {
                double temp = rA(k+1,i+1);
                rA(k+1,i+1) = rA(row+1,i+1);
                rA(row+1,i+1) = temp;
            }
            // swap vector entries k+1 with row+1
            double temp = rb(k+1);
            rb(k+1) = rb(row+1);
            rb(row+1) = temp;
        }
        
    return solution;
}
