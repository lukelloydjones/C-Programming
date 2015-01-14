//
//  OutOfRangeException.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 13/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#ifndef OUTOFRANGEEXCEPTIONDEF
#define OUTOFRANGEEXCEPTIONDEF

#include <string>
#include "Exception.hpp"

class OutOfRangeException: public Exception
{
private:
    std::string problemString;
public:
    OutOfRangeException(std::string probStringDerived);
};

#endif



