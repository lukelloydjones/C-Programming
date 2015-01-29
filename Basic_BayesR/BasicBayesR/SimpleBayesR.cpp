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
#include <iomanip>  // setprecision()
#include <string>
#include <vector>
#include <cerrno> // something to help with reading in buffers

// Probably going to need armadillo



// Set the namespace std

using namespace std;





/************************************************************************
 ************************************************************************
 **                                                                    **
 **                    BEGIN SIMPLE BAYES R                            **
 **                                                                    **
 ************************************************************************
 ************************************************************************/


// Use dynamic allocation of memory

// Function prototypes
// -------------------

double** AllocateMatrixMemory(int numRows, int numCols);                                    // Function to allocate memory dynamically
void FreeMatrixMemory(int numRows, double** matrix);                                        // Function to free dynamically allocated memory
double** Multiply(double** A, double** B, int nrowA, int ncolA, int nrowB, int ncolB);      // Function to multiply two matrices
                                                                                            // Function to multiply matrix by a vector
                                                                                            // Function to calculate the dot product of two vectors
                                                                                            // Function to draw from chi-squared
                                                                                            // Function to draw from normal distribution
                                                                                            // Function to draw from uniform may already be built in
                                                                                            // Function to sample from a Dirichlet
                                                                                            




// MAIN COMPUTATION BLOCK
// ----------------------
// ----------------------
// ----------------------



int main(int argc, char* argv[])
{
    // VARIABLE ALLOCATION
    // -------------------
    // -------------------
    
    
    // Allocate the variables that will be required in the computation
    
    double** A;
    double** C;
    int nrow=0;
    int ncol=0;
    string line;
    
    
    // READ IN THE GENOTYPE AND PHENOTYPE MATRICES
    // -------------------------------------------
    // -------------------------------------------
    
    
    // GENOTYPE MATRIX
    // ---------------
    
    
    // Open the read file stream and read in the genotype matrix
    
    ifstream read_file_size ("/Users/hayleywise/Dropbox/Post_Doc_QBI/BayesR/Bayes_R_prog_practice/geno.raw");
    
    
    // Get the size of the matrix stored as a text file
    
    if( !read_file_size)
    {
        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
    }
    else
    {
        while(getline(read_file_size,line)) // Get one line of the file and store as string
        {
            
            istringstream iss(line); // Make the line into a string stream
            string result;           // Make another string to store the ind elements
            ncol=0;
            while(getline(iss,result, ' ')) // Get each element of the stream separated by space
            {
                ncol++;                     // Increment the columns
            }
            nrow++;                         // Increment the rows
            
        }
        
    }
    
    
    // Print the number of rows and the number of columns of the matrix being read in
    
    cout << "# of Rows in the genotype matrix " << nrow << "\n";
    cout << "# of Cols in the genotype matrix " << ncol << "\n";
    
    
    // Flush the read buffer
    
    read_file_size.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    
    
    // Allocate the memory to the matrix.
    
    A= AllocateMatrixMemory(nrow,ncol);
    
    
    // Read in the data matrix
    
    ifstream read_geno_file ("/Users/hayleywise/Dropbox/Post_Doc_QBI/BayesR/Bayes_R_prog_practice/geno.raw");
    assert(read_geno_file.is_open());
    
    for (int i=0; i<nrow; i++)
    {
        for (int j=0; j<ncol; j++)
        {
            read_geno_file >> A[i][j];
            // std::cout << "ith jth element of the A matrix" << A[i][j] << "\n";
        }
    }
    
    
    // GENOTYPE MATRIX
    // ---------------
    
    
    // Open the read file stream and read in the genotype matrix
    
    ifstream read_file_size ("/Users/hayleywise/Dropbox/Post_Doc_QBI/BayesR/Bayes_R_prog_practice/geno.raw");
    
    
    // Get the size of the matrix stored as a text file
    
    if( !read_file_size)
    {
        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
    }
    else
    {
        while(getline(read_file_size,line)) // Get one line of the file and store as string
        {
            
            istringstream iss(line); // Make the line into a string stream
            string result;           // Make another string to store the ind elements
            ncol=0;
            while(getline(iss,result, ' ')) // Get each element of the stream separated by space
            {
                ncol++;                     // Increment the columns
            }
            nrow++;                         // Increment the rows
            
        }
        
    }
    
    
    // Print the number of rows and the number of columns of the matrix being read in
    
    cout << "# of Rows in the genotype matrix " << nrow << "\n";
    cout << "# of Cols in the genotype matrix " << ncol << "\n";
    
    
    // Flush the read buffer
    
    read_file_size.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    
    
    // Allocate the memory to the matrix.
    
    A= AllocateMatrixMemory(nrow,ncol);
    
    
    // Read in the data matrix
    
    ifstream read_file ("/Users/hayleywise/Dropbox/Post_Doc_QBI/BayesR/Bayes_R_prog_practice/geno.raw");
    assert(read_file.is_open());
    
    for (int i=0; i<nrow; i++)
    {
        for (int j=0; j<ncol; j++)
        {
            read_file >> A[i][j];
            // std::cout << "ith jth element of the A matrix" << A[i][j] << "\n";
        }
    }
    
    
    
    // WRITING ELEMENTS OF THE PROGRAM OUT
    // -----------------------------------
    // -----------------------------------
    
    
    // Print an element to the screen to check what we are reading in
    
    std::cout << "First element of the A matrix: " << A[0][0] << "\n";
    
    
    // Do the matrix multiplication
    
    C= Multiply(A, A, nrow, ncol, nrow, ncol);
    
    
    // Write the matrix result to a file
    
    std::ofstream write_output("/Users/hayleywise/Dropbox/Post_Doc_QBI/BayesR/Bayes_R_prog_practice/geno.raw"); //Open the write stream
    assert(write_output.is_open());  // Make sure it's open
    
    for (int i=0; i<nrow; i++)
    {
        for (int j=0; j<ncol; j++)
        {
            if ((j+1)%ncol==0)
            {
                write_output << C[i][j] << "\n";
            }
            else
            {
                // For those not at the end of a row
                write_output << C[i][j] << "\t";
            }
        }
    }
    
    
    // Close the write stream
    
    write_output.close();
    
    
    // FREEING MATRIX MEMORY
    // ---------------------
    // ---------------------
    
    
    
    // Free the matrix memory where the first integer argument is the number of rows of matrix
    
    FreeMatrixMemory(nrow, A);
    
}



// FUNCTIONS
// ---------
// ---------
// ---------


// Function to multiple two matrices


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
