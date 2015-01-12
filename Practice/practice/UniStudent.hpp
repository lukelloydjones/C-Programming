//
//  UniStudentClass.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 20/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

// 7.1 Write a class of students that have the following public memebers
// - a string for the student's name
// - a double precision variable that store the library fines owed by the student
// - a double precision floating point variable the stores the tuition fees
// - a method that return the total money owed by the student, that is the sum of the
// - library fines and tuition fees associated with a given student
// - a few constructors that take different arguments

#ifndef UNISTUDENTDEF
#define UNISTUDENTDEF

#include <string>

class UniStudent
{
private:
    double mlibraryFines;
public:
    UniStudent();
    UniStudent(double x, double y);
    std::string name;
    double tuitionFees;
    void SetLibraryFines(double h);
    double GetLibraryFines() const;
    virtual double CalculateTotalMoneyOwing();
    
};


#endif
