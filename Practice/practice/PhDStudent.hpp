//
//  PhDStudent.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 20/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef PHDSTUDENTDEF
#define PHDSTUDENTDEF

#include "GraduateStudent.hpp"

class PhDStudent:public GraduateStudent
{
public:
    std::string time;
    GraduateStudent(double x, double y);
    virtual double CalculateGraduateMoneyOwing(double y, double t) = 0;
};

#endif
