//
//  Guest.hpp
//  practice
//
//  Created by Hayley Wise on 15/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef GUESTDEF
#define GUESTDEF

#include <string>

class Guest
{
public:
    std::string name, roomType, arrivalDate;
    int numberOfNights;
    double telephoneBill;
    virtual double CalculateBill();
    
};


#endif
