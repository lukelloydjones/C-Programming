//
//  AbstractOdeSolver.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 18/11/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef ABSTRACTODESOLVERDEF
#define ABSTRACTODESOLVERDEF

class AbstractOdeSolver
{
private:
    double mstepsize;    // h
    double minitialTime; // T0
    double mfinalTime;   // T1
    double minitialValue; // Y0
public:
    
    // Set the private elements
    
    void SetStepSize(double h);
    void SetTimeInterval(double t0, double t1);
    void SetInitialValue(double y0);
    
    // Set the private elements
    
    double GetStepSize() const;
    double GetTimeInterval() const;
    double GetInitialValue() const;
    double GetInitialTime() const;
    double GetFinalTime() const;
    
    // Write the virtual functions needed for different derived classes
    
    virtual double RightHandSide(double y, double t) = 0; // The = 0 syntax defines a non initiated virtual funtion
    virtual double SolveEquation() = 0; // These are pure virtual functions

};

#endif
