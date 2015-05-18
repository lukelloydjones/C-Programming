// ---------------------------------------------------------------------
// Author: Luke Lloyd-Jones
// Date:
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Includes and headers
// ---------------------------------------------------------------------


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <functional>



// ------------------------------------------------------------------------------------------
// Main
// ------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
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











