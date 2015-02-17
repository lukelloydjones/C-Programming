//
//  Vector.cpp
//  practice
//
//  Created by Luke Lloyd-Jones on 19/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#include <cmath>
#include <iostream>
#include <cassert>
#include "Vector.hpp"
#include "Exception.hpp"
// #include "<string>"

// Section 10.2 - Constructors and Destructors
// -------------------------------------------

// Encourage that the reader ensures that when dynamically
// allocation memory that every new statement is matched
// with a delete statement. If this is not done then
// the code may consume large amount of available memory
// Eventually the computer will run out of memory preventing
// the code from running further. Writing appropriate
// constructors and destructors for the vector and matric
// classes allows us to automatically match a delete statement
// through the calling of a destructor when the object goes out
// of scope. With every new statement hidden from the user of the
// class in a constructor.

// Overidden copy constructor
// Allocates memory for new vector, and copies
// entries of other vector into it

Vector::Vector(const Vector& otherVector)
{
    mSize = otherVector.GetSize();
    mData = new double [mSize];
    for (int i = 0; i < mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
}

// Constructor for vector of a given size
// Allocates memory, and initialises entries
// to zero

// Vector class allocates memory to  store a given vector
// when it is called.

Vector::Vector(int size)
{
    assert(size > 0);
    mSize = size;
    mData = new double [mSize];
    for (int i=0; i < mSize; i++)
    {
        mData[i] = 0.0;
    }
}


// Overridden destructor to correctly free memory

Vector::~Vector()
{
    delete[] mData;
}


// Method to get the size of a vector

int Vector::GetSize() const
{
    return mSize;
}

// Overloading square brackets
// Note that this uses ‘zero-based’ indexing,
// and a check on the validity of the index

double& Vector::operator[](int i) const
{
    assert(i > -1);
    assert(i < mSize);
    return mData[i];
}

// Read-only variant of [ ]
// Note that this uses 'zero-based' indexing,
// and a check on the validity of the index

double Vector::Read(int i, const Vector& v1) const
{
    return v1[i];
}

// Overloading round brackets
// Note that this uses 'one-based' indexing,
// and a check on the validity of the index

double& Vector::operator()(int i) const
{
    assert(i > 0);
    assert(i < mSize + 1);
    return mData[i-1];
}


// Overloading the assignment operator
// Make each element equal to the another
// vectors elements. Check that the size of the LHS
// vector is the same as the RHS vector.

Vector& Vector::operator=(const Vector& otherVector)
{
    // assert(mSize == otherVector.mSize);
    if (mSize != otherVector.mSize)
    {
        throw (Exception("VECTOR SIZES", "Size of LHS vector not equal to RHS"));
    }
    for (int i=0; i < mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
    return *this;
}

// Overloading the unary - operator
// Make each element equal to the negative of
// each element

Vector Vector::operator-() const
{
    Vector v(mSize);
    for (int i=0; i < mSize; i++)
    {
        v[i] = -mData[i];
    }
    return v;
}


// Overloading the binary + operator

Vector Vector::operator+(const Vector& v1) const
{
    assert(mSize == v1.mSize);
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = mData[i] + v1.mData[i];
    }
    return v;
}


// Overloading the binary - operator

Vector Vector::operator-(const Vector& v1) const
{
    assert(mSize == v1.mSize);
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = mData[i] - v1.mData[i];
    }
    return v;
}


// Overloading scalar multiplication

Vector Vector::operator*(double a) const
{
    Vector v(mSize);
    for (int i = 0; i < mSize; i++)
    {
        v[i] = a*mData[i];
    }
    return v;
}


// Overloading scalar multiplcation for the left hand side
// We use a friend function.

Vector operator * (double a, Vector& v) {
    
    return v * a;
}


// Method to calculate norm (with default value p=2)
// corresponding to the Euclidean norm

double Vector::CalculateNorm(int p) const
{
    
    double norm_val, sum = 0.0;
    for (int i=0; i<mSize; i++)
    {
        sum += pow(fabs(mData[i]), p);
    }
    
    norm_val = pow(sum, 1.0/((double)(p)));
    return norm_val;
}


// MATLAB style friend to get the size of a vector
// This friend component allows it to read the
// privat element mSize. We use const for the
// vector reference so that the vector passed
// is not changed.

int length(const Vector& v)
{
    return v.mSize;
}


// Code to write out a vector to the screen

std::ostream& operator<<(std::ostream& output, const Vector& v1)
{
    
    for (int i = 0; i < v1.GetSize(); i++)
    {
        output << v1.Read(i, v1) << "\n";
    }
    output << std::endl;
    return output;
}






