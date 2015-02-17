//
//  Exception.cpp
//  practice_2
//
//  Created by Hayley Wise on 14/02/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//


#include <iostream>
#include "Exception.hpp"

//Constructor

Exception::Exception(std::string tagString, std::string probString)
{
    mTag = tagString;
    mProblem = probString;
}

void Exception::PrintDebug() const
{
    std::cerr << "** Error ("<<mTag<<") **\n";
    std::cerr << "Problem: " << mProblem << "\n\n";
}