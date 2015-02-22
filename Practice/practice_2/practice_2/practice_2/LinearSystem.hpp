#ifndef LINEARSYSTEMHEADERDEF
#define LINEARSYSTEMHEADERDEF
#include "Vector.hpp"
#include "Matrix.hpp"

class LinearSystem
{

private:
   int mSize; // size of linear system
   Matrix* mpA;  // matrix for linear system
   Matrix* mpb;  // vector for linear system

   // Only allow constructor that specifies matrix and 
   // vector to be used.  Copy constructor is private.
   LinearSystem(const LinearSystem& otherLinearSystem){};
public:
   LinearSystem(const Matrix& A, const Matrix& b);

   // destructor frees memory allocated
   ~LinearSystem();

   // Functions to get private elemetns
   
    int GetSize() const;
    Matrix GetInputMatrix() const;
    Matrix GetInputVector() const;

   // Functions to set private elements
    
    void SetSize(int i);
    void SetInputMatrix(Matrix& A);
    void SetInputVector(Matrix& b);
    
   // Method for solving system
   virtual Matrix Solve();
    
   // The virtual keyword is a signal to the compiler that a method
   // does different things for different derived classes. For different
   // derived classes you can overide it to do different things
};

#endif

