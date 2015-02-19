//
//  Vector.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 19/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

#include <iostream>

class Vector
{
private:
    double* mData; // Data to be stored in the vector
    int mSize;     // Size of the vector
public:
    Vector(const Vector& otherVector);     // Copy constructor
    Vector(int size);
    ~Vector();                            // Destructor
    int GetSize() const;                  // Method for getting private size
    double& operator[] (int i) const;           // Overload the indexing operator
    double  Read(int i, const Vector& v1) const;     // Read-only zero-based indexing
    double& operator()(int i) const;       // One-based indexing
    Vector& operator = (const Vector& otherVector); // Overlaod assignment operator =
    Vector  operator + () const;        // Overlaod + unary operator
    Vector operator - () const;        // Overlaod - unary operator
    Vector operator + (const Vector& v1) const;        // Overlaod + binary operator
    Vector operator - (const Vector& v1) const;        // Overlaod - binary operator
    Vector operator * (double a) const; // Scalar multiplation RHS
    friend Vector operator * (const Vector& v1,
                            const Vector& v2); // Element wise multiplication
    friend Vector operator * (double a, Vector& v1); // Scalar multipli LHS
    double CalculateNorm(int p=2) const; // p-2-norm method
    friend double SumVector(const Vector& v) const; // p-2-norm method
    friend int length(const Vector& v); // Length friend funtion
    friend std::ostream& operator<<(std::ostream& output, const Vector& v1);
};

// Prototype signature of length() friend function

int length(const Vector& v);
Vector operator * (double a, Vector& v1);
Vector operator * (const Vector& v1, const Vector& v2);
std::ostream& operator<<(std::ostream& output, const Vector& v1);
#endif
