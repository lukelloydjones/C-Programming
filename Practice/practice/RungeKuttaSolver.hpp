//
//  RungeKuttaSolver.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 5/12/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef RUNGEKUTTASOLVERDEF
#define RUNGEKUTTASOLVERDEF

class RungeKuttaSolver:public AbstractOdeSolver
{
public:
    double RightHandSide(double y, double t);
    double SolveEquation();
};


#endif
