//
//  Header.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 9/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#ifndef EXCEPTIONDEF
#define EXCEPTIONDEF

#include <string>

class Exception
{
private:
    std::string mTag, mProblem;
public:
    Exception(std::string tagString, std::string probString); // Constructor
    void PrintDebug() const; // Print function
};

#endif
