//
//  Example.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 5/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef EXAMPLECLASSDEF
#define EXAMPLECLASSDEF

class ExampleClass
{
private:
    double mMemberVariable1;
    double mMemberVariable2;
public:
    ExampleClass(double member1, double member2);
    double GetMinimum() const;
    friend double GetMaximum(const ExampleClass& egClass);
};
#endif
