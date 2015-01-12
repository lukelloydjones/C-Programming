//
//  GraduateStudent.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 20/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef GRADUATEUNISTUDENTDEF
#define GRADUATEUNISTUDENTDEF

#include "UniStudent.hpp"

class GraduateStudent:public UniStudent
{
public:
    std::string time;
    GraduateStudent(double x, double y);
    double CalculateTotalMoneyOwing();
};


#endif
