//
//  Ebook.hpp
//  practice
//
//  Created by Hayley Wise on 15/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef EBOOKHEADERDEF
#define EBOOKHEADERDEF

#include <string>
#include "Book.hpp"

class Ebook: public Book // Sayes that Ebook is a derived class of Book
{
public:
    Ebook();
    std::string hiddenUrl;
};


#endif
