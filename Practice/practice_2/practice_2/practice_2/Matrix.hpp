#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"

class Matrix
{
private:
    double** mData; // entries of matrix
    int mNumRows, mNumCols; // dimensions
public:
    Matrix(const Matrix& otherMatrix);
    Matrix(int numRows, int numCols);
    ~Matrix();
    int GetNumberOfRows() const;
    int GetNumberOfColumns() const;
    double& operator()(int i, int j); //1-based indexing
    //overloaded assignment operator
    Matrix& operator=(const Matrix& otherMatrix);
    Matrix operator+() const; // unary +
    Matrix operator-() const; // unary -
    Matrix operator+(const Matrix& m1) const; // binary +
    Matrix operator-(const Matrix& m1) const; // binary -
    // scalar multiplication
    Matrix operator*(double a) const;
    double CalculateDeterminant() const;
    friend Matrix Multiply(const Matrix& X, const Matrix& Y);
    friend Matrix Transpose(const Matrix& X);
    // declare vector multiplication friendship
    friend Vector operator*(const Matrix& m,
                            const Vector& v);
    friend Vector operator*(const Vector& v,
                            const Matrix& m);
    friend Matrix operator*(const Matrix& X,
                            const Matrix& Y); // Element wise multiplication
    friend Matrix operator/(const Matrix& X,
                            const Matrix& Y); // Element wise devision
    friend std::ostream& operator<<(std::ostream& output, const Matrix& X);
    double CalculateNorm(int p = 2) const; // p-2-norm method
    
};
// prototype signatures for friend operators
Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);
Matrix operator*(const Matrix& X, const Matrix& Y);
Matrix operator/(const Matrix& X, const Matrix& Y); // Element wise devision
Matrix Multiply(const Matrix& X, const Matrix& Y);
Matrix Transpose(const Matrix& X);
std::ostream& operator<<(std::ostream& output, const Matrix& X);

#endif
