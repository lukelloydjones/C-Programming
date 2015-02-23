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
    PosDefSymmLinearSystem(const Matrix& A, const Matrix& b): LinearSystem(A, b){}
    Matrix Solve();
};

#endif
