//
//  Book.h
//  practice
//
//  Created by Luke Lloyd-Jones on 31/10/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//


// The BOOK CLASS
#ifndef BOOKHEADERDEF
#define BOOKHEADERDEF


#include <string>

class Book
{
public: // These can be accessed outside the class
    std::string author, title, publisher, format;
    int  price; // Given in dollars
    void SetYearOfPublication(int year) // Doesn't return a variable associated with a class called Book and SetYearOfPublication and requires an integer input
    {
        assert ((year > 1440) && (year < 2020)); // Check if it's within a reasonable year bracket
        mYearOfPublication = year;
    }
    
    int GetYearOfPublication() const
    {
        return mYearOfPublication;
    }
    // void SetYearOfPublication(int year); // Accept an integer argument but is void
    // int  GetYearOfPublication() const; // Signals the compiler that we want the instance of the class to remain constant throughout the execuation of the method
private: // These members cannot
    int mYearOfPublication; // m prefix allows us to know it's ours
};

#endif


