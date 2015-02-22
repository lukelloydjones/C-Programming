//
//  PosDefSymmLinearSystem.hpp
//  practice_2
//
//  Created by Luke Lloyd-Jones on 19/02/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#ifndef PosDefSymmLinearSystemDef
#define PosDefSymmLinearSystemDef

#include "LinearSystem.hpp"
#include <cassert>
class PosDefSymmLinearSystem: public LinearSystem
{
public:
    PosDefSymmLinearSystem(const Matrix& A, const Matrix& b) : LinearSystem(A, b){
        // check matrix and vector are of compatible sizes
        int local_size = A.GetNumberOfRows();
        assert(A.GetNumberOfColumns() == local_size);
        assert(b.GetNumberOfRows() == local_size);
        
        // set variables for linear system
        mSize = local_size;
        mpA = new Matrix(A);
        mpb = new Matrix(b);
    };
    
    Matrix Solve();
};

#endif
