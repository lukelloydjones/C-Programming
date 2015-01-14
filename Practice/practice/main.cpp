//
//  main.cpp
//  practice
//
//  Created by Luke Lloyd-Jones on 8/09/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
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

// Set the namespace std

using namespace std;

/************************************************************************
 ************************************************************************
 **                                                                    **
 **            Chapter 9 - Errors and Exceptions                       **
 **                                                                    **
 ************************************************************************
 ************************************************************************/


// Section 9.6 - Excercises
// ------------------------

// Excercise 3

// Problem 7.3. Suppose that the solution of the ode represents a prob of some event
// happening as time evolves. The true solution should be non-negative and no
// greater than 1. Slight violations of this are acceptable and thus we extend the
// library to handle these requirements in a way that is consitent with the
// of dealing with errors in section 9.2.

// Assume that an acceptable absolute error is 10e-6. When solving the diff equation
// we won't be concerned if the solution for a value of yi in problem 7.3 lies in
// in the interval -10e-6<y_i<0. Under these circumstance we simply write 0.0
// to file containing the solution at eaxh time ti and the value yi. If the solution
// lies in the interval 1 < y_i < 1+10e-6 we write 1.0 to file. This is an instance
// type 1 error.

// #1-IF THE ERROR CAN BE FIXED SAFELY, THEN FIX IT. IF NEED BE WARN THE USER

// Now suppose the value of yi lies further outside the range of acceptabel value.
// The most likely reason is a h that is too large. Under this circumstance an
// exception should be thrown explaining this. The code that calls the library for
// the initial value problem ode would then know to reduce the step size: a suitable
// new step size would be half of the step size currently being used. This is an
// instance of an error of #2

// #2 - If the error could be caused by some reasonable user input then throw an excep-tion up to the calling code, since the calling code should have enough context to fix the problem.

// It is possible that an error has been made elsewhere in the library or in the
// used to call the library. Under these circumstances persisting with making the
// size smaller may not solve the problem. We therefore want to terminates the code
// if the step size falls below some critical threshold. This is type 3 #3

// #3 -  If the error should not happen under normal circumstances then trip an assertion.

// PROBLEM

// Incorporate the error handling procedure described above into the library for
// solving initial value odes. Test this using the error handling using the example
// dy/dt = -100y, with initial condition y=0.8 when t=0, for the time interval 0<t<100. Investigate how different values of the step size h affect the error handling implemented.




// Excercise 2

// Section 4.3.2 showed how it was possible for bad memory allocation to terminate
// your program. If you want your program to continue through a memory allocation
// error there are two ways to cope with the exception: to turn the exception off
// (and check the value of the pointer) or catch the exception.

//int main(int argc, char* argv[])
//{
//    double* p_x;
//    
//    try
//    {
//    p_x = new double[100000000000000];
//    }
//    catch (std::bad_alloc& badAlloc)
//    {
//        std::cout << "Allocation failed\n";
//        std::cout << "Give an alternative size of the vector\n";
//        int newSize;
//        std::cin >> newSize;
//        p_x = new double[newSize];
//    }
//    
//    delete p_x;
//    return 0;
//}

// Excercise 1

// Extend the Exception class by creating two inherited classes 'OutOfRangeException" and "FileNotOpenException". The constructors for each of the two classes should take only the probString argument and should set the tagString member to an appropriate string. Write a catch block which is able to catch a gneric exception but can also differentiate between these two types of error.

// Constructor for FileNotOpenException exception class
//
//#include "FileNotOpenException.hpp"
//
//FileNotOpenException::FileNotOpenException(std::string probStringDerived) : Exception("Cannot open file", probStringDerived)
//{
//    problemString=probStringDerived;
//}
//
//// Constructor for FileNotOpenException exception class
//
//#include "OutOfRangeException.hpp"
//
//OutOfRangeException::OutOfRangeException(std::string probStringDerived) : Exception("File out of range", probStringDerived)
//{
//    problemString=probStringDerived;
//}

// Section 9.5 - Test-Driven Development
// -------------------------------------

// The following tips may help to get the most out of test driven development
// 1. Use a C++ testing framework such as googletest. This will help structure your tests
// 2. Add one or more tests for every new piece of functionality.
// 3. Make tests definitive-they should either pass or fail. Beware of floating point tolerances and allow for rounding errors in caclulations.
// 4. Remember to write tests for corner cases. That is cases that are rare but may cause problems collinear triangles, singular matrices, the complex number 0+0i
// 5. Review your tests from time to time. Add new tests as necessary and remove only those which you know to be redundant.
// 6. Automate your testing, so that you do not have to remember to run the tests or remember to check the results.

// We have been using assertions to check for things up to this point we are going to change that

// Section 9.1 - Preconditions
// ---------------------------

// 9.1.1 Example of two implementations of a graphics function

// A story about a professor and the rendering of an annulus

// Section 9.2 - Three Levels of Errors
// ------------------------------------

// 1. If the error can be fixed safely, the fix it. If need be, warn the user.
// 2. If the error could be caused by some reasonable user input then throw
// an exception up to the calling code, since the calling code should have enough
// context to fix the problem
// 3. If the error should not happen under normal circumstance then trip and assertion.

// Section 9.3 - Introducing the Exception
// ---------------------------------------

// There exists a class called exception. The use of exceptions requires the keywords 'try', 'throw', and 'catch'.

// 'try' is used in the calling code and tells the program to execute some statements in the knowledge that some error might happen
// 'throw' is used when the error is identified. the fun will encaosulate information about the error into an exception object and throw it back to the caller.
// 'catch' is used in the calling code to show how to attempt to fix the error. Every block of code that has the 'try' keyword must be match by a 'catch' block.
// Exeptions that are not caught by the calling code may cause the program to halt.

// When an error occurs we want the code to throw a one work summary of the problem type and a more lengthy description of the error. We write a class 'Exception' to store these two pieces of information with the ability to print this information when required.

//#include "Exception.hpp"
//
//
//// Constructor for exception class
//
//Exception::Exception(std::string tagString, std::string probString)
//{
//    mTag = tagString;
//    mProblem = probString;
//}
//
//// Constructor for FileNotOpenException exception class
//
//#include "FileNotOpenException.hpp"
//
//FileNotOpenException::FileNotOpenException(std::string probStringDerived) : Exception("Cannot open file", probStringDerived)
//{
//    problemString=probStringDerived;
//}
//
//// Constructor for FileNotOpenException exception class
//
//#include "OutOfRangeException.hpp"
//
//OutOfRangeException::OutOfRangeException(std::string probStringDerived) : Exception("File out of range", probStringDerived)
//{
//    problemString=probStringDerived;
//}
//
//// Exception print function 
//
//void Exception::PrintDebug() const
//{
//    std::cerr << "** Error ("<<mTag<<") **\n";
//    std::cerr << "Problem: " <<mProblem<< "\n\n";
//}
//
//
//// Listing 3.4 we read from an output file. We assume that the file exists and throw an error if it did not. Below is a more sophisticate read function
//
//void ReadFile(const std::string& fileName, double x[], double y[])
//{
//    std::ifstream read_file(fileName.c_str());
//    if (read_file.is_open() == false)
//    {
//        throw (Exception("FILE", "File can't be opened"));
//    }
//    for (int i=0; i<6; i++)
//    {
//        read_file >> x[i] >> y[i];
//    }
//    read_file.close();
//    
//    std::cout << fileName << " read successfully\n";
//}
//
//int main(int argc, char* argv[])
//{
//    double x[6], y[6];
//     try {
//        ReadFile("Output.dat", x, y);
//    } catch (Exception& error)
//    {
//        // FileNotOpenException err("File can't be opened");
//        // exception.PrintDebug();
//        // Exception& error;
//        error.PrintDebug();
//        std::cout << "Couldn't open Output.dat\n";
//        std::cout << "Give alternative location\n";
//        std::string file_name;
//        std::cin >> file_name;
//        ReadFile(file_name, x, y);
//   }
//    return 0;
//}

/************************************************************************
 ************************************************************************
 **                                                                    **
 **            Chapter 8 - Templates                                   **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

// Section 8.5 - Excercises
// ------------------------

// Ex 8.4 - Modify the example of an STL set given in Sect 8.3.2 so that the coordinates of the point are now given by double precision floating point variables.

// #include "Point2d.hpp"

//int main(int argc, char* argv[])
//{
//    std::set<Point2d> points;
//    Point2d origin(0.0,0.0);
//    points.insert(origin);
//    points.insert(Point2d(-2.4, -5.9));
//    points.insert(Point2d(-1.45, -3.98));
//    points.insert(Point2d(2, 4));
//    
//    
//    std::cout << "Number of points in set = " << points.size() << "\n";
//    
//    std::set<Point2d>::const_iterator c;
//    for (c=points.begin(); c!=points.end(); c++)
//    {
//        std::cout << c->v << " " << c->z << "\n";
//    }
//    
//    return 0;
//}

// Ex 8.3 - Use the class of complex numbers in Sect 6.4 to create an STL vector of complex numbers. Investigate the functionality of the STL demonstrated in Sec. 8.3.1 using this vector of complex numbers. When you add an object in an STL vector it is a copy which is added, so the copy constructor must be working as expected.

#include "ComplexNumber.hpp"

//int main(int argc, char* argv[])
//{
//    // Declare an STL vector of complex numbers of length 4
//    
//    std::vector<ComplexNumber> complex_number_vector;
//    complex_number_vector.reserve(6);
//    
//    // Create 4 complex numbers
//    
//    ComplexNumber z1(4.0,3.0);
//    ComplexNumber z2(4.4,31.0);
//    ComplexNumber z3(4.0,5.0);
//    ComplexNumber z4(9.0,1.0);
//    
//    // Add these to the vector
//    
//    complex_number_vector.push_back(z1);
//    complex_number_vector.push_back(z2);
//    complex_number_vector.push_back(z3);
//    complex_number_vector.push_back(z4);
//    
//    // What's the length of the vector?
//    
//    std::cout << "Length of vector is " << complex_number_vector.size() << "\n";
//    
//    // Print out the entries of the vector
//    
//    for (int i=0; i<4; i++)
//    {
//        std::cout << complex_number_vector[i] << "\n";
//    }
//    
//    // Print out the entries of the vector 2
//    
//    std::vector<ComplexNumber>::const_iterator comp_num_iter;
//    for (comp_num_iter=complex_number_vector.begin(); comp_num_iter!=complex_number_vector.end(); comp_num_iter++)
//    {
//        std::cout << *comp_num_iter << "\n";
//    }
//    
//    // Add in a new complex number at the beggining of the vector
//    
//    ComplexNumber z5(2.0,33.3);
//    complex_number_vector.insert(complex_number_vector.begin(),z5);
//    
//    // Print them all out again
//    
//    for (comp_num_iter=complex_number_vector.begin(); comp_num_iter!=complex_number_vector.end(); comp_num_iter++)
//    {
//        std::cout << *comp_num_iter << "\n";
//    }
//    
//    // Try and use the sort function
//    
//    sort(complex_number_vector.begin(),complex_number_vector.end());
//    
//    // Print them all out again
//    
//    for (comp_num_iter=complex_number_vector.begin(); comp_num_iter!=complex_number_vector.end(); comp_num_iter++)
//    {
//        std::cout << *comp_num_iter << "\n";
//    }
//    
//}

// Ex 8.2 - Use templates to write a single function that may be used to calculate the absolute value of an integer or a double precision floaitng point number.

// Define the prototype

//template<class U> U AbsValue(U value);
//
//// Use the absolute value function for integers
//
//int main(int argc, char* argv[])
//{
//    std::cout << AbsValue<int>(-10) << "\n";
//    std::cout << AbsValue<double>(-10.25) << "\n";
//}
//
//// Write the template function
//
//template<class U> U AbsValue(U value)
//{
//    U output;
//    if (value < 0)
//    {
//        output = -value;
//    }
//    else
//    {
//            // If the value is greater than 0
//        output = value;
//    }
//    return output;
//}

// Ex 8.1 - N days of probabilities. These values should take value between 0 and 1 inclusive. However, they may be only correct to an absolution error of -10^-6
// 1+10^-6 inclusive. Using the ideas of section 8.1 use templates so that the value
// store by the array is returned if it is 0-1 inclusive, the value 0 is returned if the value is between -10^-6 and 0 inclusive, and 1 for 1+10^-6 and an assertion is tripped otherwise

//#include "RainyDays.hpp"
//
//
//int main(int argc, char* argv[])
//{
//    RainyDays<4> x;
//    x[0] = 0.98;
//    x[1] = 1.00000001;
//    x[2] = 0.111;
//    x[3] = -0.000000001;
//    // x[3] = 2;
//    // x[4] = 9.0;
//    
//    std::cout << "What's in the box " << x[3] << "\n";
//}


// Section 8.4 - Tips - Template Compilation
// -----------------------------------------

// When including classes we can avoid compiling it everytime time it is used by using explicit instantiation. We make the class in a .hpp file and make an unnamed instance of the required size in the .cpp file come

// #include "DoubleVector.hpp"

// template class DoubleVector<5>;
// tenplate class DoubleVector<7>;







// Section 8.3 - Survey of the standard template library
// -----------------------------------------------------

// Using random access vectors and sets are dynamic arrays. Other containers include maps, multimaps, multisets, lists and deques. These have less relevance to scientific computing, but they exist

// Section 8.3.1 Sets
// ------------------

// A set is an STL container where entries are only stored if they are distinct from the entries already stored. May be more efficient. The elements of the set must be ordered. The class Point2d representing the class of points in two dimensions is given in the listing  below. There is a constructor that allows the initialisation of the coordinates and an averloaded < operator, which allows us to order points in two dimensions as described above.

//#include "Point2d.hpp"
//#include <set>
//
//int main(int argc, char* argv[])
//{
//    std::set<Point2d> points; // Create a set made up of the instances of the class Point2d
//    Point2d origin(0, 0); // This point is equivalent to the one below. Only one is stored
//    points.insert(origin);
//    points.insert(Point2d(2, 1));
//    points.insert(Point2d(-2, -5));
//    points.insert(Point2d(0, 0));
//    
//    std::cout << "Number of points in set = " << points.size() << "\n"; // Use the size method
//    
//    std::set<Point2d>::const_iterator c;
//    for (c=points.begin(); c!=points.end(); c++)
//    {
//        std::cout << c->x << " " << c->y << "\n";
//    }
//    
//    return 0;
//}

//class Point2d
//{
//public:
//    int x, y;
//    // Constructor
//    Point2d(int a, int b)
//    {
//        x=a;
//        y=b;
//    }
//    bool operator < (const Point2d& other) const
//    {
//        if (x < other.x)
//        {
//            return true;
//        }
//        else if (x > other.x)
//        {
//            return false;
//        }
//        else if (y<other.y)
//        {
//            // x == other.x
//            return true;
//        }
//        else
//        {
//            // x == other.x
//            // y >= other.y
//            return false;
//        }
//    }
//    
//};

// Section 8.3.1 Vectors
// ---------------------

// The STL vector class is extensible, which implies that its size is not fixed either at compile time or at the time that it is created. It can grow to accomodate new items as necessary. List is quite efficient at delete or inserting elements anywhere in the container.

// To use the vector container you need the vector header file and the algorithm header file for some vector algorithms


//int main(int argc, char* argv[])
//{
//    
//    // Define the vector
//    
//    std::vector<std::string> destinations;
//    
//    
//    // Add some elements and reserve 6 spots. Don't have to decalre the size of the vector.
//    
//    destinations.reserve(6);
//    destinations.push_back("Paris"); // The push_back method appends a copy of this string to the current vector
//    destinations.push_back("New York");
//    destinations.push_back("Singapore");
//    
//    
//    // Use the method "size" for accessing the number of elements of a vector
//    
//    std::cout << " Length of vector is " << destinations.size() << "\n";
//    std::cout << " Length of vector is " << destinations.size() << "\n";
//    
//    
//    // Accessing elements of the vector is still the same
//    
//    for (int i=0; i<3; i++)
//    {
//        std::cout << destinations[i] << "\n";
//    }
//    
//    // Accessing elements using an iterator. We can use the begin and end methods. The iterator points at the entries of the vector
//    
//    std::vector<std::string>::const_iterator c;
//    for (c=destinations.begin(); c!=destinations.end(); c++)
//    {
//        std::cout << *c << "\n";
//    }
//    
//    // Add a string to the start of a vector by using insert
//
//    destinations.insert(destinations.begin(), "Sydney"); // Put at the start
//    destinations.insert(destinations.begin()+1, "Moscow"); // Put at the second position
//    destinations.push_back("Frankfurt");   // Add another element to the vector
//    
//    
//    // Print the elements of the vector
//    
//    std::cout << " Length of vector is " << destinations.size() << "\n";
//    std::cout << " Entries of vector are \n";
//    
//    for (c=destinations.begin(); c!=destinations.end(); c++)
//    {
//        std::cout << *c << "\n";
//    }
//    
//    
//    // Erase from the fourth position to the end of the vector
//    
//    destinations.erase(destinations.begin()+3,destinations.end());
//    
//    std::cout << " Length of vector is " << destinations.size() << "\n";
//    std::cout << " Entries of vector are\n";
//    
//    
//    for (c=destinations.begin(); c!=destinations.end(); c++)
//    {
//        std::cout << *c << "\n";
//    }
//    
//    // Use the sort function to sort the vector of strings alphabetically
//    
//    sort(destinations.begin(), destinations.end());
//    
//    std::cout << "Length of vector is " << destinations.size() << "\n";
//    std::cout << "Entries of vector are\n";
//    
//    for (c=destinations.begin(); c!=destinations.end(); c++)
//    {
//        std::cout << *c << "\n";
//    }
//    
//    return 0;
//    
//}


// Section 8.2 - Templates for Polymorphism
// ----------------------------------------

// Distinguishing between integers and floating point variables is a good thing. If you want to write a function that can be used for both integers and floats then we have to write two different functions.


template<class T> T GetMaximum(T number1, T number2); // This looks like a template prototype

//int main(int argc, char* argv[])
//{
//    std::cout << GetMaximum<int>(10,-2) << "\n";
//    std::cout << GetMaximum<double>(10.44,-2.9) << "\n";
//}

// This is a function which can take both integers and double. The function prototpe defines that the function is defined for a general class T, and that the return type and the arguments with be instances of the same class T. To call the function we have put the data type used in angled brackets. This function is polymorphic because it can do the same function on different input arguments. Also called static polymorphism because when the compiler see line 7 and 8 of this listing it makes a specific verison of GetMaximum ready for the int or double type.

template<class T> T GetMaximum(T number1, T number2)
{
    T result;
    if (number1>number2)
    {
        result=number1;
    }
    else
    {
        // number1 <= number2
        result = number2;
    }
    
    return result;
}

// Section 8.1 - Templates to Control Dimensions and Verify Sizes
// --------------------------------------------------------------

// In scientific computing most problems are underpinned by vectors and matices. We may have problems accessing when we try and access and element of an array that doesn't exist but this will often not throw an error in C++. We can check for this using a templated class


#include "DoubleVector.hpp"

//int main(int argc, char* argv[])
//{
//    // When using the class we must declare v as a DoubleVector with the size enclosed within pointed brackets. 
//    DoubleVector <5> v;
//    v[0]=1.0; // This is OK
//    v[7]=5.0; // This will hopefully trip the assertion
//    return 0;
//}

// Want a function that returns the larger of two number, but want it to work for integers and double precision floating point variables. Could use functions overloading and write two functions. This would be ok for these small functions but for larger functions that perform the same function this would be problematic. This is where templates come in. This really allows deep generality to be incorporated in the code. We can use the standard template library.



/************************************************************************
 ************************************************************************
 **                                                                    **
 **            Chapter 7 - Inheritance and Derived Classes             **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

// Section 7.8 - Excercises
// ------------------------

// Section 7.8.3 - Excercise 3
// ---------------------------

// Calculate the numerical solution to initial value ODEs of the form dy/dt=f(t,y) for some specific function f(t,y), where y=Y0 at t=T0 for an initial value Y0 at some initial time T0. We want to calculate a numerical solution in the time interval T0<t<T1 where T1 is the final time. We need an integration step size denoted h. Each method that could be used to solve this requires different inputs and thus could be code very effectively using an abstract class 


    // Going to use the Euler method and the Runge-Kutta method. Step size h, define points ti, i=0,1,2,....N by ti=T0+ih,

    // where h is chosen so that tN=T1. The numerical solution at these points is denoted by yi, y=0,1,2,....,N. The solutions yi are determined by the numerical technique chosen.

    // For the forward Euler method we set y0=Y0. For i=1,2,....,N, yi is given by
    //                  yi=yi-1 + hf(ti-1, yi-1)

    // For the fourth order Runge-Kutta method, we set y0=Y0. For i=1,2,....,N, we calculate yi using the following 

//#include "AbstractOdeSolver.hpp"
//
//// Write all the preliminary functions to access and set things
//
//
//// Functions to SET private variables
//
//void AbstractOdeSolver::SetStepSize(double h)
//{
//    mstepsize = h;
//}
//
//void AbstractOdeSolver::SetTimeInterval(double t0, double t1)
//{
//    minitialTime = t0;
//    mfinalTime   = t1;    
//}
//
//void AbstractOdeSolver::SetInitialValue(double y0)
//{
//    minitialValue = y0;
//}
//
//
//// Functions to GET private variables
//
//
//double AbstractOdeSolver::GetStepSize() const
//{
//    return mstepsize;
//}
//
//double AbstractOdeSolver::GetInitialTime() const
//{
//    return minitialTime;
//}
//
//double AbstractOdeSolver::GetFinalTime() const
//{
//    return mfinalTime;
//}
//
//double AbstractOdeSolver::GetInitialValue() const
//{
//    return minitialValue;
//}
//
//// Write the class methods for the Forward Euler Solver
//
//#include "ForwardEulerSolver.hpp"
//
//// Write the function to set the right hand side of the function to be solved. Requires the use of function pointers. Declare a function pointer *p_function.
//
//double ForwardEulerSolver::RightHandSide(double t, double y)
//{
//    return 1+t;
//}
//
//
//double ForwardEulerSolver::SolveEquation()
//{
//    // Set some temporary variables
//    
//    double yi=0.0;
//    double yi_1;
//    double ti_1;
//    
//    // Access all the set private members
//    
//    int N=(GetFinalTime()-GetInitialTime())/GetStepSize();
//    double h=GetStepSize();
//    
//    // Initialise the y0 and t0 values
//    
//    yi_1 = GetInitialValue();
//    ti_1 = GetInitialTime();
//    
//    // Forward Euler update
//    
//    for (int i=0;i<N; i++)
//    {
//        yi=yi_1 + h*RightHandSide(ti_1,yi_1);
//        ti_1=GetInitialTime() + i*h;
//        yi_1=yi;
//    }
//    
//    // Return the final result
//    
//    return yi;
//}
//
//
//#include "RungeKuttaSolver.hpp"
//
//double RungeKuttaSolver::RightHandSide(double t, double y)
//{
//    return 1+t;
//}
//
//
//double RungeKuttaSolver::SolveEquation()
//{
//    // Set some temporary variables
//    
//    double yi=0.0;
//    double yi_1;
//    double ti_1;
//    double k1=0.0;
//    double k2=0.0;
//    double k3=0.0;
//    double k4=0.0;
//    
//    // Access all the set private members
//    
//    int N=(GetFinalTime()-GetInitialTime())/GetStepSize();
//    double h=GetStepSize();
//    
//    // Initialise the y0 and t0 values
//    
//    yi_1 = GetInitialValue();
//    ti_1 = GetInitialTime();
//    
//    // Forward Euler update
//    
//    for (int i=0;i<N; i++)
//    {
//        k1=h*RightHandSide(ti_1,yi_1);
//        k2=h*RightHandSide(ti_1+(1.0/2.0)*h,yi_1+(1.0/2.0)*k1);
//        k3=h*RightHandSide(ti_1+(1.0/2.0)*h,yi_1+(1.0/2.0)*k2);
//        k4=h*RightHandSide(ti_1+h,yi_1+k3);
//        yi=yi_1 + (1.0/6.0)*(k1+2*k2+2*k3+k4);
//        ti_1=GetInitialTime() + i*h;
//        //std::cout << "The yi th value " << yi << "\n";
//        yi_1=yi;
//    }
//    
//    // Return the final result
//    
//    return yi;
//}
//
//
//
//int main(int argc, char* argv[])
//{
//    
//    // Create an instance of the class
//    
//    ForwardEulerSolver test_func_fes;
//    RungeKuttaSolver test_func_rgs;
//    
//    // Set the elements for the problem
//    
//    test_func_fes.SetStepSize(0.05);
//    test_func_fes.SetInitialValue(2.0);
//    test_func_fes.SetTimeInterval(0.0,1.0);
//    
//    test_func_rgs.SetStepSize(0.05);
//    test_func_rgs.SetInitialValue(2.0);
//    test_func_rgs.SetTimeInterval(0.0,1.0);
//    
//    // Solve the differential system
//    
//    std::cout << "Solution is " << test_func_fes.SolveEquation() << "\n";
//    std::cout << "Solution is " << test_func_rgs.SolveEquation() << "\n";
//}




// Section 7.8.2 - Excercise 2
// ---------------------------

// Investigate the proper use of the virtual keyword and into the safe ways of making abstract classes. There is an abstract class AbstractPerson, and two derived classes Mother and Daughter. The code in the main function demostrate the power of polymorphic inheritance. It shows that it is possible to have a variety of objects of the same family stored as pointers to a generic abstract type, each of which could be a different concrete class. The AbstractPerson class promises a Print method but it is only at run-time that the system inspects the class pointed to by p_mother and works ou which Print method to invoke.

    // The preffered method of making an abstract class with a pure virtual method is to give no implementation of that method in the class. Done with the second line in the AbstractPerson class

//class AbstractPerson
//{
//public:
//    virtual void Print() = 0;
//};
//
//class Mother : public AbstractPerson
//{
//public:
//     void Print(){std::cout<<"Mother\n";}
//};
//
//class Daughter : public Mother
//{
//public:
//      void Print(){std::cout << "Daughter\n";}
//};
//
//int main(int argc, char* argv[])
//{
//    AbstractPerson* p_abstract = new AbstractPerson;
//    AbstractPerson* p_mother = new Mother;
//    AbstractPerson* p_daughter = new Daughter;
//    p_abstract->Print();
//    p_mother->Print();
//    p_daughter->Print();
//    delete p_mother;
//    delete p_daughter;
//    delete p_abstract;
//}








// Going to develop classes to describe the students at a university
// 1. Write a class of students that have the following public memebers
// - a string for the student's name
// - a double precision variable that store the library fines owed by the student
// - a double precision floating point variable the stores the tuition fees
// - a method that return the total money owed by the student, that is the sum of the
// - library fines and tuition fees associated with a given student
// - a few constructors that take different arguments

////void ComplexNumber::SetConjugate()
////{
////    mImaginaryPart=-mImaginaryPart;
////}
//
//#include "UniStudent.hpp"
//
//// Overide default construtor and set the fines and fees to zero
//
//UniStudent::UniStudent()
//{
//    mlibraryFines = 0.0;
//    tuitionFees = 0.0;
//}
//
//
//// Overide default construtor and set the fines and fees to zero
//
//UniStudent::UniStudent(double x, double y)
//{
//    mlibraryFines = x;
//    tuitionFees = y;
//}
//
//#include "GraduateStudent.hpp"
//
//// Overide the default constructor to set the tuition fees of the graduate students =0
//
//GraduateStudent::GraduateStudent(double x, double y)
//{
//    SetLibraryFines(x);
//    tuitionFees = 0;
//}
//
//// Overide the default constructor to set the tuition fees of the graduate students
//
////double GraduateStudent::CalculateGraduateMoneyOwing(double y, double t)
////{
////    double money_owing;
////    money_owing = y + t;
////    return money_owing;
////}
//
//
//// Method to set the private member mlibraryFines
//
//void UniStudent::SetLibraryFines(double h)
//{
//    if (h>=0)
//    {
//    mlibraryFines = h;
//    }
//    else
//    {
//        std::cout << "Whump Whump Whump Whow ... library fines must be a value greater than 0" << "\n";
//    }
//}
//
//
//// Method to retrieve private member mlibraryFines
//
//double UniStudent::GetLibraryFines() const
//{
//    return mlibraryFines;
//}
//
//
//// Method to calculate the money owing by the student
//
//double UniStudent::CalculateTotalMoneyOwing()
//{
//    double money_owing;
//    money_owing= mlibraryFines + tuitionFees;
//    return money_owing;
//}
//
//double GraduateStudent::CalculateTotalMoneyOwing()
//{
//    double money_owing;
//    money_owing= GetLibraryFines()+ 0; // Because graduate students don't pay fees
//    return money_owing;
//}
//
//
//// Some code to use the class of students
//
//int main(int argc, char* argv[])
//{
//    UniStudent* p_us1 = new UniStudent;
//    UniStudent* p_us2 = new UniStudent;
//    // UniStudent* p_us3 = new GraduateStudent;
//    GraduateStudent p_us8(6540, 19);
//    p_us1->SetLibraryFines(90);
//    p_us1->tuitionFees=85;
//    //p_us3->SetLibraryFines(5);
//    //std::cout << "Library fines for individual 1 " << p_us3->tuitionFees <<  "\n";
//    std::cout << "Tuition fees for graduate student " << p_us8.tuitionFees <<  "\n";
//    std::cout << "Tuition fees for graduate student " << p_us8.CalculateTotalMoneyOwing() <<  "\n";
//    std::cout << "Tuition fees for graduate student " << p_us1->CalculateTotalMoneyOwing() <<  "\n";
//
//    
//    delete p_us1;
//    delete p_us2;
//    // delete p_us3;
//}

// Section 7.7 - Tips:Using a Debugger
// -----------------------------------

// Breakpoints are places where you wish to temporarily pause execution
// Maybe I can learn how to use the debugger in Xcode but that will most likely come with time


// Section 7.6 - The Abstract class pattern
// ----------------------------------------

// Suppose we wanted to write an object orientated program for calculating the numerical solution of initial value ordinary differential equations of the form

// dy/dt=f(t,y), given y(T0)=Y0

// wher f(t,y) is a given function and T0 Y0 are given values. Many methods exists for solving these equations like the forward Euler method, Heun's method, various Runge-Kutta methods, and various multistep methods. One way of implementing these numerical methods would be to wriate a class called AbstractOdeSolver that has members that would be used by all of these numerical methods, such as variables representing the stepsize and intial conditions, a method that represents the function f(t,y) and a virtual method SolveEquation for implementing on of the numerical techniques described above. We would then implement each oth the numerical methods using a class derived from AbstractOdeSolver, and overriding the virtual function SolveEquation. The derived class would then contain members that allows a specific numerical algorithm to be implemented, as well as the members of the base class AbstractOdeSolver that would be required by all the numerical solvers.

// Using the class structure described above, the base class AbstractOdeSolver would not actually include a numerical method for calculating a numerical solution of a differential equation, and so we would not want to ever create an instance of this class. We can automatically enforce this by making Abstract-OdeSolver an abstract class.  This is implemented bu setting the cirtual functions SolveEquation and RightHandSide to be pure virtual functions. We indicate that these functions are pure virtual functions by completing the declaration of these members with '=0' as shown in the lisitng below. 


// A class is an abstract class if it contains one or more pure virtual methods.


// Section 7.5 - Run-time polymorphism
// -----------------------------------

// Polymorphism may be used when a number of classes are derived from the base class, and for some of these derived classes we want to override one or more—of the methods of the base class.

// Suppose we have developed a class of guests who stay at a hotel. This class will include members such as name, room type, arrival date, number of nights booked, and a member method that computes the total bill. It is likely that the hotel has negotiated special nightly rates for individuals from par- ticular organisations. To reflect this, the method that computes the total bill must act differently on guests from these organisations.

// This may be incorporated into soft- ware in a very elegant manner through the use of virtual methods where the method does different things for different derived classes. This is implemented by the use of the virtual keyword, shown in the header file for the class of hotel guests shown below.

// The virtual keyword is a signal to the compiler that a method has the potential to be overidden by a derived class

#include "Guest.hpp"

double Guest::CalculateBill()
{
    return telephoneBill + ((double)(numberOfNights))*50.0;
}

// Suppose now that the hotel have negotiated a deal with a company that reduces the room rate to £45 for the first night that a guest stays, and £40 for subsequent nights, and offers free telephone calls. This may be implemented by deriving a class SpecialGuest from the class Guest as shown below.

#include "SpecialGuest.hpp"

double SpecialGuest::CalculateBill()
{
    return 45.0 + ((double)(numberOfNights-1))*40.0;
}

// Note that declaring the member method CalculateBill as virtual in the class Guest does not require that the method must be overridden (redefined) in derived classes: it simply gives us the option to override it.

// The real power of run-time polymorphism can be seen when we use only pointers to the base class in a family tree of objects. It might not be obvious what the exact type of each object in our program is, but the run-time system is able to find out. In the following code, there are three pointers to Guest objects, but one of them is in actuality a SpecialGuest and therefore has a reduced bill. One might imagine a larger-scale program running over an array of Guest pointers—representing those guests who are checking out—each of which has their own mechanism for calcu- lating the bill. The programmer does not need to be aware which of these Guest

//int main(int argc, char* argv[])
//{
//    Guest* p_gu1 = new Guest;
//    Guest* p_gu2 = new Guest;
//    Guest* p_gu3 = new SpecialGuest;
//    
//    //Set the three guests identically
//    p_gu1->numberOfNights = 3;
//    p_gu1->telephoneBill = 0.00;
//    p_gu2->numberOfNights = 3;
//    p_gu2->telephoneBill = 0.00;
//    p_gu3->numberOfNights = 3;
//    p_gu3->telephoneBill = 0.00;
//    std::cout <<"BillforGuest1=" << p_gu1->CalculateBill() <<  "\n";
//    std::cout <<"BillforGuest2=" << p_gu2->CalculateBill() << "\n";
//    std::cout << "Smaller bill for Guest 3 = " << p_gu3->CalculateBill() << "\n";
//    
//    delete p_gu1;
//    delete p_gu2;
//    delete p_gu3;
//}


// Section 7.4 - Classes derived from derived classes
// --------------------------------------------------

// If Class2 is derived from Class1, we may derive a new class Class3 from Class2 in exactly the same way as in Sect. 7.2, as shown in the header file for Class3 shown below.

// 



// Section 7.2 - A class of e-books derived from a class of books
// --------------------------------------------------------------


//#include "Ebook.hpp"
//
//int main(int argc, char* argv[])
//{
//    Ebook holiday_reading;
//    holiday_reading.title = "The skull beneath the skin";
//    holiday_reading.author= "P D James";
//    std::cout << "The author is " << holiday_reading.author << "\n";
//    std::cout << "The title is " << holiday_reading.title << "\n";
//    std::cout << "The format is " << holiday_reading.format << "\n";
//    
//    holiday_reading.SetYearOfPublication(1982);
//    std::cout << "Year of publication is " << holiday_reading.GetYearOfPublication() << "\n";
//    holiday_reading.hiddenUrl = "http://ebook.example.com/example-book";
//    std::cout <<" The URL is " << holiday_reading.hiddenUrl << "\n";
//    
//    return 0;
//}

//Ebook::Ebook() : Book()
//{
//    format = "electronic";
//}
// The class Ebook will have the same members as the class Book, but with two differences. The first difference is that the class member format will be set to “electronic”. The second difference is that instances of the class Ebook will have an additional class member hiddenUrl that contains the private URL. The header file for this class is given below.

// As the class Ebook is derived from the class Book, we include the header file for the class Book in the header file for the class Ebook below.

// public members o fBook are public members of Ebook;
// protected members of Book are protected members of Ebook;and
// private members of Book are hidden from Ebook, and so may not be used by
// the derived class.

// This is known as public inheritance. 

// Object-orientated programming allowed for more reliable programming
// paradigm with one reason for this being inheritance. Inheritance allows
// us to extend the functionality of a class by introducing a new class
// known as the derived class, which containes all the features of the
// original class known as the base class.

// Private members of Book are not available to Ebook. However, we can still access them via the public methods of the SetYearOfPublication etc,

// Section 7.1 - Inheritance, Extensibility and Polymorphism
// ---------------------------------------------------------


// The most important feature of object-orientated programming is inheritance.
// This allows for functionality of classes to be built into a family tree.
// The data operation and functionlity of a given class may be directly resused
// extended and modified in another class the derived class.

// Suppose we have written a class that allows us to solve linear systems.
// Suppose further that we now want to write a class for solving linear systems that may be used only when the matrix in the linear system is symmetric and positive definite, thus allowing us to solve the system using the very effective conjugate gradient technique discussed in Sect. A.2.3.

// Much of the functionality required—such as specifying the vectors, matrix and tolerance, and providing a function for calculating the scalar product between two vectors—will already be implemented in the class that has been written to solve more general linear systems.


//  Inheritance allows us to write a new class for solving a special category of linear systems that uses or inherits all the features of the class for solving
// general linear systems. If we wanted to extend the functionality of the class that uses the conjugate gradient scheme to include Successive Over–Relaxation (SOR),2 we simply inherit again so that the SOR variant is a grandchild derived class of the original.

// Inheritance gives rise to two important concepts first mentioned in Sect. 1.1.1: extensibility and polymorphism. Extensibility is the idea, not just that the code can be extended, but that it can be extended easily, and without changing any of the original functional behaviour of the base class. Polymorphism is the ability to perform the same operations on a wide variety of different types of objects. This method of the base class is then redefined in a derived class for symmetric, positive definite matrices, without changing its arguments. At run- time, the program is able to decide which object it has and therefore which type of Solve to run. This type of polymorphism is also known as dynamic polymorphism or run-time polymorphism.



/************************************************************************
 ************************************************************************
 **                                                                    **
 **                  Chapter 6 - Classes                               **
 **                                                                    **
 ************************************************************************
 ************************************************************************/

#include "TwoByTwo.hpp"

TwoByTwo::TwoByTwo(const TwoByTwo& otherTwoByTwo)
{
    mNumRows = otherTwoByTwo.mNumRows;
    mNumCols = otherTwoByTwo.mNumCols;
    mData = new double* [mNumRows];
    for (int i=0; i<mNumRows; i++)
    {
        mData[i] = new double [mNumCols];
    }
    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; j<mNumCols; j++)
        {
            mData[i][j] = otherTwoByTwo.mData[i][j];
        }
    }
}

// Section 6.7 - Excercises

// Ex 6.2 - Develop a class of 2x2 matrices

// Ex. 6.1.7 - Write code to dynamically allocate memory for a 3x3 matrix of complex numbers.

// Constructor for vector of a given length
// Allocates memory, and initialises entries
// to zero

//int main(int argc, char* argv[])
//{
//    // Dynamically allocate memory for a 3x3 matrix of complex numbers
//    
//    int num_rows=3;
//    int num_cols=3;
//    ComplexNumber** complex_matrix;
//    complex_matrix = new ComplexNumber* [num_rows];
//    for (int i=0; i<num_rows; i++)
//    {
//        complex_matrix[i] = new ComplexNumber [num_cols];
//    }
//    
//    // Allocate complex numbers to the matrix
//    
//    ComplexNumber z1(0.0, 0.0);
//    ComplexNumber z2(4.0, 31.0);
//    ComplexNumber z3(7.0, 32.0);
//    ComplexNumber z4(4.0, 38.0);
//    ComplexNumber z5(9.0, 31.0);
//    ComplexNumber z6(4.0, 32.0);
//    ComplexNumber z7(2.0, 2.0);
//    ComplexNumber z8(4.0, 9.0);
//    ComplexNumber z9(12.0, 9.0);
//    complex_matrix[0][0]= z1;
//    complex_matrix[0][1]= z2;
//    complex_matrix[0][2]= z3;
//    complex_matrix[1][0]= z4;
//    complex_matrix[1][1]= z5;
//    complex_matrix[1][2]= z6;
//    complex_matrix[2][0]= z7;
//    complex_matrix[2][1]= z8;
//    complex_matrix[2][2]= z9;
//    
//    
//    std::cout << "first element of the complex matrix " << complex_matrix[0][0] << "\t" << complex_matrix[0][1]<< "\t"  << complex_matrix[0][2] << "\n";
//    
//    int big_n=10e-5;
//    for (int n; n<big_n; n++)
//    {
//        for (int i; i<num_rows; i++)
//        {
//            for (int j; j<num_cols; j++)
//            {
//                complex_matrix[i][j]= complex_matrix[i][j]+complex_matrix[i][j].CalculatePower(n);
//            }
//        }
//    }
//    
//    for (int i; i<num_rows; i++)
//    {
//        for (int j; j<num_cols; j++)
//        {
//            complex_matrix[i][j]= complex_matrix[i][j]/big_n;
//        }
//    }
//    
//    std::cout << "first element of the exp complex matrix " << complex_matrix[0][0] << "\t" << complex_matrix[0][1]<< "\t"  << complex_matrix[0][2] << "\n";
//
//for (int i=0; i<num_rows; i++)
//{
//    delete[] complex_matrix[i]; //Deletes the columns
//}

//    return 0;
//
//}

//// Code to overload the division operator for complex numbers
//
//ComplexNumber ComplexNumber::operator/(int n) const
//{
//    ComplexNumber w;
//    w.mRealPart = mRealPart/n;
//    w.mImaginaryPart = mImaginaryPart/n;
//    return w;
//}
//
//
//// Ex. 6.1.6 - Extend the class to include a method called CalculateConjugate which returns the complex conjugate if a complex number x + iy
//
//void ComplexNumber::SetConjugate()
//{
//    mImaginaryPart=-mImaginaryPart;
//}
//
//// Ex. 6.1.5 - Extend the class to include a method called SetConjugate which has a
//// void return type and sets the complex number x+iy to its complex conjugate x-iy
//
//
//
//
//ComplexNumber ComplexNumber::CalculateConjugate() const
//{
//    ComplexNumber q(mRealPart, -mImaginaryPart);
//    return q;
//}
//
//
//
//
//// Ex. 6.1.4 - Extend the class to include a constructor that allows us to specify a real number in complex form through a constructor that accepts one double precision floating point varaible as input, sets the real part of the complex number to the input varaible and the imaginary part to 0
//
//// Constructor to just set the real part of a complex number
//
//ComplexNumber::ComplexNumber(double x)
//{
//    mRealPart=x;
//    mImaginaryPart=0.0;
//}
//
//
//// Ex. 6.1.3 - Extend the class to include an overidden copy instructor
//
//ComplexNumber::ComplexNumber(const ComplexNumber& anotherComplexNumber)
//{
//    mRealPart=anotherComplexNumber.GetRealPart();
//    mImaginaryPart=anotherComplexNumber.GetImaginaryPart();
//}

// Ex. 6.1.1 - Extend the class of complex numbers to include methods that allow us
// to access the corresponding private members. Call them GetRealPart and GetImaginaryPart

// Ex. 6.1.2 - Write friend functions to do the same thing as in Ex. 6.1.1 .


//int main(int argc, char* argv[])
//{
//    ComplexNumber z1(4.0, 3.0);
//    std::cout << "real part of z1 " << z1.GetRealPart() << "\n";
//    
//    // Try for my other constructor for allocating just the real part
//    
//    ComplexNumber zreal(3.0);
//    std::cout << "real part of zreal " << zreal.GetRealPart() << "\n";
//    std::cout << "imaginary part of zreal " << zreal.GetImaginaryPart() << "\n";
//    
//    // Try my complex conjugate function
//    
//    ComplexNumber z12(4.0, 3.0);
//    std::cout << "complex number z12 " << z12 << "\n";
//    std::cout << "complex conjugate of z12 " << z12.CalculateConjugate() << "\n";
//    
//    
//    std::cout << "z1= " << z1 << "\n";
//    std::cout << "Modulus z1=" << z1.CalculateModulus() << "\n";
//    std::cout << "Argument z1=" << z1.CalculateArgument() << "\n";
//    
//    ComplexNumber z2;
//    z2 = z1.CalculatePower(3);
//    std::cout << "z2 = z1*z1*z1=" << z2 << "\n";
//    
//    ComplexNumber z3;
//    z3 =-z2;
//    std::cout << "z3 = -z2" << z3 << "\n";
//    
//    ComplexNumber z4;
//    z4 =z1+z2;
//    std::cout << "z1 + z2 = " << z4 << "\n";
//    std::cout << "real part of z4 " << GetRealPart(z4) << "\n";
//    std::cout << "imaginary part of z4 " << GetImaginaryPart(z4) << "\n";
//    ComplexNumber zs[2];
//    zs[0]=z1;
//    zs[1]=z2;
//    std::cout << "Second element of zs = " << zs[1] << "\n";
//    
//    return 0;
//    
//}
//
//double GetRealPart(const ComplexNumber& complexNum)
//{
//    return complexNum.mRealPart;
//}
//
//double GetImaginaryPart(const ComplexNumber& complexNum)
//{
//    return complexNum.mImaginaryPart;
//}
//
//double ComplexNumber::GetRealPart() const
//{
//    return mRealPart;
//}
//
//double ComplexNumber::GetImaginaryPart() const
//{
//    return mImaginaryPart;
//}




// Tips: Coding to a standard
// --------------------------

// A famous C++ coding style called joinst strike fights was drafter for a European
// aviation project and has now been adopted by many commercial software houses.
// Some organisations use automatic checks to ensure that their code complies to
// to the standard, while others use the standard as a guidline.

// A few simple coding rules make programs much more readable.

// 1. Code within blocks is indented. The curly brackets are always used, even in
// single statement blocks and appear on a line of their own.

// if (p>q)
// {
//      Statement 1;
//      Statement 2;
// }

// 2. Lines of code which are too long to fit within the width of the editor are
// split split across multiple lines with a suitable indentation

// 3. Names for variables and functions are meaningful but are not so verbose that
// they become unwieldy.

// 4. Variables are declared close to where they are used, rather than at the beginn
// ing of a function. Loop counter variables are declared in the contect of the loop

// 5. Locally declared varibale names have undescores

// 6. Where types are pointers or references the characters are written adjacent to the native type with no space between i.e., int* i

// 7. Pointer names begin with 'p' with the exception that when the pointer is used for an array of values stored in dynamically allocated memory

// 8. Function names are in camel-case and the first word is a verb to indicate what
// it is that they do. This applies to class methods as well as to regular functions

// 9. Names of arguments to functions and class methods are also in camel-case but they begin in lower-case 'firstDimension'. The same format is also applied to member data of classes, but the following rule helps us to distinguish them.

// 10. Class data which have access controls are also in camel-case with m for 'my' to denote 'private' or 'protected' mSize or 'mpQuadraticMesh' for private pointer. This allows us to distinguish in the body of a class method between the method arguments and the class variables.

// 11. Class names are also in camel-case and are distinguished by the context

// 12. There should be lots of descriptive comments


// Some additional remarks on operator overloading
// -----------------------------------------------

// Many more operators can be overloaded.





// Key revision of classes
// -----------------------

// The 'protected' class are accessible to other class members to derived classes and to friends

// Classes allow modularity, which includes placing similar functionality in a few files. Classes allow us to go further than this: access controls allow us to control which resources are available outside of the class, and which are hidden from users.

// The variables/data and functions associated with a class are known as class members, and the functions more specifically as methods.

// Section 6.4.2 - The class of complex numbers
// --------------------------------------------




// Section 6.4 - A second example Class: A class of Complex Numbers
// ----------------------------------------------------------------

// Develop a class of complex numbers, allowing some more advanced features of classes
// operator overloading. A class of complex numbers will therefore contain class members that represent both of these quantities.


// #include "ComplexNumber.hpp"

// Override default constructor
// Set real and imaginary parts to zero

ComplexNumber::ComplexNumber()
{
    mRealPart=0.0;
    mImaginaryPart=0.0;
}

// Overrides the automatically generated default constructor and initialises both the real part and the imaginary part of the complex number to zero if no values are specified

// Constructor that set complex number z=x+iy. Accepts two double precision floating point variables, sets the real part of the complex number to the first of these, and the imaginary part of the complex number to the second of these.

ComplexNumber::ComplexNumber(double x, double y)
{
    mRealPart=x;
    mImaginaryPart=y;
}


// Copy constructor

ComplexNumber::ComplexNumber(const ComplexNumber& anotherComplexNumber)
{
    mRealPart=anotherComplexNumber.GetRealPart();
    mImaginaryPart=anotherComplexNumber.GetImaginaryPart();
}

// Methods to get real and imaginary parts from the private valriables

double ComplexNumber::GetRealPart() const
{
    return mRealPart;
}

double ComplexNumber::GetImaginaryPart() const
{
    return mImaginaryPart;
}


// Method for computing the modulus of a complex number

double ComplexNumber::CalculateModulus() const // Indicates that it is a member of the class ComplexNumber and two the method is calls CalculateModulus. The text () indicates that no arguments are required. Member methods can access all class members and so there is no need to specify either the real of imag part of the complex numberin the list of arguments. Conclude with const to ensure that both the real and imag part of the CN are left unchanged by this method
{
    return sqrt(mRealPart*mRealPart+mImaginaryPart*mImaginaryPart);
}

// Method for computing the argument of a complex number. Use similar arguments to calculate the argument of a complex number,

double ComplexNumber::CalculateArgument() const
{
    return atan2(mImaginaryPart, mRealPart);
}

// Method for raising complex numbers to the power of n using De Moivre's theorem
// - first complex numbers must be converted to polar form. The header specifies that the variable returned is of type ComplexNumber: that is methods can be used to return an instance of a class as well as simpler variables types such as double. The method also requires the argument of the exponent to which we raise the complex number: this is specified by double n.

ComplexNumber ComplexNumber::CalculatePower(double n) const
{
    double modulus = CalculateModulus(); // Calling the methods from the class
    double argument = CalculateArgument();
    double mod_of_result = pow(modulus,n);
    double arg_of_result = argument*n;
    double real_part = mod_of_result*cos(arg_of_result);
    double imag_part = mod_of_result*sin(arg_of_result);
    ComplexNumber z(real_part, imag_part);
    return z ;
}

// Overloading the = (assignment) operator. The argument to the assignment operator is a reference to another instance of the class, rather than the object itself. All method arguments are called by copy, necessitating the overhead of the use of the copy constructor in making the assignment. The use of const guarantees that the assignment operator will not alter the object argument z. The remainder of the method for assignment used an entity called this which does not appear to have to be declared. The word this is a pointer to the complex number that is returned: it is the contents of this which is returned.

ComplexNumber& ComplexNumber:: operator=(const ComplexNumber& z)
{
    mRealPart = z.mRealPart;
    mImaginaryPart = z.mImaginaryPart;
    return *this;
}

// Overloading the unary -  operator. Explains that the return type is a ComplexNumber and the method is a member of the class ComplexNumber, defines the operator -, the function requires no input arguments by () and the original complex number is left unchanged through const. An instance of the class CompledNumber, called w, is then decalred and the real and imaginary part of w are set to the negative of those of the original complex number and returned.

ComplexNumber ComplexNumber::operator-() const
{
    ComplexNumber w;
    w.mRealPart = -mRealPart;
    w.mImaginaryPart = -mImaginaryPart;
    return w;
}

// Overloading the binary +  operator. Begin by specifying the return type, the class that the function is a member of, the operator and the input argument. There is only one input argument, which is the + operator. We declare an instance of a complex number perform the addition and then return the result of this addition. A simular function overloads the binary subtraction operator.

ComplexNumber ComplexNumber::operator+( const ComplexNumber& z) const
{
    ComplexNumber w;
    w.mRealPart = mRealPart+z.mRealPart;
    w.mImaginaryPart = mImaginaryPart+z.mImaginaryPart;
    return w;
}

// Overloading the binary -  operator

ComplexNumber ComplexNumber::operator-( const ComplexNumber& z) const
{
    ComplexNumber w;
    w.mRealPart = mRealPart-z.mRealPart;
    w.mImaginaryPart = mImaginaryPart-z.mImaginaryPart;
    return w;
}


// Overloading the insertion <<  operator. This is the output stream << insertion operator. The operator is not a member method of the class but is an external fuction. This operator used the friend keyword for the operator << of the header for complex numbers, this operator may access all class members including private members. The function defining this operator takes an output stream and inserts characters into it using the complex number z. 

std::ostream& operator<<(std::ostream& output,const ComplexNumber& z)
{
    // Format as "(a + bi)" or as "(a - bi)"
    output << "(" << z.mRealPart << " " ;
    if (z.mImaginaryPart >= 0.0)
    {
    output << "+ " << z.mImaginaryPart << "i)";
    } else
    {
        output << "- " << -z.mImaginaryPart << "i)";
    };
 
    return output;
}


// The following code makes use of the class. When member methods are called that require no arguments we still need to acknowledge that are functions by using empty brackets for example z1.CalculateModulus(). We can decalre an arrya of complex numbers where we create an array of complex number with two entries. By setting the first element of this array to the complex number z2. Show how to access a friend function of an entry of an array, through printing the complex number that is the second entry if the array of complex numbers ot the screen.


//int main(int argc, char* argv[])
//{
//    ComplexNumber z1(4.0, 3.0);
//
//    std::cout << "z1= " << z1 << "\n";
//    std::cout << "Modulus z1=" << z1.CalculateModulus() << "\n";
//    std::cout << "Argument z1=" << z1.CalculateArgument() << "\n";
//    
//    ComplexNumber z2;
//    z2 = z1.CalculatePower(3);
//    std::cout << "z2 = z1*z1*z1=" << z2 << "\n";
//    
//    ComplexNumber z3;
//    z3 =-z2;
//    std::cout << "z3 = -z2" << z3 << "\n";
//    
//    ComplexNumber z4;
//    z4 =z1+z2;
//    std::cout << "z1 + z2 = " << z4 << "\n";
//    
//    ComplexNumber zs[2];
//    zs[0]=z1;
//    zs[1]=z2;
//    std::cout << "Second element of zs = " << zs[1] << "\n";
//    
//    return 0;
//    
//}
//







// Section 6.3 - The friend keyword
// --------------------------------

// When developing a program we may wish to access private members of a class from outside the class. Create a new public method that accesses the private member. Can write a free function that is a 'friend' of the class: such functions may access all members of the class including private variables. 

//#include "ExampleClass.hpp"
//
//// Constructor to set private members
//
//ExampleClass::ExampleClass(double member1, double member2)
//{
//    mMemberVariable1=member1;
//    mMemberVariable2=member2;
//}
//
//// GetMinimum is a member method
//
//double ExampleClass::GetMinimum() const
//{
//    if (mMemberVariable1 < mMemberVariable2)
//    {
//        return mMemberVariable1;
//    }
//    else
//    {
//        // mMemberVariable1 >= mMemberVariable2
//        return mMemberVariable2;
//    }
//}
//
//// GetMaximum is a friend function
//
//double GetMaximum(const ExampleClass& egClass)
//{
//    if (egClass.mMemberVariable1> egClass.mMemberVariable2)
//    {
//        return egClass.mMemberVariable1;
//    }
//    else
//    {
//        // egClass.Var1 <= egClass.Var2
//        return egClass.mMemberVariable2;
//    }
//}
//
//int main(int argc, char* argv[])
//{
//    ExampleClass example(2.0, 3.0);
//    std::cout << "Minimum value = " << example.GetMinimum() << "\n";
//    std::cout << "Maximum value = " << GetMaximum(example) << "\n";
//    return 0;
//
//
//}
//







// One can declare a pointer to an instance of a class. Seems like another way to control the memory of the items in a class.

//#include "Book.hpp"
//
//int main(int argc, char* argv[])
//{
//    Book* p_book_i_am_reading = new Book;
//
//    (*p_book_i_am_reading).author = "Philip Pulman"; // Denote the contents of the memory whose address is stored by the pointer. Brackets allow us to access the class members
//    p_book_i_am_reading->title = "Lyra's Oxford"; // More convenient way of accessing a class member associated with a pointer to a class in which the forward arrow means de-reference and then access the member.
//    
//    delete p_book_i_am_reading; // Every new must have a delete
//
//    return 0;
//
//
//}


// Section 6.2.7 - Constructores and Destructors
// -------------------------------------------

// Each time the class Book is created the program calls a functions that allocates space in memory for all the variables used. This is called a default constructor and is generated automatically.

// This can be overidden if desired. If any memort management such as allocating memeory dynamically is required by a class, then it is essential to change the behavior of the automatically generated default constructor: if not the default constructor will not allocate any memeory. We can change the behavior either by overriding is with a default constructor of our own or by providing some other constructor. The automatically generated default constructor is only available if no other constructors have been provided by the programmer.

// Another constructor that is auto generated is a copy constructor. This constrcutor requires as input another instance of the class, and creates a copy of this instance of the class.

// Additionally we may write our own customised constructor that takes any inputs we feel are appropriate and we may write as many of these as we like.

// Demostrare how to write a constructor and how to override a copy constructor.

// Firstly, we need an appropriate header file that declares an overridden copy constructor and and line 11 explaines that there will be a constructor that accepts a string as input.

// Lines 14-22 are the overridden copy constructor to create another instances of the class Book, called another_book, that is initialised with class members taking identical values to those of good read.

// Destructors are also automatically written and free memory allocated for an object when it goes out of scope. 

//#include "Book2.hpp"
//
//int main(int argc, char* argv[])
//{
//    Book2 good_read;
//    
//    good_read.author = "C S Lewis";
//    good_read.title = "The silver chair";
//    good_read.publisher = "Geoffrey Bles";
//    good_read.price = 699;
//    good_read.format = "paperback";
//    good_read.SetYearOfPublication(1953);
//    
//    Book2 another_book(good_read);
//    
//    Book2 an_extra_book("The Magician’s nephew");
//    
//    return 0;
//    
//    
//}
//
//// Overridden defualt constructor
//
//Book2::Book2()
//{
//    author= "unspecified";
//    title = "unspecified";
//    publisher = "unspecified";
//    format = "unspecified";
//}
//
//// Overidden copy constructor (mimics system version
//
//Book2::Book2(const Book2& otherBook)
//{
//    author = otherBook.author;
//    title = otherBook.title;
//    publisher = otherBook.publisher;
//    format = otherBook.format;
//    price = otherBook.price;
//    mYearOfPublication=otherBook.GetYearOfPublication();
//}
//
//
//// Specialised constructor
//
//Book2::Book2(std::string bookTitle)
//{
//    title = bookTitle;
//}
//
//
//void Book2::SetYearOfPublication(int year) // Doesn't return a variable associated with a class called Book and SetYearOfPublication and requires an integer input
//{
//    assert ((year > 1440) && (year < 2020)); // Check if it's within a reasonable year bracket
//    mYearOfPublication = year;
//}
//
//int Book2::GetYearOfPublication() const
//{
//    return mYearOfPublication;
//}

// Section 6.2.6 - Including Function Implementations in Header Files
// ------------------------------------------------------------------

// It may be more convenient to include the implementation of these functions in the
// header file. Implement the functions that are members of our class in the header file
// for this class thus combining the files



// Section 6.2.3 - Setting and Accessing Variables
// -----------------------------------------------

// In the class of books we developed in the previous section, all class members were variables, such as strings, double precision floating point numbers, or integers.  Classes are, however, much more powerful than this: we will now show how functions may also be defined as class members, known as class methods.

// Suppose we want to check that the year of publication of an instance of the class Book always takes a valid year. Assuming that no book in our catalogue was published before the invention of the printing press, and has already been published or will be in the near future, then we may write a function known as a member method, called SetYearOfPublication that allows us to set this variable and check that the integer value for year of publication falls within a sensible range (after the invention of the printing press and not too far in the future). As we are writing a method that allows us to check that a valid year of publication is assigned, it seems sensible to force the user of the class to use this method to set this variable. This may be implemented by setting the member yearOfPublication to be a private variable. Private variables may only be accessed by other class members: making yearOfPublication a private variable therefore prevents us from accessing this variable through code


// Now that have made yearOfPublication a private member, we cannot di- rectly access this member from outside the class.

//#include "Book.hpp"
//
//int main(int argc, char* argv[])
//{
//
//    Book promotion_book;
//    
//    promotion_book.author = "Iris Murdoch";
//    promotion_book.title = "The sea, the sea";
//    promotion_book.publisher = "Chatto & Windus";
//    promotion_book.price = 299;
//    promotion_book.format = "hardback";
//    promotion_book.SetYearOfPublication(1441);
//    
//    std::cout << "Year of publication of " << promotion_book.title << " is " << promotion_book.GetYearOfPublication() << "\n";
//    
//    // In the code above we need to acknowledge that the class member GetYearOfPublication is a function or method by including empty brackets after using this class method
//
//    // Using access privileges ensure that variables may only be set through a class memeber that provides a check on the accuracy of data
//}


//void Book::SetYearOfPublication(int year) // Doesn't return a variable associated with a class called Book and SetYearOfPublication and requires an integer input
//{
//    assert ((year > 1440) && (year < 2020)); // Check if it's within a reasonable year bracket
//    mYearOfPublication = year;
//}
//
//int Book::GetYearOfPublication() const
//{
//    return mYearOfPublication;
//}


// Section 6.2.2 - Header Files
// ----------------------------

// Don't include header files more than once. To avoid this code being included twice we adapt it so that the header file for a class called ExampleClass is of the form shown below.


// We therefore see that the #ifndef, #define and #endif statements may be used to ensure that the contents of a header file are not included more than once.


// Section 6.2 - A class of books
// ------------------------------


// Each book has the following attributes
    // author
    // title
    // format
    // price
    // year of publication
    // publisher

// These attributed can be associated with each instance of a book by first saving the file below as Book.hpp. These attributes are known as class members

// The file is known as a header file associated with the class: the extension .hpp indicates that this file is a header file associated with a C++ program. The word "public" allows us to access all variables associated with the class. There are more details with respect to class privileges. Need the semicolon

// When header files are included the names of these files are enclosed within quotation marks, in contrast to the system header files such as iosteam fstream etc that we have used earlier. This is done to disguish between local included files and those from external libraries

//#include "Book.hpp"
//
//int main(int argc, char* argv[])
//{
// 
//    Book my_favorite_book;
//    
//    my_favorite_book.author = "David Foster Wallace";
//    my_favorite_book.title = "Infinite Jest";
//    my_favorite_book.publisher = "Springer";
//    my_favorite_book.price = 10;
//    my_favorite_book.format = "Hardback";
//    my_favorite_book.yearOfPublication = 1999;
//    
//    std::cout << "Year of publication of " << my_favorite_book.title << " is " << my_favorite_book.yearOfPublication << "\n";
//    
//
//}

// The class of books written here allows us to associate data with each instance of the class. The class allows us to define a new data type on line 6 in this case called my favorite book. Pretty cool





// These problems could have been overcome if we could write a module that

// 1. Contains all the functions needed to solve the system
// 2. Does not allow these functions to be accessed by another part of the program
// except through the interface
// 3. Can not itself access any other part of the program
// 4. Also contains all the data needed to solve the system

// The variables data and functions associated with a class are known as class members and the function more specifically as methods.

// Classes allow modularity which includes placing similar functionality in a few files. Classes allow us to access controls, allow us to control which resources are available outside of the class, and which are hidden from users.

// The concept of abstraction is that the particulars of an idea should not be important. Classes allow us to hid the irrelevant details of functionality from users who need not know about them. For example, I do not need to know how a compiler translates a C++ code into a machine readable executable file, but only how to instruct the compiler to perform this task. Abstraction allows emphasis to be placed on the qualities or properties that characterise the objects in how they act and the type of information that they carry.

// A further property of classes is inheritance which allows easy code reuse, extensibility and polymorphism.



// Section 6.1.2 - Abstraction, Encapsulation and Modularity of Classes
// --------------------------------------------------------------------


// Section 6.1.1 - Problems that may arise when using modules
// --------------------------------------------------------

// Sometimes the modules can't be used as black boxes. In modules data is stored there is only ever one copy of a particular module and one copy of any data asociated with it

// Modules are useful for code reuse and allow for rapid code development
// Linear algebra lies at the heart of numerical analysis and so numerical
// analysts use linear solcers in many programs that they write.
// Many different linear algerba techniques for solving linear systems. It is possible
// to include

// Consider a linear solver that has is able to deal with singular matrices. Such a linear solver will need access to the null space of the singular matrix. If we use the linear solver to solve a linear system then the linear system will solve the linear system subject to known and storing the null space of this system. If we were to solce a nonsingular system ww would have to rememebr to specify the null space as empty or the linear solver would attempt to find the solution of the nonsingular system subject to the previously specified null space.

// Classes allow us to get around these problems.


// Section 6.1.0 - The Raison d'Etre for Classes - important reason or purpose
// -------------------------------------------------------------------------

// Modules are useful for code reuse and allow for rapid code development
// Linear algebra lies at the heart of numerical analysis and so numerical
// analysts use linear solcers in many programs that they write.
// Many different linear algerba techniques for solving linear systems. It is possible
// to include


/************************************************************************
 ************************************************************************
 **                                                                    **
 **                  Chapter 6 - Classes                               **
 **                                                                    **
 ************************************************************************
 ************************************************************************/










/************************************************************************
 ************************************************************************
 **                                                                    **
 **                    Section 5 Excercises                            **
 **                                                                    **
 ************************************************************************
 ************************************************************************/


// Use dynamic allocation of memory

// Functions prototypes for Section 5 excercises
// ---------------------------------------------

double** AllocateMatrixMemory(int numRows, int numCols);
void FreeMatrixMemory(int numRows, double** matrix);
void PrintInt(int* n);
void ChangeInt(int* n, int* k);
void ChangeDouble(double* x, double* y);
void ChangeDouble2(double& x, double& y);
double** Multiply(double** A, double** B, int nrowA, int ncolA, int nrowB, int ncolB);
void  MeanandStandardDeviation(double** x, int length, double& mean, double& stdev);
double** Multiply(double* x, double** A, int length, int ncolA, int nrowA);
double** Multiply(double** A, double** x, int ncolA, int nrowA, int length);
double p_norm(double* v, int length, int p);
double p_norm(double* v, int length);
double Determinant(double** A, int nrow, int ncol);
double** linear_solve(double** A, double** b, int nrow, int ncol, int length);
double** LinearSolve2(double** A, double** b, int nrow, int ncol, int length);




// Excercise 5.10
// -------------

// Write a module for solving a linear system b=Ac where A is nonsingular

//int main(int argc, char* argv[])
//{
//    // Variable declaration
//    
//    int nrow;
//    int ncol;
//    int length;
//    double** A;
//    double** b;
//    double** x;
//    
//    // Start with a small matrix
//    
//    nrow=4;
//    ncol=4;
//    length=4;
//    
//    // Allocate the memory
//    
//    A=AllocateMatrixMemory(nrow,ncol);
//    b=AllocateMatrixMemory(nrow,1);
//    x=AllocateMatrixMemory(nrow,1);
//    
//    // Enter the values of the A matrix
//    
//    A[0][0]=1; A[0][1]=9; A[0][2]=3; A[0][3]=4;
//    A[1][0]=-4; A[1][1]=5; A[1][2]=2; A[1][3]=7;
//    A[2][0]=6; A[2][1]=1; A[2][2]=-9; A[2][3]=3;
//    A[3][0]=4; A[3][1]=400; A[3][2]=5; A[3][3]=2;
//    
//    // Enter the values of the b vector
//    
//    b[0][0]=1; b[1][0]=9; b[2][0]=3; b[3][0]=64;
//    
//    // Print the result
//    
//    std::cout << Determinant( A, nrow, ncol)  << "\n";
//    
//    // linear_solve(A, b,  nrow, ncol, length);
//    
//    x= LinearSolve2(A, b,  nrow, ncol, length);
//    
//    for (int i=0; i<nrow; i++)
//    {
//        std::cout << x[i][0] << "\n";
//    }
//    
//    // Delete the allocated memory as it is good practice
//    
//    FreeMatrixMemory(nrow, A);
//    FreeMatrixMemory(length, b);
//}






// Function to recursively calculate the determinant of a matrix. We will try for a 2x2 and then step it up

double Determinant(double** A, int nrow, int ncol)
{
    double result=0;
    double** Atemp;
    
    // Print out some diagnostics
    
     std::cout << "ncol are " << ncol << "\n";
     std::cout << "\n";
    
    // Define the determinant of a 1*1 matrix
    if (ncol==1)
    {
        std::cout << "Front bit is " << A[0][0] << "\n";
        std::cout << "\n";
        return A[0][0];
        
    }
    else
    {
        // For matrices of size greater than size 1
        
        // The core of the method. Rests upon defining the correct indices so that a matrix of correct size can be allocated
        
        // The i index keeps track of the matrix size
        
        for (int i=0; i<ncol; i++)
        {
             std::cout << "i is " << i << "\n";
             std::cout << "\n";
             std::cout << "alt is " <<  pow(-1,i);
             std::cout << "\n";
            
            // Allocate the memory for the temporary matrix
            
            Atemp=AllocateMatrixMemory(nrow-1,ncol-1);
            
            // Cycle over the different elements of the matrix at each recursive loop so that we
            // miss the first row and column of interest
            
            for (int j=0; j<(nrow-1); j++)
            {
                for (int k=0; k<(ncol-1);k++)
                {
                    if (i==0)
                    {
                        std::cout << "row is " << j+1 << "\t";
                        std::cout << "col is " << k+1 << "\n";
                        std::cout << "\n";
                        Atemp[j][k]=A[j+1][k+1];
                        
                    }
                    else if (k==i&i!=0)
                    {
                        std::cout << "row is " << j+1 << "\t";
                        std::cout << "col is " << k+1 << "\n";
                        std::cout << "\n";
                        Atemp[j][k]=A[j+1][k+1];
                        
                    }
                    else if (k>i&i!=0)
                    {
                        std::cout << "row is " << j+1 << "\t";
                        std::cout << "col is " << k   << "\n";
                        std::cout << "\n";
                        Atemp[j][k]=A[j+1][k+1];
                    }
                    else
                    {
                        std::cout << "row is " << j+1 << "\t";
                        std::cout << "col is " << k   << "\n";
                        std::cout << "\n";
                        Atemp[j][k]=A[j+1][k];
                    }
                    
                    // std::cout << "Atemp[j][k] " << Atemp[j][k] << "\n";
                    // std::cout << "\n";
                }
                
            }
            
            // std::cout << "alternating part is" << pow(-1,i) << "\n";
            // std::cout << "part out the front is "<< A[0][i] << "\n";
            if (ncol==4)
            {
                std::cout << "Atemp is" << "\n" << Atemp[0][0] << "\t" << Atemp[0][1] << "\t" << Atemp[0][2] << "\n" <<  Atemp[1][0]<< "\t" ;
                std::cout << Atemp[1][1] << "\t"<< Atemp[1][2] << "\n" << Atemp[2][0] << "\t" << Atemp[2][1]<< "\t" << Atemp[2][2]<< "\n";
                std::cout << "\n";
                
            }
            else if (ncol==3)
            {
                std::cout << "Atemp is" << "\n" <<Atemp[0][0] << "\t" << Atemp[0][1] << "\n" <<  Atemp[1][0]<< "\t" << Atemp[1][1]<< "\n";
            }
            else
            {
                 std::cout << "Atemp is" << "\n" <<Atemp[0][0] << "\n";
                std::cout << "\n";
            }
            
            // The recursive component that makes the code work
            
            result += pow(-1,i)*A[0][i]*Determinant(Atemp,nrow-1,ncol-1);
            std::cout << "result at this round is " << result << "\n";
        }
    }
    return result;
}








// A function to solve the linear system of equations via Gaussian elimination no pivoting

double** LinearSolve2(double** A, double** b, int nrow, int ncol, int length)
{
    // Assign the variables
    
    double** Atemp;
    double** btemp;
    double** x;
    double** P;
    
    // Allocate the memory
    
    Atemp=AllocateMatrixMemory(nrow,ncol);
    btemp=AllocateMatrixMemory(length,1);
    P=AllocateMatrixMemory(nrow,ncol);
    x=AllocateMatrixMemory(length,1);
    
    //std::cout << "ncol is " << ncol << "\n";
    //std::cout << "nrow is " << nrow << "\n";
    
    // Insert a condition so that we have a determined system
    
    if (Determinant(A,nrow,ncol)==0)
    {
        std::cout << "Sorry your A matrix is singular" << "\n";
    } else
    {
        // If the matrix is not singular do the Gaussian elimination
        
        for (int k=0; k<ncol; k++)
        {
            // Include a pivoting step. We must first as for the absolute values of those diagonal elements that are below k and
            double max_diag=0;
            int max_k=0;
            for (int d=k; d<ncol; d++)
            {
                std::cout << "What iteration of k are we hitting " << k << "\n";
                if (fabs(A[d][d])>max_diag)
                {
                    max_diag=fabs(A[d][d]);
                    max_k=d;
                } else
                {
                    max_diag=max_diag;
                    max_k=d;
                }
                // std::cout << "The absolute value of the diagonal " << fabs(A[d][d]) << "\n";
                // std::cout << "The greatest diagonal value in this iteration is " << fabs(A[d][d]) << "\n";
                // std::cout << "The value of k is " << k << "\n";
                // std::cout << "The row of the greatest diag " << max_k << "\n";
                // std::cout << "\n";
            }
            
            // Build the P matrix to do the pivoting and multiply by A to get the pivoted matrix
            if (max_k>k)
            {
                for (int i=0; i<ncol; i++)
                {
                    for (int j=0; j<ncol; j++)
                    {
                        if (i==j & i!=k & j!=k & i!=max_k & j!=max_k)
                        {
                            P[i][j]=1;
                        } else if (i==k & j==max_k)
                        {
                            P[i][j]=1;
                        } else if (i==max_k & j==k)
                        {
                            P[i][j]=1;
                        } else
                        {
                            P[i][j]=0;
                        }
                        
                    }
                }
            } else {
                for (int i=0; i<ncol; i++)
                {
                    for (int j=0; j<ncol; j++)
                    {
                        if (i==j)
                        {
                            P[i][j]=1;
                        } else {
                            P[i][j]=0;
                        }
                        
                    }
                }

            }
            
            // Print out the results so we can see what is happening
            
            // P matrix
            
            for (int p=0; p<nrow; p++)
            {
                
                std::cout << "P i j is " << "\t" << P[p][0] << "\t" << P[p][1] << "\t" << P[p][2] << "\n";
            }
            
            // Multiply the P matrix with the A matrix to do the pivoting
            
            A=Multiply(P, A, nrow, ncol, nrow, ncol);
            b=Multiply(P, b, nrow, ncol, length);
            
            
            // Print the result of A so that the correct matrix has been stores
            
            for (int p=0; p<nrow; p++)
            {
                
                std::cout << "A i j is " << "\t" << A[p][0] << "\t" << A[p][1] << "\t" << A[p][2] << "\n";
            }
            
            // Print the result of the b vector after pivoting
            
            for (int i=0; i<nrow; i++)
            {
                
                // Print out the results so we can see what is happening
                std::cout << "b i j is " << b[i][0] << "\n";
            }
            
            
            // Build the kth elimination matrix
            
            for (int i=k+1; i<nrow; i++)
            {
                b[i][0]=b[i][0]-(A[i][k]/A[k][k])*b[k][0];
                for (int j=k+1; j<ncol; j++)
                {
                    A[i][j]=A[i][j]-(A[i][k]/A[k][k])*A[k][j];
                    
                    // Print out the results so we can see what is happening
                    // std::cout << "Atemp[i][j] is " << Atemp[i][j] << "\n";
                    //std::cout << "A[i][k] is " << A[i][k] << "\n";
                    //std::cout << "A[k][k] is " << A[k][k] << "\n";
                    //std::cout << "A[k][j] is " << A[k][j] << "\n";
                    //std::cout << "i is " << i << "\n";
                    //std::cout << "j is " << j << "\n";
                    //std::cout << "A i j is " << A[i][j] << "\n";
                }
            }
        }
        
        // Assign the 0 to the elements of the matrix that are below the diagonal. The above code only deals with the upper triangular matrix
        
        for (int zero_row=1; zero_row <ncol;zero_row++)
        {
            for (int zero_col=0; zero_col<zero_row; zero_col++)
            {
                //std::cout << "zero_row is " << zero_row << "\n";
                //std::cout << "zero_col is " << zero_col << "\n";
                A[zero_row][zero_col]=0;
            }
        }
        
        // Print out the results so we can see what is happening
        
        // A matrix
        
        for (int p=0; p<nrow; p++)
        {
            
            std::cout << "A i j is " << "\t" << A[p][0] << "\t" << A[p][1] << "\t" << A[p][2] << "\n";
        }
        
        // b vector
        
        for (int i=0; i<nrow; i++)
        {
            
            // Print out the results so we can see what is happening
            //std::cout << "b i j is " << b[i][0] << "\n";
        }
    }
    
    // Given the upper triangular matrix and the adjusted b vector calculate the elements of x
    
    for (int k=(ncol-2); k>-1; k--)
    {
        double sum_temp=0;
        x[ncol-1][0]=b[ncol-1][0]/A[ncol-1][ncol-1];
        // std::cout << "The first solution is " << x[ncol-1][0] << "\n";
        for (int i=(ncol-1);i> -1;i--)
        {
            sum_temp+= A[k][i]*x[i][0];
        }
        x[k][0]=(1/A[k][k])*(b[k][0]-sum_temp);
        // std::cout << "The k th solution is " << x[k][0] << "\n";
    }
    return x;
    
    // Free matrix memory
    
    FreeMatrixMemory(nrow,Atemp);
    FreeMatrixMemory(length,btemp);
    FreeMatrixMemory(length,x);
    
}





// Function multiply a A%*%b

double** Multiply(double** A, double** x, int nrowA, int ncolA, int length)
{
    // Assert that the columns of A and the rows of B match
    
    assert (ncolA==length);
    
    // Create the matrix to store the matrix product
    
    double** Matrix;
    
    //Allocate the memory for Matrix
    
    Matrix = AllocateMatrixMemory(nrowA,1);
    
    //Calculate the elements of Matrix as the sum of the product of the elements in A and B
    
    for (int i=0; i<nrowA; i++)
    {
        double temp=0;
        for (int j=0; j<length; j++)
        {
            // double temp=0;
            // for (int k=0; k<ncolA; k++)
            // {
                temp += A[i][j]*x[j][0];
                std::cout << "Inside the multiply loop A[i][k] " << A[i][j] << "\n";
                std::cout << "Inside the multiply loop x[k][0] " << x[j][0] << "\n";
            // }
            // Matrix[j][0]=temp;
            // std::cout << "Inside the multiply loop" << Matrix[j][0] << "\n";
        }
        Matrix[i][0]=temp;
    }
    
    return Matrix;
}









// A function to solve the linear system of equations via Gaussian elimination no pivoting

//double** linear_solve(double** A, double** b, int nrow, int ncol, int length)
//{
//    // Assign the variables
//    
//    double** Atemp;
//    double** btemp;
//    double** x;
//    
//    // Allocate the memory
//    
//    Atemp=AllocateMatrixMemory(nrow,ncol);
//    btemp=AllocateMatrixMemory(length,1);
//    x=AllocateMatrixMemory(length,1);
//    
//    //std::cout << "ncol is " << ncol << "\n";
//    //std::cout << "nrow is " << nrow << "\n";
//    
//    // Insert a condition so that we have a determined system
//    
//    if (Determinant(A,nrow,ncol)==0)
//    {
//        std::cout << "Sorry your A matrix is singular" << "\n";
//    } else
//    {
//        // If the matrix is not singular do the Gaussian elimination
//        
//    for (int k=0; k<ncol; k++)
//     {
//        for (int i=k+1; i<nrow; i++)
//        {
//            b[i][0]=b[i][0]-(A[i][k]/A[k][k])*b[k][0];
//            for (int j=k+1; j<ncol; j++)
//            {
//                A[i][j]=A[i][j]-(A[i][k]/A[k][k])*A[k][j];
//                
//                // Print out the results so we can see what is happening
//                // std::cout << "Atemp[i][j] is " << Atemp[i][j] << "\n";
//                //std::cout << "A[i][k] is " << A[i][k] << "\n";
//                //std::cout << "A[k][k] is " << A[k][k] << "\n";
//                //std::cout << "A[k][j] is " << A[k][j] << "\n";
//                //std::cout << "i is " << i << "\n";
//                //std::cout << "j is " << j << "\n";
//                //std::cout << "A i j is " << A[i][j] << "\n";
//            }
//        }
//    }
//    
//    // Assign the 0 to the elements of the matrix that are below the diagonal. The above code only deals with the upper triangular matrix
//        
//    for (int zero_row=1; zero_row <ncol;zero_row++)
//    {
//        for (int zero_col=0; zero_col<zero_row; zero_col++)
//        {
//        std::cout << "zero_row is " << zero_row << "\n";
//        std::cout << "zero_col is " << zero_col << "\n";
//        A[zero_row][zero_col]=0;
//        }
//    }
//    
//    // Print out the results so we can see what is happening
//    
//    // A matrix
//        
//    for (int p=0; p<nrow; p++)
//    {
//
//        std::cout << "A i j is " << "\t" << A[p][0] << "\t" << A[p][1] << "\t" << A[p][2] << "\n";
//    }
//    
//    // b vector
//        
//    for (int i=0; i<nrow; i++)
//    {
//            
//        // Print out the results so we can see what is happening
//        std::cout << "b i j is " << b[i][0] << "\n";
//        }
//    }
//    
//    // Given the upper triangular matrix and the adjusted b vector calculate the elements of x
//    
//    for (int k=(ncol-2); k>-1; k--)
//    {
//        double sum_temp=0;
//        x[ncol-1][0]=b[ncol-1][0]/A[ncol-1][ncol-1];
//        std::cout << "The first solution is " << x[ncol-1][0] << "\n";
//         for (int i=(ncol-1);i> -1;i--)
//         {
//            sum_temp+= A[k][i]*x[i][0];
//         }
//     x[k][0]=(1/A[k][k])*(b[k][0]-sum_temp);
//     std::cout << "The k th solution is " << x[k][0] << "\n";
//    }
//    return x;
//    
//    // Free matrix memory
//    
//    FreeMatrixMemory(nrow,Atemp);
//    FreeMatrixMemory(length,btemp);
//    FreeMatrixMemory(length,x);
//    
//}


//// Excercise 5.8
//// -------------
//
//// Calculate the determinant of a matrix of arbitrary size using recursion
//
//int main(int argc, char* argv[])
//{
//    // Variable declaration
//    
//    int nrow;
//    int ncol;
//    double** A;
//    
//    // Start with a matrix of size 1
//    
//    nrow=3;
//    ncol=3;
//    
//    
//    // Allocate the memory
//    
//    A=AllocateMatrixMemory(nrow,ncol);
//    
//    A[0][0]=1; A[0][1]=9; A[0][2]=3;// A[0][3]=4;
//    A[1][0]=4; A[1][1]=5; A[1][2]=2;// A[1][3]=7;
//    A[2][0]=6; A[2][1]=1; A[2][2]=9;// A[2][3]=3;
//   // A[3][0]=4; A[3][1]=4; A[3][2]=5; A[3][3]=2;
//    
//    // std::cout << A[0][0] << "\n";
//    
//    // Print the result
//    
//     std::cout << determinant(A,  nrow, ncol) << "\n";
//    // determinant(A,  nrow, ncol);
//    // Delete the allocated memory as it is good practice
//    
//     FreeMatrixMemory(nrow, A);
//}



// Matrix multiplication of two matrices

double** Multiply(double** A, double** B, int nrowA, int ncolA, int nrowB, int ncolB)
{
    // Assert that the columns of A and the rows of B match
    
    assert (ncolA==nrowB);
    
    // Create the matrix to store the matrix product
    
    double** Matrix;
    
    //Allocate the memory for Matrix
    
    Matrix = AllocateMatrixMemory(nrowA, ncolB);
    
    //Calculate the elements of Matrix as the sum of the product of the elements in A and B
    
    for (int i=0; i<ncolA; i++)
    {
        for (int j=0; j<nrowB; j++)
        {
            double temp=0;
            for (int k=0; k<ncolA; k++)
            {
                temp += A[i][k]*B[k][j];
            }
            Matrix[i][j]=temp;
            // std::cout << Matrix[i][j] << "\n";
        }
    }
    
    return Matrix;
}






//    result=0;
//    for (int i=0; i<ncol; i++)
//    {
//        Atemp=AllocateMatrixMemory(nrow-1,ncol-1);
//        
//        result+=pow(-1,i)*A[0][i]*determinant(A,i,i) ;
//    }



// Excercise 5.7
// --------------

// The p-norm of a vector v on length n is ||v||_p=(sum_i^n|v_i|^p)^(1/p) where p is a positive
// integer. Extend the code in listing 5.2 to calculate the p-norm of a given vector, where p take the default value 2.

//int main(int argc, char* argv[])
//{
//        // Variable declaration
//    
//        int length;
//        int p;
//        double* v = new double [length] ;
//    
//        length=5;
//        p=2;
//        v[0]=1; v[1]=2.5; v[2]=90.0; v[3]=3.2; v[4]=9.7;
//    
//        // Calculate the pnorm of a vector
//    
//        // p_norm(v,length, p);
//    
//        // Print me out the p norm
//    
//         std::cout << p_norm(v,length, p) << "\n";
//    
//        // Test the default function as well
//    
//        std::cout << p_norm(v,length) << "\n";
//        // Delete the allocated memory as it is good practice
//    
//        delete[] v;
//}

// Overload the function so that the default is just the regular 2 norm

double p_norm(double* v, int length)
{
    // Declare the return variable
    
    double p_norm_val;
    // std::cout << p_norm_val << "\n";
    p_norm_val = 0.0;                  // Remember to always initialise the temporary value
    for (int i=0; i<length; i++)
    {
        p_norm_val += pow(fabs(v[i]),2.0);
    }
    
    // Do the final power after the summation
    
    p_norm_val=pow(p_norm_val,0.5); // I think the 1.0 here is very important here to keep it as a double
    
    return p_norm_val;
}


// Function to calculate the p-norm of a vector v on length n is ||v||_p=(sum_i^n|v_i|^p)^(1/p) where p is a positive integer

double p_norm(double* v, int length, int p)
{
    // Declare the return variable
    
    double p_norm_val;
    // std::cout << p_norm_val << "\n";
    p_norm_val = 0.0;                  // Remember to always initialise the temporary value
    for (int i=0; i<length; i++)
    {
        p_norm_val += pow(fabs(v[i]),p);
    }
    
    // Do the final power after the summation
    
    p_norm_val=pow(p_norm_val,1.0/p); // I think the 1.0 here is very important here to keep it as a double
    
    return p_norm_val;
}





// Excercise 5.4
// -------------

// Write a function to calculate the mean and standard deviation of a vector

//int main(int argc, char* argv[])
//{
//    // Define the variables
//    
//    double** x;
//    int nrow=5, ncol=1;
//    double mean;
//    double stdev;
//    
//    // Allocate the matrix memory
//    
//    x = AllocateMatrixMemory(nrow,ncol);
//    
//    x[0][0]=3.0 ; x[1][0]=9.7; x[2][0]=4.5 ; x[3][0]=7.2; x[4][0]=9.23;
//    
//    // Calculate the mean and standard deviation
//    
//    MeanandStandardDeviation(x, nrow, mean, stdev);
//    
//    // Print the mean and standard deviation to the screen
//    
//    std::cout << "The mean of the vector x is " << mean << "\n";
//    std::cout << "The mean of the vector x is " << stdev << "\n";
//    
//    // Free the matrix memory where the first integer argument is the number of rows of matrix
//
//    FreeMatrixMemory(nrow, x);
//
//}

//void  MeanandStandardDeviation(double** x, int length, double& mean, double& stdev)
//{
//    // Define the variables
//    
//    double temp=0;   // Set a temporary holder for the sum of the values
//    double sumsqr=0; // Set a temporary holder for the sum of squares the values
//    
//    
//    // Calculate the mean as sum(x[i])/n
//    
//    for (int i=0; i<length; i++)
//    {
//        temp += x[i][0];
//    }
//    mean= temp/length;
//    
//  
//    // Calculate the standard deviation
//    
//    for (int i=0; i<length; i++)
//    {
//        sumsqr += (x[i][0]-mean)*(x[i][0]-mean);
//    }
//    stdev = sqrt(sumsqr/(length-1));
//}







//// Excercise 5.BONUS
//// -------------
//
//// Compute the matrix product of the genotype raw file for my Bayes R practice data set
//// Require me to read in the data find the size of the matrix, allocate the memory,
//// compute the product and write it out and then deallocate the memory
//
//int main(int argc, char* argv[])
//{
//    double** A;
//    double** C;
//    int nrow=0;
//    int ncol=0;
//    string line;
//
//    // Open the read file stream and read in the 100*100 genotype matrix
//    
//    ifstream read_file_size ("/Users/uqllloyd/Desktop/Bayes_R_prog_practice/geno.raw");
//    
//    
//    // Get the size of the matrix stored as a text file
//    
//    
//    if( !read_file_size)
//    {
//        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
//    }
//    else
//    {
//            while(getline(read_file_size,line)) // Get one line of the file and store as string
//            {
//
//                istringstream iss(line); // Make the line into a string stream
//                string result;           // Make another string to store the ind elements
//                ncol=0;
//                while(getline(iss,result, ' ')) // Get each element of the stream separated by space
//                {
//                    ncol++;                     // Increment the columns
//                }
//                nrow++;                         // Increment the rows
//                
//            }
//    
//    }
//    
//    cout << "# of Rows " << nrow << "\n";
//    cout << "# of Cols " << ncol << "\n";
//    read_file_size.close(); // Flush the buffer. This is important so that we don't over fill the buffer
//    
//    // Allocate the memory.
//    
//    A= AllocateMatrixMemory(nrow,ncol);
//    
//    
//    // Read in the data
//    
//    ifstream read_file ("/Users/uqllloyd/Desktop/Bayes_R_prog_practice/geno.raw");
//    assert(read_file.is_open());
//    
//    for (int i=0; i<nrow; i++)
//    {
//        for (int j=0; j<ncol; j++)
//        {
//            read_file >> A[i][j];
//            // std::cout << "ith jth element of the A matrix" << A[i][j] << "\n";
//        }
//    }
//
//    std::cout << "First element of the A matrix " << A[0][0] << "\n";
//    
//    read_file.close(); // Flush the buffer. This is important so that we don't over fill the buffer
//    
//    
//    // Do the matrix multiplication
//
//    C= Multiply(A, A, nrow, ncol, nrow, ncol);
//    
//    
//    // Write the matrix result to a file
//    
//    std::ofstream write_output("/Users/uqllloyd/Desktop/Bayes_R_prog_practice/geno_geno.raw"); //Open the write stream
//    assert(write_output.is_open());  // Make sure it's open
//    
//    for (int i=0; i<nrow; i++)
//    {
//        for (int j=0; j<ncol; j++)
//        {
//            if ((j+1)%ncol==0)
//            {
//            write_output << C[i][j] << "\n";
//            }
//            else
//            {
//                // For those not at the end of a row
//                write_output << C[i][j] << "\t";
//            }
//        }
//    }
//    
//    // Close the write stream
//    
//    write_output.close();
//    
//    
//    // Free the matrix memory where the first integer argument is the number of rows of matrix
//
//    FreeMatrixMemory(nrow, A);
//
//}

// Excercise 5.6
// -------------

// Overload the Multiply function so that it can multiply a vector and a matrix, a matrix and a vector, a scalar and a matrix, a matrix and a scalar
//
//int main(int argc, char* argv[])
//{
//    int n=2;
//    double** A;
//    double** B;
//    double* x = new double [n] ;
//    int scalar=5;
//    
//    // Dynamically allocate the memory
//
//    A=AllocateMatrixMemory(2,2);
//    B=AllocateMatrixMemory(2,2);
//    double** C;
//
//    // Allocate the matrices and vectors
//    
//    x[0]=7; x[1]=18;
//    A[0][0]=2; A[0][1]=3; A[1][0]=3; A[1][1]=5;
//    B[0][0]=10; B[0][1]=5; B[1][0]=6; B[1][1]=2;
//    
//    // Do the vector by matrix multiplication
// 
//    C=Multiply(x, B, 2, 2, 2);
//    std::cout << C[0][0] << "\t" << C[0][1] << "\n" ;
//
//    // Do the matrix by matrix multiplication
//
//    // C=Multiply(A, B, 2, 2, 2, 2);
//    // std::cout << C[0][0] << "\t" << C[0][1] << "\n" << C[1][0] << "\t" << C[1][1] ;
//
//    // Free the matrix memory
//
//    FreeMatrixMemory(2, A);
//    FreeMatrixMemory(2, B);
//}
//
//// Multiple a scalar and matrix
//
//double** Multiply(scalar, double** A, int ncolA, int nrowA)
//{
//    // Assert that the columns of A and the rows of B match
//    
//    assert (length==nrowA);
//    
//    // Create the matrix to store the matrix product
//    
//    double** Matrix;
//    
//    //Allocate the memory for Matrix
//    
//    Matrix = AllocateMatrixMemory(1, ncolA);
//    
//    //Calculate the elements of Matrix as the sum of the product of the elements in A and B
//    
//    for (int i=0; i<nrowA; i++)
//    {
//        for (int j=0; j<length; j++)
//        {
//            double temp=0;
//            for (int k=0; k<nrowA; k++)
//            {
//                temp += x[j]*A[k][i];
//            }
//            Matrix[0][j]=temp;
//            // std::cout << Matrix[i][j] << "\n";
//        }
//    }
//    
//    return Matrix;
//}




// Multiple a vector and matrix

double** Multiply(double* x, double** A, int length, int ncolA, int nrowA)
{
    // Assert that the columns of A and the rows of B match
    
    assert (length==nrowA);
    
    // Create the matrix to store the matrix product
    
    double** Matrix;
    
    //Allocate the memory for Matrix
    
    Matrix = AllocateMatrixMemory(1, ncolA);
    
    //Calculate the elements of Matrix as the sum of the product of the elements in A and B
    
    for (int i=0; i<nrowA; i++)
    {
        for (int j=0; j<length; j++)
        {
            double temp=0;
            for (int k=0; k<nrowA; k++)
            {
                temp += x[j]*A[k][i];
            }
            Matrix[0][j]=temp;
            // std::cout << Matrix[i][j] << "\n";
        }
    }
    
    return Matrix;
}





// Excercise 5.5
// -------------

// Write a function Multiply that may ve used ti multiply two matrices given the matrices
// and the size of both matrices. Use assertions to verify that the matrices are of suitable
// sizes

//int main(int argc, char* argv[])
//{
//    double** A;
//    double** B;
//    
//    // Dynamically allocate the memory
//    
//    A=AllocateMatrixMemory(2,2);
//    B=AllocateMatrixMemory(2,2);
//    double** C;
//    
//    // Allocate the matrices
//    
//    A[0][0]=2; A[0][1]=3; A[1][0]=3; A[1][1]=5;
//    B[0][0]=10; B[0][1]=5; B[1][0]=6; B[1][1]=2;
//    
//    //Do the matrix multiplication
//    
//    C=Multiply(A, B, 2, 2, 2, 2);
//    std::cout << C[0][0] << "\t" << C[0][1] << "\n" << C[1][0] << "\t" << C[1][1] ;
//    
//    // Free the matrix memory
//    
//    FreeMatrixMemory(2, A);
//    FreeMatrixMemory(2, B);
//}

// Matrix multiplication

//double** Multiply(double** A, double** B, int nrowA, int ncolA, int nrowB, int ncolB)
//{
//    // Assert that the columns of A and the rows of B match
//    
//    assert (ncolA==nrowB);
//    
//    // Create the matrix to store the matrix product
//    
//    double** Matrix;
//    
//    //Allocate the memory for Matrix
//    
//    Matrix = AllocateMatrixMemory(nrowA, ncolB);
//    
//    //Calculate the elements of Matrix as the sum of the product of the elements in A and B
//    
//    for (int i=0; i<ncolA; i++)
//    {
//        for (int j=0; j<nrowB; j++)
//        {
//            double temp=0;
//                for (int k=0; k<ncolA; k++)
//                {
//                    temp += A[i][k]*B[k][j];
//                }
//            Matrix[i][j]=temp;
//           // std::cout << Matrix[i][j] << "\n";
//        }
//    }
//    
//    return Matrix;
//}

// Function to allocate memory for a matrix dynamically - can be used for arrays too

double** AllocateMatrixMemory(int numRows, int numCols)
{
    double** matrix;
    matrix = new double* [numRows];  // Allocate the rows
    for (int i=0; i<numRows; i++)
    {
        matrix[i] = new double [numCols]; //Allocate the columns
    }
    return matrix;
}


// Function to free memory of a matrix

void FreeMatrixMemory(int numRows, double** matrix)
{
    for (int i=0; i<numRows; i++)
    {
        delete[] matrix[i]; //Deletes the columns
    }
    delete[] matrix;
}


// Excercise 5.3
// -------------

// Write a function that swaps the values of two double precision FPNs so that these changes are
// visible in the code that has called this function. First with pointers and then references

//int main(int argc, char* argv[])
//{
//    double x=10;
//    double y=5;
//    //ChangeDouble(*x,*y); //Take in the addresses of two FPNs and swaps x to y and VV-pointers
//    ChangeDouble2(x,y); //Take in the addresses of two FPNs and swaps x to y and VV-pointers
//    std::cout << "The value at x address is " << x << "\n";
//    std::cout << "The value at y address is " << y << "\n";
//    return 0;
//}


// Function to swap the values of two FPNs at a particular address - references -Ex 5.3

void ChangeDouble2(double& x, double& y)
{
    double temp_x;
    temp_x = x;
    x=y;
    y=temp_x;
}


// Function to swap the values of two FPNs at a particular address - pointers -Ex 5.3

void ChangeDouble(double* x, double* y)
{
    double temp_x;
    temp_x = *x;
    *x=*y;
    *y=temp_x;
}



// Excercise 5.2
// -------------

// Write code that sends the address of an integer to a function that changes the value of the integer

//int main(int argc, char* argv[])
//{
//    int n=10;
//    int k=5;
//    ChangeInt(&n,&k); //Take in the addresses of two integers and swap n to k them in a function
//    std::cout << "The value at this address is " << k << "\n";
//    return 0;
//}


// Excercise 5.1
// -------------

// Write code that sends the address of an integer to a function that prints the value of the integer

//int main(int argc, char* argv[])
//{
//    int n=10;
//    PrintInt(&n);
//    
//    return 0;
//}


// Function to change the value of an integer at a particular address - Ex 5.2

void ChangeInt(int* n, int* k)
{
    std::cout << "The value at this address is " << *n << "\n";
    *n=*k;
}


// Function to print the value of an integer at a particular address - Ex 5.1

void PrintInt(int* n)
{
    std::cout << "The value at this address is " << *n << "\n";
}


// Function to allocate memory for a matrix dynamically - can be used for arrays too

//double** AllocateMatrixMemory(int numRows, int numCols)
//{
//    double** matrix;
//    matrix = new double* [numRows];  // Allocate the rows
//    for (int i=0; i<numRows; i++)
//    {
//        matrix[i] = new double [numCols]; //Allocate the columns
//    }
//    return matrix;
//}
//
//
//// Function to free memory of a matrix
//
//void FreeMatrixMemory(int numRows, double** matrix)
//{
//    for (int i=0; i<numRows; i++)
//    {
//        delete[] matrix[i]; //Deletes the columns
//    }
//    delete[] matrix;
//}



/************************************************************************
 ************************************************************************
 **                                                                    **
 **                   Section 5 Excercises                             **
 **                                                                    **
 ************************************************************************
 ************************************************************************/



/************************************************************************
 ************************************************************************
 **                                                                    **
 **                   Something Very Important                         **
 **                                                                    **
 ************************************************************************
 ************************************************************************/




// Very important comment
// ----------------------

//Tips: Code Documentation
//Tips: Code Documentation

//Pay attention to quality. Your code will not always be as well understood at it is now
//You may come back to it in three years
//You may hand your code over to someone else

////p-norm function prototype
//double CalculateNorm(double x, int s, int p);
////int CalculateFactorial(int n);
////Computer programs should be human readable
//// Function to calculate the p-norm of a vector:
//// = [ Sum_i ( |x_i|**p ) ] ** (1/p)
////  x is a pointer to the vector which is of size vecSize
//
//
//int main(int argc, char* argv[])
//{
//    double x;
//    int s=1;
//    int p=2;
//    x=10;
//    
//    //CalculateNorm(*p_x,s,p)
//    std::cout << CalculateNorm(x,s,p) << "\n";
//    return 0;
//}
//
//
//double CalculateNorm(double x, int s, int p)
//{
//    double sum = 0.0;
//    //Loop over elems x_i of x, incrementing sum by |x_i|**p
//
//    double temp = fabs(x);
//    sum +=pow(temp, p);
//    
//    //Return p-th root of sum
//    return pow(sum,1.0/p);
//}

//Tips: Code Documentation
//Tips: Code Documentation

//Modules-Want to solve linear systems Ax=b, where A is a square invertible matrix of size n
//Modules-Want to write a function Solve Linear System
//A Module is a collection of functions that perform a given tast. Every module has an interface.
//This interface was defined by the prototype of the function and is a list of variable that contains
//and may be thought of as a list of variables that contains: i) those that must be input to the module and those that are output by the module
//Useful for sharing code. Can be used then as a black box

//SolveLinearSystem(double** A, double* x, double* b, int n);


//Modules
//Modules



//Recursive Functions
//Recursive Functions

//int CalculateFactorial(int n);
//
//int main(int argc, char* argv[])
//{
//    int n=10;
//    std::cout << "The factorial of " << n << " is " << CalculateFactorial(n) << "\n";
//    return 0;
//}
//
//int CalculateFactorial(int n)
//{
//    assert (n > 0);
//    if(n==1)
//    {
//        return 1;
//    }
//    else
//    {
//        // n>1
//        std::cout << "current n value is " << n << "\n";
//        return n*CalculateFactorial(n-1);
//    }
//}


//Recursive Functions-This is pretty crazy good
//Recursive Functions



//// Implementation of Newton-Raphson iteration
//// Implementation of Newton-Raphson iteration
//// Implementation of Newton-Raphson iteration
//
//double SolveNewton(double (*pFunc)(double), double (*pFuncPrime)(double), double x)
//{
//    double step;
//    do
//    {
//        step = (*pFunc)(x)/(*pFuncPrime)(x);
//        x -=step;
//    } while (fabs(step) > 1.0e-5);
//    return x;
//}
//
////Function to calculate x that satisfies sqrt(x)=10
////Function to calculate x that satisfies sqrt(x)=10
//
//double Sqrt10(double x)
//{
//    return sqrt(x) -10.0;
//}
//
//
//// Derivative of function sqrt(x)=10 to calculate x that satisfies sqrt(x)=10
//
//double Sqrt10Prime(double x)
//{
//    return 1.0/(2.0*sqrt(x));
//}
//
//// Function to calculate x that satisfies x*x*x=10
//
//double Cube10(double x)
//{
//    return x*x*x - 10.0;
//}
//
//// Derivative of function to calculate x that satisfies x*x*x=10
//
//double Cube10Prime(double x)
//{
//    return 3.0*x*x;
//}
//
//int main(int argc, char* argv[])
//{
//    std::cout << "Root sqrt(x)=10, with guess 1.0 is "<< SolveNewton(Sqrt10,Sqrt10Prime,200.0) << "\n";
//    std::cout << "Root x**3=10, with guess 1.0 is " << SolveNewton(Cube10,Cube10Prime,1.0) << "\n";
//    return 0;
//}
//

//Function Pointers
//Function Pointers





//double myFunction(double x);
//double myOtherFunction(double x);
//
////Function Pointers-Implement NR for a nonlinear function f(x)=0 for different nonlinear functions
////Function Pointers- Can do this via function pointers
//
//int main(int argc, char* argv[])
//{
//    double (*p_function)(double x);
//    
//    p_function = &myFunction;
//    std::cout << p_function(2.0) << "\n";
//    
//    p_function = &myOtherFunction;
//    std::cout << p_function(2.0) << "\n";
//    
//    return 0;
//}
//
//double myFunction(double x)
//{
//    return x*x;
//}
//
//double myOtherFunction(double x)
//{
//    return x*x*x;
//}
//
////Function Pointers
////Function Pointers







//Declaring Functions Without Prototypes-It is good prectice to give th function signature p
//Declaring Functions Without Prototypes-prototypes before you write the implementation. This is so the function main will recognise the name and argument types of the new function.

//double Square(double x)
//{
//    return x*x;
//}

//Declaring Functions Without Prototypes-have to put it before main so the compiler can see it
//Declaring Functions Without Prototypes-can get into trouble doing this


//Function Overloading-Can use the same name for a function but just pass diff args
//Function Overloading-This is called function overloading

//void Multiply(double scalar, double* u, double* v, int n);
//void Multiply(double scalar, double** A, double** B, int n);
//
//int main(int argc, char* argv[])
//{
//    int n = 2;
//    double* u = new double [n];
//    double* v = new double [n];
//    double** A = new double* [n];
//    double** B = new double* [n];
//    for (int i=0; i<n; i++)
//    {
//        A[i] = new double [n];
//        B[i] = new double [n];
//    }
//    
//    u[0] = -8.7; u[1] = 3.2;
//    A[0][0] = 2.3; A[0][1] = -7.6;
//    A[1][0] = 1.3; A[1][1] = 45.3;
//    
//    double s=2.3, t=4.8;
//    
//    // vector multiplication
//    Multiply(s, u, v, n);
//    
//    // matrix multiplication
//    Multiply(t, A, B, n);
//    
//    delete[] u;
//    delete[] v;
//    for (int i=0; i<n; i++)
//        {
//            delete[] A[i];
//            delete[] B[i];
//        }
//    
//    delete[] A;
//    delete[] B;
//    return 0;
//}
//
//void Multiply(double scalar, double* u, double* v, int n)
//{
//    // v = scalar*u (scalar by vector)
//    for (int i=0; i<n; i++)
//    {
//     v[i]= scalar*u[i];
//        std::cout << v[i]<<"\n";
//    }
//}
//
//void Multiply(double scalar, double** A, double** B, int n)
//{
//    // B= scalar*A (scalar by matrix)
//    for (int i=0; i<n; i++)
//    {
//        for (int j=0; j<n; j++)
//        {
//            B[i][j]= scalar*A[i][j];
//            std::cout << B[i][j] << "\n";
//        }
//    }
//}

//Function Overloading-compiler can only see the difference between function from the argum
//Function Overloading-ments that are passed to it. This is not the case with the return type



//Default Values for Function Arguments-Tolerance for Newton-Raphson technique
//Default Values for Function Arguments-Using NR to solve for f(x)=x^3-K=0
// Using x0=guess and iteration xn=xnm1 - (xnm1-K)/(3*xnm1^2). Set default values for the tolerance and maximum number of function iterations
//
//void CalculateCubeRoot(double& x, double K, double tolerance = 1.0e-6, int maxIterations=100);
//
//int main(int argc, char* argv[])
//{
//    double x = 1.0;
//    double K = 12.0;
//    
//    // Calculate cube root using default values
//    CalculateCubeRoot(x, K);
//    std::cout << x << "\n";
//
//    // Calculate cube root using a tolerance of 0.001 and the
//    // default maximum number of iterations
//    
//    double tolerance = 0.001;
//    CalculateCubeRoot(x, K, tolerance);
//    std::cout << x << "\n";
//    
//    // Calculate cube root using a tolerance of 0.001 and a
//    // maximum number of iterations of 50
//    
//    int maxIterations = 0;
//    CalculateCubeRoot(x, K, tolerance, maxIterations);
//    std::cout << x << "\n";
//    
//    return 0;
//}
//
//void CalculateCubeRoot(double& x, double K, double tolerance, int maxIterations)
//{
//    int iterations = 0;
//    double residual = x*x*x-K;
//    while ((fabs(residual) > tolerance) && (iterations < maxIterations))
//    {
//        x = x-(x*x*x-K)/(3.0*x*x);
//        residual = x*x*x-K;
//        iterations++;
//    }
//}

//Default Values for Function Arguments
//Default Values for Function Arguments



//Reference Variables-pointers can be used to allow changes within function to have an effect outside funtions
//Reference Variables-An alternative is to use reference varaibles-variables used inside functions that are a different name for the same variable as that sent to a function. Any change in the function will have an effect outside and they are much easier to use than pointers. Use of the & symbol


//void CalculateRealAndImaginary(double r, double theta, double& real, double& imaginary);
//
//int main(int argc, char* argv[])
//{
//    double r = 3.4;
//    double theta = 1.23;
//    double x, y;
//    CalculateRealAndImaginary(r, theta, x, y);
//    std::cout << "Real part = " << x << "\n";
//    std::cout << "Imaginary part = " << y << "\n";
//
//    return 0;
//}
//
//
//void CalculateRealAndImaginary(double r, double theta, double& real, double& imaginary)
//{
//    real = r*cos(theta);
//    imaginary = r*sin(theta);
//}

//Reference Variables
//Reference Variables


//Example: A Function to Calculate the Scalar Product of Two Vectors
//Example: A Function to Calculate the Scalar Product of Two Vectors



//double CalculateScalarProduct(int size, double* a, double* b);
//
//
//int main(int argc, char* argv[])
//{
//    int n=3;
//    double* x = new double [n];
//    double* y = new double [n];
//    x[0]=1.0; x[1]=4.0; x[2] = -7.0;
//    y[0]=4.4; y[1] =4.3; y[2] =76.7;
//    double scalar_product = CalculateScalarProduct(n, x, y);
//    std::cout << "Scalar product=" << scalar_product << "\n";
//    delete[] x;
//    delete[] y;
//    
//    return 0;
//}
//
//
//double CalculateScalarProduct(int size, double* a, double* b)
//{
//    double scalar_product = 0.0;
//    for (int i=0; i<size; i++)
//    {
//        scalar_product += a[i]*b[i];
//        std::cout << scalar_product<< "\n";
//    }
//    return scalar_product;
//}


//Example: A Function to Calculate the Scalar Product of Two Vectors
//Example: A Function to Calculate the Scalar Product of Two Vectors





//Sending Arrays to Functions
//Sending Arrays to Functions

//, any changes made to an array inside a function will have an effect when that variable is used subsequently outside the function

//void DoSomething(double u[], double A[][10], double B[10][10]);
//
//
//int main(int argc, char* argv[])
//{
//    double u[5], A[10][10], B[10][10];
//    DoSomething(u, A, B);
//    
//    // This will print the values allocated in
//    // the function DoSomething
//    std::cout << u[1] << "\n";
//    std::cout << A[2][3] << "\n";
//    std::cout << B[3][3] << "\n";
//    
//    return 0;
//}
//
//
//void DoSomething(double u[], double A[][10], double B[10][10])
//{
//    u[5] = 1.0;
//    A[2][3] = 4.0;
//    B[3][3] = -90.6;
//}

//Sending Arrays to Functions
//Sending Arrays to Functions




//Use of Pointers as Function Arguments-change inside a function affecting outside
//Use of Pointers as Function Arguments- use pointers to reference the address

//void CalculateRealAndImaginary(double r, double theta, double* pReal, double* pImaginary);
//
//int main(int argc, char* argv[])
//{
//    double r = 3.4;
//    double theta = 1.23;
//    double x, y;
//    CalculateRealAndImaginary(r, theta, &x, &y);
//    std::cout << "Real part = " << x << "\n";
//    std::cout << "Imaginary part = " << y << "\n";
//    
//    return 0;
//}
//
//
//void CalculateRealAndImaginary(double r, double theta, double* pReal, double* pImaginary)
//{
//    *pReal = r*cos(theta);
//    *pImaginary = r*sin(theta);
//}

//Use of Pointers as Function Arguments-change inside a function affecting outside
//Use of Pointers as Function Arguments- use pointers to reference the address

//Use of Pointers as Function Arguments
//Use of Pointers as Function Arguments

//
//// Function to allocate memory for a matrix dynamically
//
//double** AllocateMatrixMemory(int numRows, int numCols)
//{
//    double** matrix;
//    matrix = new double* [numRows];
//    for (int i=0; i<numRows; i++)
//    {
//        matrix[i] = new double [numCols];
//    }
//    return matrix;
//}
//
//// Function to free memory of a matrix
//
//void FreeMatrixMemory(int numRows, double** matrix)
//{
//    for (int i=0; i<numRows; i++)
//    {
//        delete[] matrix[i]; //Deletes the columns
//    }
//    delete[] matrix;
//}

//Use of Pointers as Function Arguments
//Use of Pointers as Function Arguments



//Returning Pointer Variables from a Function
//Returning Pointer Variables from a Function

//double** AllocateMatrixMemory(int numRows, int numCols);
//void FreeMatrixMemory(int numRows, double** matrix);
//
//int main(int argc, char* argv[])
//{
//    double** A;
//    A = AllocateMatrixMemory(5, 3);
//    A[0][1] = 2.0;
//    A[4][2] = 4.0;
//    FreeMatrixMemory(5, A);
//
//    return 0;
//}
//
//// Function to allocate memory for a matrix dynamically
//
//double** AllocateMatrixMemory(int numRows, int numCols)
//{
//    double** matrix;
//    matrix = new double* [numRows];
//    for (int i=0; i<numRows; i++)
//    {
//        matrix[i] = new double [numCols];
//    }
//    return matrix;
//}
//
//// Function to free memory of a matrix
//
//void FreeMatrixMemory(int numRows, double** matrix)
//{
//    for (int i=0; i<numRows; i++)
//    {
//        delete[] matrix[i]; //Deletes the columns
//    }
//    delete[] matrix;
//}

//Returning Pointer Variables from a Function
//Returning Pointer Variables from a Function







//Void Functions
//Void Functions

//void HasNoEffect(double x);
//
//int main(int argc, char* argv[])
//{
//    double x = 2.0;
//    HasNoEffect(x); //Only has an effect in the block that it is written in
//    std::cout << x << "\n"; // will print out 2.0
//    
//    return 0;
//}
//
//void HasNoEffect(double x)
//{
//    // x takes the value 2.0 here
//    x += 1.0;
//   // x takes the value 3.0 here
//    
//    std::cout << x << "\n"; // will print out 2.0
//}

//Void Functions
//Void Functions





//Void Functions
//Void Functions

//void PrintPassOrFail(int score, int passMark);
//
//int main(int argc, char* argv[])
//{
//    int score = 31, pass_mark = 30;
//    PrintPassOrFail(score, pass_mark);
//    
//    return 0;
//}
//
//void PrintPassOrFail(int score, int passMark)
//{
//    if (score >= passMark)
//    {
//        std::cout << "Pass - congratulations!\n";
//    }
//    else
//    {
//        // score < passMark
//        std::cout << "Fail - better luck next time\n";
//    }
//}

//Void Functions
//Void Functions



//Simple Functions
//SImple Functions

//double CalcMin(double a, double b); //function prototype tells the compiler what to expect
//
//int main(int argc, const char * argv[])
//{
//    
//
//    double x = 4.0, y = -8.0;
//    double min_val = CalcMin(x, y);
//    std::cout <<"The minimum of" << x << "and" << y << " is " << min_val << "\n";
//    return 0;
//}
//
//double CalcMin(double a, double b)
//{
//    double minimum;
//    if(a<b)
//    {
//        minimum = a;
//    }
//    else
//    {
//        // a >= b
//        minimum = b;
//    }
//    
//    return minimum; //Only one variable may be returned from a function. We may want to return more that one variable. We may also want a function to not return any variable this maybe prototyped as a "void" function. Maybe just print something
//}

//Simple Functions
//SImple Functions
    
//int i=5;  //global i
    //Blocks, Functions and Reference Variables
    //Blocks, Functions and Reference Variables
//    int j = 7;
//    std::cout << i << "\n";
//    {
//        int i=10, j=11;
//        std::cout << i << "\n"; // local value of i is 10
//        std::cout << ::i << "\n"; // global value of i is 5
//        std::cout << j << "\n"; // value of j here is 11
//        //The other j (value 7) is inaccessible
//    }
//    std::cout << j << "\n"; // value of j here is 7
//    //return 0;
    
    //Blocks, Functions and Reference Variables
    //Blocks, Functions and Reference Variables
    
    
    
    //Pointers Excercise 4.4
    //Pointers Excercise 4.4
    
//    for (int i; i<1000000000; i++)
//    {
//        int rows =2, cols =2;
//        double** A;
//        double** B;
//        double** C;
//        A= new double* [rows];
//        B= new double* [rows];
//        C= new double* [rows];
//        for (int i=0; i<rows; i++)
//            {
//                A[i]=new double [cols];
//                B[i]=new double [cols];
//                C[i]=new double [cols];
//                std::cout << A[i] << "\n";
//                std::cout << B[i] << "\n";
//                std::cout << C[i] << "\n";
//            }
//        A[0][0]= 1.5; A[0][1]= 2.5; A[1][0]= 4.5; A[1][1]= 3.7;
//        B[0][0]= 1.5; B[0][1]= 2.5; B[1][0]= 1.3; B[1][1]= 2.7;
//        C[0][0]= A[0][0]+B[0][0]; C[1][0]=A[1][0]+B[1][0]; C[0][1]=A[0][1]+B[0][1] ; C[1][1]=A[1][1]+B[1][1];
//        
//        std::cout << A[1][1] << "\n";
//        std::cout << B[1][1] << "\n";
//        std::cout << C[1][1] << "\n";
////        
//        for (int i=0; i<rows; i++)
//            {
//                delete[] A[i];
//                delete[] B[i];
//                delete[] C[i];
//            }
//        delete[] A;
//        delete[] B;
//        delete[] C;
    //}
    
    //Pointers Excercise 4.4
    //Pointers Excercise 4.4
    
    //Pointers Excercise 4.3
    //Pointers Excercise 4.3
    
//    double* p_x;
//    double* p_y;
//    double* p_DP;
//    
//    for (int i; i<1000000000; i++)
//    {
//    p_x = new double [3]; //create the pointer array of size 2
//    p_y = new double [3]; //create the pointer array of size 2
//    p_DP= new double;
//    
//    p_x[0]=1.0;
//    p_x[1]=3.0;
//    p_x[2]=4.0;
//    
//    p_y[0]=9.0;
//    p_y[1]=12.2;
//    p_y[2]=9.5;
//    
//    *p_DP=p_x[0]*p_y[0]+p_x[1]*p_y[1]+p_x[2]*p_y[2];
//    
//    std::cout << *p_DP << "\n";
//    std::cout << i << "\n";
//    delete[] p_x;
//    delete[] p_y;
//    delete[] p_DP;
//    }
    
    //Pointers Excercise 4.3
    //Pointers Excercise 4.3
    
    
    
    //Pointers Excercise 4.2
    //Pointers Excercise 4.2
    
//    int j=5;
//    int k=10;
//    int* p_j;
//    int* p_k;
//    int* p_df1;
//    
//    p_j = &j;
//    p_k = &k;
//    
//    std::cout << j << "\n";
//    std::cout << k << "\n";
//    
//    p_df1 = new int [1];
//    
//    *p_df1 = *p_j;
//    //std::cout << *p_df1 << "\n";
//    
//    j=*p_k;
//    k=*p_df1;
//    
//    std::cout << j << "\n";
//    std::cout << k << "\n";
    //std::cout << *p_j << "\n";
    //::cout << *p_k << "\n";
    
    //std::cout << j << "\n";
    //std::cout << k << "\n";
    
    //Pointers Excercise 4.2
    //Pointers Excercise 4.2
    
    
    
    //Pointers Excercise 4.1
    //Pointers Excercise 4.1
    
//    int i=5;
//    int* p_j;
//    int* p_k;
//    std::cout << i << "\n";
//    std::cout << p_j << "\n";
//    p_j = &i;
//    std::cout << *p_j << "\n";
//    std::cout << *p_j*5 << "\n";
//    *p_j=*p_j*5;
//    std::cout << *p_j << "\n";
//    
//    p_k = new int [1];
//    std::cout << p_k << "\n";
//    std::cout << *p_k << "\n";
//    p_k = &i;
//    std::cout << *p_k << "\n";
//    
//    delete[] p_k;
    
    //std::cout << *p_k << "\n";
    //Pointers Excercise 4.1
    //Pointers Excercise 4.1
    
    //*p_j = p_j*5;
    //5*p_j;
    //Pointers Excercise 4.1
    //Pointers Excercise 4.1
    
    //Pointer TIPS//Pointer TIPS//Pointer TIPS
    //Pointer TIPS//Pointer TIPS//Pointer TIPS
    
    //DO THE EXCERCISES AS IT IS A DIFFICULT CONCEPT
    
    //TIP 1//TIP 1//TIP 1
    //TIP 1//TIP 1//TIP 1
    
    //Pointer aliasing. In large-scale programs it may be difficult to see where pointers are aliases for other variables. An example is in vector or matrix additon in which the vectors or matrices are stored as arrays and passed into a function via pointers. The operation to compute the matrix sum A=B+C would be probably in a function by a nested loop over the elements of the arrays so that the actual implementation becomes an element wise sum. Matrix aliasing in this case is fine but if the user was using a matrix by matrix product operation. It may be worth provideing two versions of the matrix matrix product one which is efficient but only safe to use when thre is no pointer aliasing and one which is safe in all circumstances.
    
    //The problems of alising run pretty deep and many people have worked hard such that it works when safe
    
    //TIP 2//TIP 2//TIP 2
    //TIP 2//TIP 2//TIP 2
    
    //Safe Dynamic Allocation
    
    //You can use the assert function to make sure that your variable has been assigned a value. It is possible to find a situation where it is not possible to allocate memeory because the number of items in an array has been set with a negative argument or because there is not enough physical memory
    
    //TIP 3//TIP 3//TIP 3
    //TIP 3//TIP 3//TIP 3
    
    //Every new has a delete
    
    //All dynamically allocated memory must be freed or else you may run out of memory. If you do not delete DAM then memory will not be accesible until your program finishes. There are several ways around this with every new having a delete. A second way is to run your program through a memory debugger. Another solution is to use shared pointers which allows memory to be automatically de-allocated.
    
    
    //Pointer TIPS//Pointer TIPS//Pointer TIPS
    //Pointer TIPS//Pointer TIPS//Pointer TIPS
    
    
    
    //Pointers-Irregularly Sized Matrices//
    //Pointers-Irregularly Sized Matrices//
    
    //Create a lower triangular matrix A of integers with 1000 rows and 1000 cols
    
    //int A[1000][1000];
    //This wastes alot of memory storing the super-diagonal entries which all take 0s. If we allocate dynamically we avoid this waste. This is done below where for row i of the matric we declare i+1 nonzero elements that is 1 elelment on row 0 2 in row 1, and so on. MEMORY should be DELETED when this array is no longer required.
//    int** A;
//    A= new int* [1000];
//    for (int i=0; i<1000; i++)
//    {
//        A[i] = new int[i+1];
//    }
    
    //Errors will result if A[9][19] were to be used because there is no position. Classes can be used to improve this
    
    
    
    //Pointers-Matrices-ALWAYS DELETE ANY MEMORY DYNAMICALLY ALLOCATED//
    //Pointers-Matrices-YOU WILL QUICKLY RUN OUT OF MEMORY//
    
    //Create a two-dim array of double precision with 5 rows and 3 columns
//    
//    int rows =5, cols =3;
//    double** A;
//    A= new double* [rows];
//    for (int i=0; i<rows; i++)
//    {
//        A[i]=new double [cols];
//        std::cout << A[i] << "\n";
//    }
//    
//    for (int i=0; i<rows; i++)
//    {
//        delete[] A[i];
//    }
//    delete[] A;
    
    //Each A[i] is a pointer and contains the address of A[i][0]; and A contains the address of the pointer A[0]. The variable A is an array of pointers which is represented by the two asterisks in line 2 of listing 4.1 Line 3 is a pointer to an array of pointers to double precision FPNs and this array is of size rows. The for loop in this listing then specifies that each pointer in the array itself points to an array of DP FPNs of length cols. It is important to delete memory if it is not needed anymore as done in the last for loop.
    
    //Pointers-Matrices//
    //Pointers-Matrices//
    
    
    //Pointers-Vectors//
    //Pointers-Vectors//
    
    //Create a one-dim array of double precision of length 10
    
//    double* x;
//    double* y;
//    x = new double [10]; //create the pointer array of size 10
//    y = new double [10];
//    
//    for (int i=0; i<10; i++)
//    {
//        x[i]=((double)(i)); //changes the interger to a double
//        y[i]=2.0*x[i];
//    }
//    
//    delete[] x;
//    delete[] y;
    
    //Pointers-Vectors//
    //Pointers-Vectors//
    
    // x stores the address of the first element of the array
//    std::cout << x << "\n";
//    std::cout << &x[0] << "\n"; //prints the same value
//    
//    //when the array is no longer required
//    
//    delete[] x;
    
    //Always be sure to free any memory allocated when it is no longer required
    //Pointers-Vectors//
    //Pointers-Vectors//
    
    
    //One main use of pointers-Dynamic allocation of memory for arrays//
    //One main use of pointers-Dynamic allocation of memory for arrays//
    
    //We may not know the size of an array before we compile the code
    //Also used for efficient storage of irregularly sized arrays, lowed triangular matrix
    //We know that most of these entries a zero then we are being wasteful with memory
    //Memory can be allocated with the 'new' operatir and deallocated with 'delete'
    
    
    //One main use of pointers-Dynamic allocation of memory//
    //One main use of pointers-Dynamic allocation of memory//
    
    
    
    
    //Warnings of pointers-2//
    //Warnings of pointers-2//
//        double y;
//        double* p_x; // p_x can store the address of a double precision number. Haven't
//                        // said which address yet
//    y=3.0;
//    p_x =&y;
//    std::cout << "y=" << y << "\n";
//    *p_x = 1.0; //This changes the value of y
//    std::cout << "y=" << y << "\n";
//    
    //Here we have altered y without explictly decalaring its alteration
    //Warnings of pointers-2//
    //Warnings of pointers-2//
    
    
    //Warnings of pointers//
    //Warnings of pointers//
//    double* p_x; // p_x can store the address of a double precision number. Haven't
//                    // said which address yet
//    
//    //*p_x=1.0; //Trying to store the value 1.0 is an unspecificed memory location. This may cause problems. Need to use the 'new' keyword to allocate a valid memory address
//    p_x = new double;  //assigns an address to p_x
//    *p_x=1.0;
//    delete p_x; //releases memory for re-use
    //Warnings of pointers//
    //Warnings of pointers//
    
    
    //Example of pointers//
    //Example of pointers//
//    double y, z;
//    double* p_x;
//    
//    z=3.0;
//    p_x = &z;    // p_x stores the address of z
//    y = *p_x + 1.0; // *p_x is the contents of the memory // p_x, i.e. the value of z
//    std::cout << y;
    //Example of pointers//
    //Example of pointers//
    
    
    //The asterisk determines that it is a pointer. All pointers will begin with p_. Recommend only one point per line
    //double* p_x; //pointer for double precision. Can store the address of a double precision
    //int* p_i;    // pointer for integer. Store the address of an integer
    //Declare pointer variables which are variables that store addresses-location of the computer's memory of other variables.
    
    //int total_sum = 10;
    //std::cout << &total_sum << "\n"; // The location in memory. Memory is allocated to
    // this variable and the location of this memory will not vary throughout execution
    // Thus, the address will take a constant value throughout execution
    
    
    
    
    
    //////////////////POINTERS/////////////////////
    //////////////////POINTERS/////////////////////
    //////////////////POINTERS/////////////////////
    
    
    
    
    //EX 3.3-implicit Euler method
    //EX 3.3-implicit Euler method
//        std::ofstream write_file("/Users/uqllloyd/Desktop/xy.dat");
//        double h, yk, ykp1, x;
//        double number_of_grid_points = atof(argv[1]);
//        assert(number_of_grid_points>0);
//        h=1/number_of_grid_points;
//        std::cout << h << "\n";
//        yk=1;
//        x=0;
//        for (int i=1; i<number_of_grid_points; i++)
//            {
//                x=x+h;
//                ykp1=yk/(1+h);
//                yk=ykp1;
//                write_file << x << " " << ykp1 << "\n";
//                //std::cout << ykp1 << "\n";
//            }
    
            //    {
    //EX 3.3-implicit Euler method
    //EX 3.3-implicit Euler method
    
    
    //EX 3.2
    //EX 3.2
//        std::ifstream read_file("/Users/uqllloyd/Desktop/x_and_y.dat");
//        if (!read_file.is_open())
//            {
//                return 1;
//            }
//        int number_of_rows = 0;
//        while(!read_file.eof())
//        {
//            double dummy1, dummy2, dummy3, dummy4;
//            read_file >> dummy1 >> dummy2 >> dummy3 >> dummy4;
//            std::cout << dummy1 << dummy2 << dummy3 << dummy4 << "\n";
//            //read_file >> dummy3 >> dummy4;
//            //std::cout << dummy3 << dummy4 << "\n";
//            number_of_rows++;
//        }
//    read_file.fail();
//        std::cout << "Number of rows = "<< number_of_rows << "\n";
//        read_file.close();
    //EX 3.2
    //EX 3.2
    

    //EX 3.1
    //EX 3.1
//    std::ofstream write_file("/Users/uqllloyd/Desktop/x_and_y.dat");
//    double x[4] = {0.0, 1.0, 1.0, 0.0};
//    double y[4] = {0.0, 0.0, 1.0, 1.0};
//    write_file.setf(std::ios::scientific);
//    write_file.setf(std::ios::showpos);
//    write_file.precision(10);
//    write_file << x[0] << " " << x[1] << " " << x[2] << " " << x[3]<< " " << "\n";
//    write_file.flush();
//    write_file << y[0] << " " << y[1] << " " << y[2]<< " " << y[3] << " " << "\n";
//    write_file.flush();
    //EX 3.1
    //EX 3.1
    
    
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    
    //    std::ofstream write_file("/Users/hayleywise/Desktop/OutputFormatted.dat");
    //    // Write numbers as +x.<<13digits>e+00 (width 20)
    //    write_file.setf(std::ios::scientific);
    //    write_file.setf(std::ios::showpos);
    //    write_file.precision(13);
    //
    //    double x = 3.4, y = 0.0000855, z = 984.424;
    //    write_file<<x<<""<<y<<""<<z<<"\n";
    //    write_file.close();
    //
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    
    
    
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    
//    std::ofstream write_file("/Users/hayleywise/Desktop/OutputFormatted.dat");
//    // Write numbers as +x.<<13digits>e+00 (width 20)
//    write_file.setf(std::ios::scientific);
//    write_file.setf(std::ios::showpos);
//    write_file.precision(13);
//    
//    double x = 3.4, y = 0.0000855, z = 984.424;
//    write_file<<x<<""<<y<<""<<z<<"\n";
//    write_file.close();
//    
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    //CONTROLLING FILE OUTPUT_SCIENTIFIC PRECISION AND SPACING
    
    
    //READING FROM A FILE PROGRAM 3-Passing arguments to a program
    //READING FROM A FILE PROGRAM 3-Passing arguments to a program
   // std::cout << "Number of command line arguments=" << argc << "\n";
//    for (int i=1; i<argc; i++)
//    {
//        std::cout << "Argument" << i << " = " << argv[i];
//        std::cout << "\n";
//    }
//    std::string program_name = argv[0];
//    int number_of_nodes = atoi(argv[1]);
//    double conductivity = atof(argv[2]);
//    std::cout << "Program name =" << program_name << "\n";
//    std::cout << "Number of nodes = " << number_of_nodes;
//    std::cout << "\n";
//    std::cout << "Conductivity = " << conductivity << "\n";
    //READING FROM A FILE PROGRAM 3--Passing arguments to a program
    //READING FROM A FILE PROGRAM 3-Passing arguments to a program
    
    
    
    
    //READING FROM A FILE PROGRAM 2-When we don't know the size of the file
    //READING FROM A FILE PROGRAM 2
//    double x[100], y[100];
//    std::ifstream read_file("/Users/uqllloyd/Desktop/Output.dat");
//    std::ofstream write_output("/Users/uqllloyd/Desktop/Output2.dat");
//    assert(read_file.is_open());
//    int i=0;
//    while (!read_file.eof()) // Boolean variable that just keeps reading. Becomes true when end of file reached.
//    {
//        read_file >> x[i] >> y[i];
//        i++;
//        write_output << x[i] << "\n";
//        std::cout << x[i];
//        std::cout << y[i];
//    }
//    write_output.close();
//    read_file.close();
    //READING FROM A FILE PROGRAM 2
    //READING FROM A FILE PROGRAM 2
    
    //READING FROM A FILE PROGRAM
    //READING FROM A FILE PROGRAM
//    double x[6], y[6];
//    std::ifstream read_file("/Users/uqllloyd/Desktop/Output.dat");
//    assert(read_file.is_open());
//    for ( int i=0; i<6; i++)
//         {
//             read_file >> x[i] >> y[i];
//             std::cout << x[i];
    
//         }
//    read_file.close();
    //READING FROM A FILE PROGRAM
    //READING FROM A FILE PROGRAM
    
    //PRINTING TO A FILE PROGRAM 2-PRECISION
    //PRINTING TO A FILE PROGRAM 2-PRECISION
//    double x=1.8364238;
//    std::ofstream write_output("/Users/uqllloyd/Desktop/Output.dat");
//    
//    write_output.precision(3); // 3 sig figs
//    write_output << x << "\n";
//    
//    write_output.precision(5); // 5 sig figs
//    write_output << x << "\n";
//    
//    write_output.precision(10); // 10 sig figs
//    write_output << x << "\n";
//    write_output.close();
    
    //PRINTING TO A FILE PROGRAM 2-PRECISION
    //PRINTING TO A FILE PROGRAM 2-PRECISION
    
    
    //PRINTING TO A FILE PROGRAM 1
    //PRINTING TO A FILE PROGRAM 1
//    double x[3] = {0.0, 1.0, 0.0};
//    double y[3] = {0.0, 0.0, 1.0};
//    //std::ofstream write_output("/Users/uqllloyd/Desktop/Output.dat"); //Will write a new file
//    std::ofstream write_output("/Users/uqllloyd/Desktop/Output.dat", std::ios::app); //Will append to a file
//    assert(write_output.is_open()); //Important to establish if we have permission to write or the directory might not exists
//    //write_output << "x" << " " << "y" << "\n";
//    for ( int i=0; i<3; i++)
//    {
//        write_output << x[i] << " " << y[i] << "\n";
//    }
//    write_output.flush(); // This flushes the buffere without closing the file handle.
//    write_output.close(); //Output to file is also buffered closing the file flushes the buffer; all data that has been buffered is written to file before the computer executer any further statements
//    //This is important because if another part of the program reads a file which is still being written then we cannot be certain what data has been written to disk. Closing the file handle has the added effect that no more data can be written to this file.
    //PRINTING TO A FILE PROGRAM 1
    //PRINTING TO A FILE PROGRAM 1

    
    
    
    
// EM ALGORITHM // EM ALGORITHM // EM ALGORITHM
//    int n1=5, n2=2, n3=7, n4=5, n5=7, n6=9, k=35;
//    double T1, T2, T3, T1up, T2up, T3up, mu, sigma2a;
//    double sigma2, mu_up, sigma2a_up, sigma2_up;
//    double w[6], v[6], w_up[6], v_up[6];
//    double B1[5]={46, 31, 37, 62, 30};
//    double B2[2]={70, 59};
//    double B3[7]={52, 44, 57, 40, 67, 64, 70};
//    double B4[5]={47,21,70,46,14};
//    double B5[7]={42,64, 50,69,77,81,87};
//    double B6[9]={35, 68, 59, 38, 57, 76, 57, 29, 60};
//    
//    for (int )
    
// EM ALGORITHM// EM ALGORITHM// EM ALGORITHM
    

    //MY FIRST NEWTON RAPSON METHOD OHHH YEEEAAAHHH
    //NEWTON-RAPSON for f(x)=exp(x)+x^3-5 //
    //Updates are xi=xi-1 -f(xi-1)/f'(xi-1_
    //f'=exp(x)+3x^2
//    double xi, xip1, diff; // fxi, fdashxi;
//    xi=0;
//    xip1=0;
//    diff=10;
//    //while (xip1-xi<0.000001)
//    for (int i=1; i<100; i++)
//    //{
//    //while (diff>0.00000000001)
//    {
//        xip1=xi-((exp(xi)+pow(xi,3)-5)/(exp(xi)+3*pow(xi,2)));
//        diff=fabs(xip1-xi);
//        xi=xip1;
//        std::cout<< diff<< "\n";
//        std::cout<< xip1 << "\n";
//                 
//    }
//    std::cout<< xip1;
    //INVERT A 2X2 matrix ////INVERT A 2X2 matrix //
    //INVERT A 2X2 matrix ////INVERT A 2X2 matrix //
    //INVERT A 2X2 matrix ////INVERT A 2X2 matrix //
    //double u[3] = {1.0, 2.0, 3.0};
    //double v[3] = {6.0, 5.0, 4.0};
//    double det;
//    double A[2][2];//= {{4.0,10.0},{1.0, 1.0}};
//    double Inv[2][2];
//    //double B[3][3]= {{-2.0, 0.0, 1.0},{1.0, 0.0, 0.0},{4.0, 1.0, 0.0}};
//    //double w[3];
//    //for (int j=0; j<2; j++)
//      //  {
//        //    for (int i=0; i<2; i++)
//          //      {
//    std::cout << "Please enter the four digits of the matrix \n";
//    std::cin >> A[0][0];
//    std::cin >> A[0][1];
//    std::cin >> A[1][0];
//    std::cin >> A[1][1];
//                    det= 1/(A[0][0]*A[1][1]-A[1][0]*A[0][1]);
//                    assert((A[0][0]*A[1][1]-A[1][0]*A[0][1])!=0);
//                    //std::cout << det;
//                    Inv[0][0]=det*A[1][1];
//                    Inv[1][1]=det*A[0][0];
//                    Inv[0][1]=-det*A[0][1];
//                    Inv[1][0]=-det*A[1][0];
//                    
//            //    }
//       // }
//    std::cout << "The inverse of this matrix is \n";
//    std::cout << Inv[0][0]<< "\t" << Inv[0][1]<< "\n";
//    std::cout << Inv[1][0]<< "\t" << Inv[1][1]<< "\n";
//    //std::cout << "w=" << "\t" << w[1] << "\t" << w[2] << "\t" << w[3];    //    //
//    
    
    //SWEET LITTLE PROGRAM TO SUM A BUNCH OF NUMBERS//
//    int x, sum; //y;
//    //double aux ;// x, sum;
//    //int j;
//    std::cout << "Please enter a string of integers. When finished please enter -1";
//    sum=1;
//    while (x!=-1)
//        {
//        std::cin >> x ;
//        if (std::cin.fail())
//        {
//            std::cout << "Sorry your value is not an integer \n";
//            std::cout << "Please enter -2 to reset your sum to 0\n";
//            std::cin.clear();
//            std::cin.ignore(256,'\n');
//            std::cin >> x;
//            sum=3+x;
//            //std::cout << "Your sum so far\n";
//            //std::cout << sum-1 << "\n";
//            std::cout << "Your total has been reset to 0 please keep entering numbers\n";
//        }
//
//        else
//        {
//        sum = sum + x ;
//            //std::cout << "Your sum so far\n";
//            //std::cout << sum-1 << "\n";
//        }
//        }
//    std::cout << "Your total iiiisss ...";
//    std::cout << sum ;
//    
//        if (sum>100)
//        {
//            sum=sum-1;
//            std::cout<<"Sum is getting too large \n";
//            break;
//        }
     //SWEET LITTLE PROGRAM TO SUM A BUNCH OF NUMBERS//
    
//    if ((p<=q) && (j == 10))
//    {
//        x=1;
//    }
//    else if (p>q)
//    {
//        x=0;
//    }
//    else
//    {
//        //If p<=q and j !=10
//        x=2;
//    }
//    std::cout << x ;

//    double x = 10.0;
//    while (x>1.0)
//    {
//        //While x>1
//        x *= 0.5;
//        std::cout << x<< "\n" << "This will be printed \n";
//    }
//    int i;
//    std::cout << i << "\n";
//    i=2;
//    bool flag = false;
//    if (!flag)
//    {
//        i +=2;
//        std::cout << "This will be printed \n";
//    }
//    std::cout << i << "\n";
//    else
//    {
//        // flage is false
//        std::cout << "This won't be printed";
//    }
    // AND logical is &&
    // OR logical is ||
    // NOT logical is !
    // Equal to ==
    // Not equal to !=
    // Great than >
    // Less than <
    // Geq >=
    // Leq <=
//    double p, q, y;
//    int i;
//    std::cout << "Enter four number fucker \n" ;
//    //std::cin >> y ;
//    std::cin >> p ;
//    std::cin >> q ;
//    std::cin >> i ;
//    if ((p>q) || (i != 1))
//        {
//            //Both conditions have been met
//            y=19.0;
//        }
//    else
//    {
//        // Neither condition has been met : p<=q and i==1
//        std::cout << "Fart \n" ;
//    }
//    std::cout << y ;
////    double x;
//    int i;
//    double y;
//    std::cout << "Enter an integer \n" ;
//    std::cin >> i;
//    if (i>100.0)
//    {
//        y=2.0;
//    }
//    else if (i<0)
//    {
//        y=10.0;
//        std::cout << "Fart \n";
//    }
//    else
//    {
//        //When 0<= i <= 0.0
//        std::cout << "Fart \n";
//    }
//    std::cout << "This is your y \n";
//    std::cout << y << "\n";
//    int Cars[5]={34, 58, 57, 32, 43};
//    int Bum;
//    Bum=9.2;
//    double  AVg;
//    AVg = (((double)(Cars[0]))+((double)(Cars[1]))+((double)(Cars[2]))+((double)(Cars[3]))+((double)(Cars[4])))/5;
//    std::cout <<  Bum <<"\n";
//    std::string FirstName;
//    std::string Surname;
//    std::string Wholename;
//    std::cout <<  "Plese enter your first name \n";
//    std::cin >> FirstName;
//    std::cout <<  "Plese enter your surname \n";
//    std::cin >> Surname;
//    std::cout <<  "Your full name is \n";
//    std::cout <<  FirstName << "\t" << Surname << "\n";
//    double A[2][2]={{1.0, 2.0}, {4.0, 5.0}};
//    double B[2][2]={{1.0, 2.0}, {4.0, 5.0}};
//    double C[2][2];
//    double D[2][2];
    /**/
    //C[0][0]=A[0][0]+ B[0][0];
    //C[0][1]=A[0][1]+ B[0][1];
    //C[1][0]=A[1][0]+ B[1][0];
    //C[1][1]=A[1][1]+ B[1][1];
//    D[0][0]=A[0][0]*B[0][0];
//    D[0][1]=A[0][1]*B[0][1];
//    D[1][0]=A[1][0]*B[1][0];
//    D[1][1]=A[1][1]*B[1][1];
//    std::cout <<  "C \n";
//    std::cout <<  C[0][0] << "\t";
//    std::cout <<  C[0][1] << "\n";;
//    std::cout <<  C[1][0] << "\t";;
//    std::cout <<  C[1][1] << "\n";;
//    std::cout << "\n";;
//    std::cout <<  "D \n";
//    std::cout <<  D[0][0] << "\t";
//    std::cout <<  D[0][1] << "\n";;
//    std::cout <<  D[1][0] << "\t";;
//    std::cout <<  D[1][1] << "\n";;/**/
    /**/
    //double dotprod;
    //double Euclid1;
    //double Euclid2;
    //std::cout << "Enter a non-negative number\n";
    //std::cin >> a;
    //dotprod = array3[0]*array4[0]+ array3[1]*array4[1] +array3[2]*array4[2];
    //Euclid1 = pow(array3[0],2)+pow(array3[1],2)+pow(array3[2],2);
    //Euclid2 = pow(array4[0],2)+pow(array4[1],2)+pow(array4[2],2);
    // insert code here...
    //double array3[3]={5.0, 1.0, 2.0} ;
    //char letter;
    //letter='d';
    //std::cout<<"The character is " << letter<< "\n";
    //bool flag1, flag2;
    //flag1=true;
    //flag2=false;
    //std::cout<< flag2 << "\n";
    //double z;
    //z=2.4;
    //array1[0]=z;
    //array1[1]=z*z;
    //z=((double)(x))/((double)(y));
    //std::cout <<  array3 << "\n";
    //for (int i = 3 - 1; i >= 0; i--)
    //std::cout << array3[i]<<"\n";
    //z=atan2(y,x);
    //std::cout << z << "\n";
    //z=fabs(u);
    //std::cout << z << "\n";
    //z=exp(x);
    //std::cout << z << "\n";
    //z=pow(x,y);
    //std::cout << z << "\n";
    //z=M_PI;
    //std::cout << z << "\n";
    //int pin;
    // std::string name;
    //<< "Enter your PIN, then hit RETURN\n";
    //std::cout.flush();
//    double array3[3] = {5.0, 1.0, 2.0};
//    double array4[3] = {4.0, 3.9, 2.4};
//    double dotprod;
//    double Euclid1;
//    double Euclid2;
//    //std::cout << "Enter a non-negative number\n";
//    //std::cin >> a;
//    dotprod = array3[0]*array4[0]+ array3[1]*array4[1] +array3[2]*array4[2];
//    Euclid1 = pow(array3[0],2)+pow(array3[1],2)+pow(array3[2],2);
//    Euclid2 = pow(array4[0],2)+pow(array4[1],2)+pow(array4[2],2);
    //std::cout << array3[0]*array3[1] << "\n";
    //std::cout << array4[0]*array3[1] << "\n";
    //std::cout << "The dot product is \n";
    //std::cout << dotprod << "\n";
    //std::cout << "Euclidean norm of vector 1 \n";
    //std::cout << Euclid1 << "\n";
    //std::cout << "Euclidean norm of vector 2 \n";
    //std::cout << Euclid2 << "\n";
    //std::cin >> b;
    //assert(a>=0.0);
    //std::cout << "The product is "<< a*b;
    //std::cout << " is " <<  sqrt(a) <<"\n";
    //std::cout << "\n" ;
//    return 0;
    
    
//}

