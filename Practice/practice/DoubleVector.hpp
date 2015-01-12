//
//  DoubleVector.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 10/12/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#include <cassert>


// THIS IS A TEMPLATED CLASS
// -------------------------

// We can declare instances of DoubleVector specifying the length of the array. The entries of this class are private members and can't be accessed as in normal arrays. We overide the the square bracket operator. This overloading allows a check to see if the index is valid before returning the variable requested.

template<unsigned int DIM> class DoubleVector
{
private:
    double mData[DIM];
    
public:
    double& operator[](int index) // overloading the [] operator
    {
        assert(index <DIM);
        assert(index>-1);
        return(mData[index]);
    }
};
