// ---------------------------------------------------------------------
// Author: Luke Lloyd-Jones
// Date:
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Includes and headers
// ---------------------------------------------------------------------


#include <iostream>
//#include <algorithm>
#include <string>
//#include <vector>
//#include <set>
//#include <cmath>
//#include <functional>
using namespace std;


// ------------------------------------------------------------------------------------------
// Main
// ------------------------------------------------------------------------------------------

int main()
{
    // ask for the person's name
    std::cout << "Please enter your first name: ";
    
    // read the name
    std::string name;     // define `name'
    std::cin >> name;     // read into `name'
    
    // write a greeting
    std::cout << "Hello, " << name  << "!" << std::endl;
    return 0;
}

// Flushing output buffers at opportune moments is an important habit when
// you are writing programs that might take a long time to run. Otherwise,
// some of the program's output might languish in the system's buffers for
// long time between when your program writes it and when you see it.












