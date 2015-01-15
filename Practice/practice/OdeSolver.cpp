//
//  OdeSolver.cpp
//  practice
//
//  Created by Luke Lloyd-Jones on 15/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <fstream>
#include <sstream>
#include <array>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iomanip>  // setprecision()
#include <string>
#include <vector>
#include <cerrno> // something to help with reading in buffers
#include <set> // The STL set container
#include "AbstractOdeSolver.hpp"
#include "Exception.hpp"

using namespace std;

// Write all the preliminary functions to access and set things


// Functions to SET private variables

void AbstractOdeSolver::SetStepSize(double h)
{
    mstepsize = h;
}

void AbstractOdeSolver::SetTimeInterval(double t0, double t1)
{
    minitialTime = t0;
    mfinalTime   = t1;
}

void AbstractOdeSolver::SetInitialValue(double y0)
{
    minitialValue = y0;
}


// Functions to GET private variables


double AbstractOdeSolver::GetStepSize() const
{
    return mstepsize;
}

double AbstractOdeSolver::GetInitialTime() const
{
    return minitialTime;
}

double AbstractOdeSolver::GetFinalTime() const
{
    return mfinalTime;
}

double AbstractOdeSolver::GetInitialValue() const
{
    return minitialValue;
}

// Write the class methods for the Forward Euler Solver

#include "ForwardEulerSolver.hpp"

// Write the function to set the right hand side of the function to be solved. Requires the use of function pointers. Declare a function pointer *p_function.

double ForwardEulerSolver::RightHandSide(double t, double y)
{
    return -10*y;
}


double ForwardEulerSolver::SolveEquation()
{
    // Set some temporary variables

    double yi=0.0;
    double yi_1;
    double ti_1;

    // Access all the set private members

    int N=(GetFinalTime()-GetInitialTime())/GetStepSize();
    double h=GetStepSize();

    // Initialise the y0 and t0 values

    yi_1 = GetInitialValue();
    ti_1 = GetInitialTime();

    // Forward Euler update

    for (int i=0;i<N; i++)
    {
        yi=yi_1 + h*RightHandSide(ti_1,yi_1);
        ti_1=GetInitialTime() + i*h;
        // std::cout << "The yi th value " << yi << "\n";
        // std::cout << yi << "\n";
    }

    // Return the final result with the error check to within reasonable precision
    
    if (yi>0&&yi<10e-6)
    {
        return 0;
    }
    else if (yi>1&&yi<1+10e-6)
    {
        return 1;
    }
    else
    {   // y_i is between 0 and 1 and the error bounds
        return yi;
    }
}


#include "RungeKuttaSolver.hpp"

double RungeKuttaSolver::RightHandSide(double t, double y)
{
    return -y;
}


double RungeKuttaSolver::SolveEquation()
{
    // Set some temporary variables

    double yi=0.0;
    double yi_1;
    double ti_1;
    double k1=0.0;
    double k2=0.0;
    double k3=0.0;
    double k4=0.0;

    // Access all the set private members

    int N=(GetFinalTime()-GetInitialTime())/GetStepSize();
    double h=GetStepSize();

    // Initialise the y0 and t0 values

    yi_1 = GetInitialValue();
    ti_1 = GetInitialTime();

    // Runge-Kutta update

    for (int i=0;i<N; i++)
    {
        k1=h*RightHandSide(ti_1,yi_1);
        k2=h*RightHandSide(ti_1+(1.0/2.0)*h,yi_1+(1.0/2.0)*k1);
        k3=h*RightHandSide(ti_1+(1.0/2.0)*h,yi_1+(1.0/2.0)*k2);
        k4=h*RightHandSide(ti_1+h,yi_1+k3);
        yi=yi_1 + (1.0/6.0)*(k1+2*k2+2*k3+k4);
        ti_1=GetInitialTime() + i*h;
        // std::cout << "The yi th value " << yi << "\n";
        yi_1=yi;
    }

    // Return the final result with the error check to within reasonable precision
    
    if (yi>0&&yi<10e-6)
    {
        return 0;
    }
    else if (yi>1&&yi<1+10e-6)
    {
        return 1;
    }
    else if (yi<0||yi>1+10e-6)
    {
        throw (Exception("SOLUTION", "Solution out of bounds"));
    }
    else
    {   // y_i is between 0 and 1 and the error bounds
        return yi;
    }
}


// Operation for the Exception class
// ---------------------------------

// Constructor for exception class

Exception::Exception(std::string tagString, std::string probString)
{
    mTag = tagString;
    mProblem = probString;
}

//// Constructor for derived FileNotOpenException exception class
//
//#include "FileNotOpenException.hpp"
//
//FileNotOpenException::FileNotOpenException(std::string probStringDerived) : Exception("Cannot open file", probStringDerived)
//{
//    problemString=probStringDerived;
//}
//
//// Constructor for derived FileNotOpenException exception class
//
//#include "OutOfRangeException.hpp"
//
//OutOfRangeException::OutOfRangeException(std::string probStringDerived) : Exception("File out of range", probStringDerived)
//{
//    problemString=probStringDerived;
//}

// Exception print function

void Exception::PrintDebug() const
{
    std::cerr << "\n ** Error ("<<mTag<<") **\n";
    std::cerr << "Problem: " <<mProblem<< "\n\n";
}

//void ExceptionHandle() {
//    try {
//        throw;
//    }
//    catch (Exception& error)
//    {
//        error.PrintDebug();
//        std::cout << "Solution is not between 0 and 1 \n";
//        std::cout << "Your step size will be halved \n";
//        std::cout << "Your current step size is "<< GetStepSize()<< "\n";
//        //        double h_update=test_func_rgs.GetStepSize()/2.0;
//        //        test_func_rgs.SetStepSize(h_update);
//        //        std::cout << "Your next step size is "<< test_func_rgs.GetStepSize() << "\n";
//        //        std::cout << "Runge Kutter Solution is "  << test_func_rgs.SolveEquation() << "\n";
//    }
//}

// Main operations for testing
// ---------------------------

int main(int argc, char* argv[])
{

    // Create an instance of the class

    ForwardEulerSolver test_func_fes;
    RungeKuttaSolver test_func_rgs;

    // Set the elements for the problem

    test_func_fes.SetStepSize(0.1);
    test_func_fes.SetInitialValue(0.8);
    test_func_fes.SetTimeInterval(0.0,100);

    test_func_rgs.SetStepSize(25.0);
    test_func_rgs.SetInitialValue(0.8);
    test_func_rgs.SetTimeInterval(0.0,100);

    // Solve the differential system

    // std::cout << "Forward Euler Solution is " << test_func_fes.SolveEquation() << "\n";
    // std::cout << "Runge Kutter Solution is "  << test_func_rgs.SolveEquation() << "\n";
    
    // Try and use an exception that reduces the step size
    
    while (test_func_rgs.GetStepSize()>0.0001)
    {
    try
    {
        std::cout << "Runge Kutter Solution is "  << test_func_rgs.SolveEquation() << "\n";
        break;
    }
    catch (Exception& error)
    {
        error.PrintDebug();
        std::cout << "Solution is not between 0 and 1 \n";
        std::cout << "Your step size will be halved \n";
        std::cout << "Your current step size is "<< test_func_rgs.GetStepSize()<< "\n";
        double h_update=test_func_rgs.GetStepSize()/2.0;
        test_func_rgs.SetStepSize(h_update);
        std::cout << "Your next step size is "<< test_func_rgs.GetStepSize() << "\n";
        // std::cout << "Runge Kutter Solution is "  << test_func_rgs.SolveEquation() << "\n";

    }
    }


    return 0;
}
