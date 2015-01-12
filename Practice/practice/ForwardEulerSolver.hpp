//
//  ForwardEulerSolver.h
//  practice
//
//  Created by Luke Lloyd-Jones on 5/12/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef FORWARDEULERSOLVERDEF
#define FORWARDEULERSOLVERDEF

#include "AbstractOdeSolver.hpp"

class ForwardEulerSolver:public AbstractOdeSolver
{
public:
    double RightHandSide(double y, double t);
    double SolveEquation();
};

#endif
