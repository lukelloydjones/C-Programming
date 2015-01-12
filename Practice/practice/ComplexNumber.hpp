//
//  ComplexNumber.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 7/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>

class ComplexNumber
{
private:
    double mRealPart;
    double mImaginaryPart;
public:
    ComplexNumber();
    ComplexNumber(double x, double y);
    ComplexNumber(double x);
    // ComplexNumber(int numRows, int numCols);
    ComplexNumber(const ComplexNumber& anotherComplexNumber);
    double CalculateModulus() const;
    double CalculateArgument() const;
    ComplexNumber CalculateConjugate() const;
    double GetRealPart() const;
    double GetImaginaryPart() const;
    friend double GetRealPart(const ComplexNumber& complexNum);
    friend double GetImaginaryPart(const ComplexNumber& complexNum);
    void SetConjugate();
    ComplexNumber operator/(int n) const;
    ComplexNumber CalculatePower(double n) const;
    ComplexNumber& operator=(const ComplexNumber& z);
    ComplexNumber operator-() const;
    ComplexNumber operator+(const ComplexNumber& z) const;
    ComplexNumber operator-(const ComplexNumber& z) const;
    friend std::ostream& operator<<(std::ostream& output, const ComplexNumber& z);
};


#endif
