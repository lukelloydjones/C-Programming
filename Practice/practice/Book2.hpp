//
//  Book2.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 4/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef BOOKHEADERDEF
#define BOOKHEADERDEF

#include <string>

class Book2
{
public:
    Book2();
    Book2(const Book2& otherBook);
    Book2(std::string bookTitle);
    std::string author, title, publisher, format;
    int price; // Given in dollars bitches
    void SetYearOfPublication(int year);
    int GetYearOfPublication() const;
private:
    int mYearOfPublication;
};


#endif
