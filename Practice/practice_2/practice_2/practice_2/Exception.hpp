//
//  Exception.hpp
//  practice_2
//
//  Created by Hayley Wise on 14/02/2015.
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
    Exception(std::string tagString, std::string probString); void PrintDebug() const;
};


#endif
