#include <cmath>
#include <cassert>
#include "LinearSystem.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

// Copy matrix and vector so that original matrix and vector
// specified are unchanged by Gaussian elimination
LinearSystem::LinearSystem(const Matrix& A, const Matrix& b)
{
   // check matrix and vector are of compatible sizes
   int local_size = A.GetNumberOfColumns();
   assert(A.GetNumberOfColumns() == local_size);
   assert(b.GetNumberOfRows() == local_size);

   // set variables for linear system
   mSize = local_size;
   mpA = new Matrix(A);
   mpb = new Matrix(b);
}

// Destructor to free memory
LinearSystem::~LinearSystem()
{
   delete mpA;
   delete mpb;
}

// Methods to get private elements

int LinearSystem::GetSize() const
{
    return mSize;
}

Matrix LinearSystem::GetInputMatrix() const
{
     return *mpA;
}

Matrix LinearSystem::GetInputVector() const
{
     return *mpb;
}

void LinearSystem::SetSize(int i)
{
    mSize = i;
}

void LinearSystem::SetInputMatrix(Matrix& A)
{
    mpA = &A;
}

void LinearSystem::SetInputVector(Matrix& b)
{
    mpA = &b;
}

// Solve linear system using Gaussian elimination
// This method changes the content of the matrix mpA
Matrix LinearSystem::Solve()
{
   Matrix m(mSize, 1); //See description in Appendix A
   Matrix solution(mSize, 1);

   // We introduce references to make the syntax readable   
   Matrix& rA = *mpA; //NB not reference in published version
   Matrix& rb = *mpb; //NB not reference in published version

   // forward sweep of Gaussian elimination
   for (int k = 0; k < mSize - 1; k++)
   {
      // see if pivoting is necessary
      double max = 0.0;
      int row = -1;
      for (int i = k; i < mSize; i++)
      {
         if (fabs(rA(i + 1, k + 1)) > max)
         {
            row = i;
            max=fabs(rA(i + 1, k + 1)); //NB bug in published version
         }
      }
      assert(row >= 0); //NB bug in published version

      // pivot if necessary
      if (row != k)
      {
         // swap matrix rows k+1 with row+1
         for (int i = 0; i< mSize; i++)
         {
            double temp = rA(k + 1, i + 1);
            rA(k + 1, i + 1) = rA(row + 1, i + 1);
            rA(row + 1, i + 1) = temp;
         }
         // swap vector entries k+1 with row+1    
         double temp = rb(k + 1, 1);
         rb(k + 1, 1) = rb(row + 1, 1);
         rb(row + 1, 1) = temp;
      }

      // create zeros in lower part of column k
      for (int i = k + 1; i < mSize; i++)
      {
         m(i + 1, 1) = rA(i + 1, k + 1) / rA(k + 1, k + 1);
         for (int j = k; j < mSize; j++)
         {
            rA(i + 1, j + 1) -= rA(k + 1, j + 1) * m(i + 1, 1);
         }
         rb(i + 1, 1) -= rb(k + 1, 1) * m(i + 1, 1);
      }
   }

   // back substitution
   for (int i = mSize - 1; i>-1; i--)
   {
      solution(i + 1, 1) = rb(i + 1, 1);
      for (int j = i + 1; j < mSize; j++)
      {
         solution(i + 1, 1) -= rA(i + 1, j + 1) * solution(j + 1, 1);
      }
      solution(i + 1, 1) /= rA(i + 1, i + 1);
   }

   return solution;
}

