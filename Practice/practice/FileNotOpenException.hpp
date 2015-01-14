//
//  FileNotOpenException.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 13/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#ifndef FILENOTOPENEXCEPTIONDEF
#define FILENOTOPENEXCEPTIONDEF

#include <string>
#include "Exception.hpp"

class FileNotOpenException: public Exception
{
private:
    std::string problemString;
public:
    FileNotOpenException(std::string probStringDerived);
};
    
#endif