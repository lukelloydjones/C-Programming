//
//  TwoByTwo.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 13/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef practice_TwoByTwo_hpp
#define practice_TwoByTwo_hpp

class TwoByTwo
{
private:
    double** mData; // entries of matrix
    int mNumRows, mNumCols; // dimensions
public:
    TwoByTwo(); // An overridden default constructor that initialises all entries of the matric to zero
    TwoByTwo(const TwoByTwo& anotherTwoByTwo); // An overridden copy constructor
    // TwoByTwo(int numRows, int); // A constructor that allocates the
    double CalculateDeterminant() const; // A method to calculate the determinant of a matrix
    TwoByTwo CalculateInverse() const;   // A method to calculate the inverse of a matrix if it exists
    TwoByTwo CalculateProduct() const;   // A method to calculate the product of a matrix
    TwoByTwo& operator=(const  TwoByTwo& A); // Overload the assingment operator
    TwoByTwo operator-() const; // Overload the unary operator so we can write A = -B
    TwoByTwo operator+(const TwoByTwo& A) const; // Overload the unary operator so we can write A = B + C
    ~TwoByTwo(); //
//    ComplexNumber(double x, double y);
//    ComplexNumber(double x);
//    // ComplexNumber(int numRows, int numCols);
//    ComplexNumber(const ComplexNumber& anotherComplexNumber);
//    double CalculateModulus() const;
//    double CalculateArgument() const;
//    ComplexNumber CalculateConjugate() const;
//    double GetRealPart() const;
//    double GetImaginaryPart() const;
//    friend double GetRealPart(const ComplexNumber& complexNum);
//    friend double GetImaginaryPart(const ComplexNumber& complexNum);
//    void SetConjugate();
//    ComplexNumber operator/(int n) const;
//    ComplexNumber CalculatePower(double n) const;
//    ComplexNumber& operator=(const ComplexNumber& z);
//    ComplexNumber operator-() const;
//    ComplexNumber operator+(const ComplexNumber& z) const;
//    ComplexNumber operator-(const ComplexNumber& z) const;
//    friend std::ostream& operator<<(std::ostream& output, const ComplexNumber& z);
};



#endif
