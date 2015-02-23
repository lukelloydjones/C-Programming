#include <cmath>
#include <cassert>
#include "Matrix.hpp"
#include "Vector.hpp"


// Overwritten copy constructor
// Allocate memory for new matrix, and copy
// entries into this matrix
Matrix::Matrix(const Matrix& otherMatrix)
{
    mNumRows = otherMatrix.mNumRows;
    mNumCols = otherMatrix.mNumCols;
    // Memory allocation
    mData = new double* [mNumRows];
    for (int i=0; i<mNumRows; i++)
    {
        mData[i] = new double [mNumCols];
    }
    // Copying
    for (int i=0; i < mNumRows; i++)
    {
        for (int j=0; j < mNumCols; j++)
        {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
}

// Constructor for matrix of a given size
// Allocates memory, and initialises entries
// to zero

Matrix::Matrix(int numRows, int numCols)
{
    assert(numRows > 0);
    assert(numCols > 0);
    mNumRows = numRows;
    mNumCols = numCols;
    mData = new double* [mNumRows];
    // Memory allocation
    for (int i=0; i< mNumRows; i++)
    {
        mData[i] = new double [mNumCols];
    }
    // Initialise to 0
    for (int i=0; i < mNumRows; i++)
    {
        for (int j=0; j < mNumCols; j++)
        {
            mData[i][j] = 0.0;
        }
    }
}

// Overwritten destructor to correctly free memory

Matrix::~Matrix()
{
    for (int i=0; i< mNumRows; i++)
    {
        delete[] mData[i];
    }
    delete[] mData;
}

// Method to get number of rows of matrix
int Matrix::GetNumberOfRows() const
{
    return mNumRows;
}

// Method to get number of columns of matrix
int Matrix::GetNumberOfColumns() const
{
    return mNumCols;
}

// Overloading the round brackets
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
double& Matrix::operator()(int i, int j)
{
    assert(i > 0);
    assert(i < mNumRows + 1);
    assert(j > 0);
    assert(j < mNumCols + 1);
    return mData[i - 1][j - 1];
}

// Overloading the assignment operator
Matrix& Matrix::operator = (const Matrix& otherMatrix)
{
    assert(mNumRows = otherMatrix.mNumRows);
    assert(mNumCols = otherMatrix.mNumCols);
    
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
    return *this;
}

// Overloading the unary + operator with round brackets
Matrix Matrix::operator+() const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mat(i + 1,j + 1) = mData[i][j];
        }
    }
    return mat;
}

// Overloading the unary - operator
Matrix Matrix::operator-() const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mat(i + 1,j + 1) = -mData[i][j];
        }
    }
    return mat;
}

// Overloading the binary + operator
Matrix Matrix::operator+(const Matrix& m1) const
{
    assert(mNumRows == m1.mNumRows);
    assert(mNumCols == m1.mNumCols);
    Matrix mat(mNumRows, mNumCols);
    for (int i = 0; i<mNumRows; i++)
    {
        for (int j = 0; j<mNumCols; j++)
        {
            mat(i + 1,j + 1) = mData[i][j] + m1.mData[i][j];
        }
    }
    return mat;
}

// Overloading the binary - operator
Matrix Matrix::operator-(const Matrix& m1) const
{
    assert(mNumRows == m1.mNumRows);
    assert(mNumCols == m1.mNumCols);
    Matrix mat(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mat(i + 1,j + 1) = mData[i][j] - m1.mData[i][j];
        }
    }
    return mat;
}

// Overloading scalar multiplication
Matrix Matrix::operator*(double a) const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mat(i + 1,j + 1) = a * mData[i][j];
        }
    }
    return mat;
}

// Overloading matrix multiplied by a vector
Vector operator*(const Matrix& m, const Vector& v)
{
    int original_vector_size = v.GetSize();
    assert(m.GetNumberOfColumns() == original_vector_size);
    int new_vector_length = m.GetNumberOfRows();
    Vector new_vector(new_vector_length);
    
    for (int i=0; i<new_vector_length; i++)
    {
        for (int j=0; j<original_vector_size; j++)
        {
            new_vector[i] += m.mData[i][j]*v.Read(j, v);
        }
    }
    
    return new_vector;
}

//// Overloading vector multiplied by a matrix
Vector operator*(const Vector& v, const Matrix& m)
{
    int original_vector_size = v.GetSize();
    assert(m.GetNumberOfRows() == original_vector_size);
    int new_vector_length = m.GetNumberOfColumns();
    Vector new_vector(new_vector_length);
    
    for (int i=0; i<new_vector_length; i++)
    {
        for (int j=0; j<original_vector_size; j++)
        {
            new_vector[i] += v.Read(j, v)*m.mData[j][i];
        }
    }
    
    return new_vector;
}

//// Overloading element wise matrix multiplication
Matrix operator*(const Matrix& X, const Matrix& Y)
{
    Matrix new_matrix(Y.GetNumberOfRows(), Y.GetNumberOfColumns());

    // If statement for scalar wise matrix multiplication i.e.,
    // multiplcation by a 1x1 matrix
    
    if (X.GetNumberOfRows() == 1 & X.GetNumberOfColumns() == 1)
    {
        for (int i=0; i < Y.GetNumberOfRows(); i++)
        {
            for (int j=0; j <  Y.GetNumberOfColumns(); j++)
            {
              new_matrix(i + 1, j + 1) = X.mData[0][0] * Y.mData[i][j];
            }
        }
    }
    else
    {
        // If not scalar
      assert(X.GetNumberOfRows() == Y.GetNumberOfRows());
      assert(X.GetNumberOfColumns() == Y.GetNumberOfColumns());
    
      for (int i=0; i < X.GetNumberOfRows(); i++)
      {
        for (int j=0; j <  X.GetNumberOfColumns(); j++)
        {
          new_matrix(i + 1, j + 1) = X.mData[i][j] * Y.mData[i][j];
        }
      }
    }
    return new_matrix;
}




// Calculate determinant of square matrix recursively
double Matrix::CalculateDeterminant() const
{
    assert(mNumRows == mNumCols);
    double determinant = 0.0;
    
    if (mNumRows == 1)
    {
        determinant = mData[0][0];
    }
    else
    {
        // More than one entry of matrix
        for (int i_outer=0; i_outer<mNumRows; i_outer++)
        {
            Matrix sub_matrix(mNumRows-1,
                              mNumRows-1);
            for (int i=0; i<mNumRows-1; i++)
            {
                for (int j=0; j<i_outer; j++)
                {
                    sub_matrix(i+1,j+1) = mData[i+1][j];
                }
                for (int j=i_outer; j<mNumRows-1; j++)
                {
                    sub_matrix(i+1,j+1) = mData[i+1][j+1];
                }
            }
            double sub_matrix_determinant =
            sub_matrix.CalculateDeterminant();
            
            determinant += pow(-1.0, i_outer)*
            mData[0][i_outer]*sub_matrix_determinant;
        }
    }
    return determinant;
}

// Calculate the norm of a column vector

double Matrix::CalculateNorm(int p)
{
    
    double norm_val, sum = 0.0;
    for (int i = 0; i < mNumRows; i++)
    {
        sum += pow(fabs(mData[i][0]), p);
    }
    
    norm_val = pow(sum, 1.0 / ((double)(p)));
    return norm_val;
}

// Matrix multiplication of two matrices

Matrix Multiply(const Matrix& X, const Matrix& Y)
{
    // Check the dimensions and create a new matrix
    
    assert(X.GetNumberOfColumns() == Y.GetNumberOfRows());
    Matrix new_matrix(X.GetNumberOfRows(), Y.GetNumberOfColumns());
    
    //Calculate the elements of Matrix as the sum of the product of the elements in A and B
    
    for (int i = 0; i < X.GetNumberOfRows(); i++)
    {
        for (int j = 0; j <  Y.GetNumberOfColumns(); j++)
        {
            double temp = 0;
            for (int k = 0; k < Y.GetNumberOfRows(); k++)
            {
                temp += X.mData[i][k] * Y.mData[k][j];

            }
            new_matrix(i + 1, j + 1) = temp;
            
        }
    }

    return new_matrix;
}

// Method to take the transpose of a matrix

Matrix Transpose(const Matrix& X)
{
    Matrix new_matrix(X.GetNumberOfColumns(), X.GetNumberOfRows());
    
    for (int i = 0; i < X.GetNumberOfRows(); i++)
    {
        for (int j = 0; j < X.GetNumberOfColumns(); j++)
        {
            new_matrix.mData[j][i] = X.mData[i][j];
        }
    }
    
    return new_matrix;
}

    
// Method to overload the insertion operator to print a matrix

std::ostream& operator<<(std::ostream& output, const Matrix& X)
{
    //output << X.GetNumberOfRows() << ' ' << X.GetNumberOfColumns() << '\n';
    for (int i = 0; i < X.GetNumberOfRows(); ++i)
    {
        for (int j = 0; j < X.GetNumberOfColumns(); ++j)
        {
          output << X.mData[i][j] << "  ";
            
        }
      output << std::endl;
    }
    return output;
}


// Element wise devision

Matrix operator/(const Matrix& X, const Matrix& Y)
{
    assert(X.GetNumberOfRows() == Y.GetNumberOfRows());
    assert(X.GetNumberOfColumns() == Y.GetNumberOfColumns());
    Matrix new_matrix(X.GetNumberOfRows(), X.GetNumberOfColumns());
        
    for (int i=0; i < X.GetNumberOfRows(); i++)
    {
        for (int j=0; j <  X.GetNumberOfColumns(); j++)
        {
            new_matrix(i + 1, j + 1) = X.mData[i][j] / Y.mData[i][j];
        }
    }
        
  return new_matrix;

}



