//  cd_lasso.cpp
//
//  Created by Luke Lloyd-Jones on 02/05/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <fstream>
#include <sstream>
#include <ostream>
#include <array>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <iomanip>  // setprecision()
#include <string>
#include <vector>
#include <cerrno> // something to help with reading in buffers
#include <armadillo>



// Set the namespace std

using namespace std;
using namespace arma;




/************************************************************************
 ************************************************************************
 **                                                                    **
 **                    COORDINATE DESCENT LASSO                        **
 **                                                                    **
 ************************************************************************
 ************************************************************************/
                                                                                            




// MAIN COMPUTATION BLOCK
// ----------------------
// ----------------------
// ----------------------



int main(int argc, char* argv[])
{
    // Preparing some arguments
    
    std::cout << "Number of command line arguments " << argc << "\n";
    for (int i = 0; i < argc; i++)
    {
        std::cout << "Argument " << i << " = " << argv[i];
        std::cout << "\n";
    }
    
    // READ IN THE GENOTYPE AND PHENOTYPE MATRICES
    // -------------------------------------------
    // -------------------------------------------
    
    
    // GENOTYPE MATRIX
    // ---------------
    
    
    // Open the read file stream and read in the genotype matrix
    
    ifstream read_file_size (argv[1]);
    
    // Set some variables
    string line;
    int ncol = 0;
    int nrow = 0;
    
    // Get the size of the matrix stored as a text file
    
    if( !read_file_size)
    {
        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
    }
    else
    {
        while(getline(read_file_size, line)) // Get one line of the file and store as string
        {
            
            istringstream iss(line); // Make the line into a string stream
            string result;           // Make another string to store the ind elements
            ncol = 0;
            while(getline(iss, result, '\t')) // Get each element of the stream separated by space
            {
                ncol++;                       // Increment the columns
            }
            nrow++;                           // Increment the rows
            
        }
        
    }
    
    
    cout << "# of Rows in the genotype matrix " << nrow << "\n";
    cout << "# of Cols in the genotype matrix " << ncol << "\n";
    
    
    // Flush the read buffer
    
    read_file_size.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    mat geno(nrow, ncol);

    
    // Read in the genotype matrix and store
    
    ifstream read_geno_file (argv[1]);
    assert(read_geno_file.is_open());
    
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            read_geno_file >> geno(i, j);
        }
    }
    
    //cout << "First column of Geno matrix " << "\n" << geno.col(1) << "\n";
    
    // Close and flush the read buffer
    
    read_geno_file.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    // Define the variable N and P from the genoptype matrices
    int N = nrow;
    int P = ncol;
    
    // PHENOTYPE VECTOR
    // ----------------
    
    
    // Open the read file stream and read in the genotype matrix
    
    ifstream read_pheno_size(argv[2]);
    
    // Reset the number of zeros
    
    nrow = 0;
    
    // Get the size of the matrix stored as a text file
    
    if( !read_pheno_size)
    {
        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
    }
    else
    {
        while(getline(read_pheno_size,line)) // Get one line of the file and store as string
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
    cout << "# of Rows in the phenotype file " << nrow << "\n";
    cout << "# of Cols in the phenotype file " << ncol << "\n";
    
    
    
    // Close and flush the read buffer
    read_pheno_size.close(); // Flush the buffer. This is important so that we don't over fill buffer
    std::cout.flush();
    
    
    // Assign a matrix to the phenotype
    
    mat pheno(nrow, ncol);


    // Read in the phenotype matrix
    
    ifstream read_pheno(argv[2]);
    assert(read_pheno.is_open());
    
    for (int i=0; i < nrow; i++)
    {
        for (int j=0; j < ncol; j++)
        {
            read_pheno >> pheno(i, j);
        }
    }
    

    // Close and flush the read buffer
    
    read_pheno.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    // cout << "The phenotype " << "\n" << pheno.col(0) << "\n";

    // Correct geno for allele frequencies
    // (currently coded 0, 1, 2) and store in X
    
    mat X(N, P);
    
    // Build the new genotype matrix
    double q;
    for (int j = 0; j < P; j++)
    {
        q = sum(geno.col(j)) / (2.0 * N); // BE CAREFUL FOR A VECTOR 0 INDEX
        X.col(j) = (geno.col(j) - 2.0 * q) / sqrt(2.0 * q * (1.0 - q));
    }
    
    // cout << X.col(0) << endl;
    
    // Variable definition
    // -------------------
    
    double criterion = 10e-5;
    double epsilon   = 10e-8;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double dl2 = 0.0;
    double lambda = 2.0;
    double l2 = 0.0;
    double objective = 0.0;
    double penalty = 0.0;         // Pass as an argument
    double new_objective = 0.0;
    double left_l2 = 0.0;
    double left_objective = 0.0;
    double left_penalty = 0.0;
    double left_root = 0.0;
    double right_l2 = 0.0;
    double right_objective = 0.0;
    double right_penalty  = 0.0;
    double right_root = 0.0;
    mat mu_col = ones(N, P);
    X.insert_cols(0, mu_col); // Add a column of ones to the X matrix
    // cout << X.col(0) << endl;
    mat estimate(P, 1);
    mat sum_x_squares(N, 1);
    mat left_resid(P, 1);
    colvec resid(P, 1);
    mat right_resid(P, 1);
    mat Y(N, 1);
    Y = pheno;
    
    // Initialise the residual vector and penalty
    // ------------------------------------------
    // REMEMBER ZERO INDEXING - WE ARE IN C++
    
    resid = Y;
    if (abs(estimate(0, 0)) > 0.0)
      {
          resid = resid - estimate(0, 0);
      }
    for (int i = 1; i < P; i++)
        {
            a = estimate(i, 0);
            b = abs(a);
            if (b > 0.0)
            {
                resid = resid - a * X.col(i);
                penalty = penalty + b;
            }
        }
    
    // cout << resid << endl;
    // cout << penalty << endl;
    
    // Initialise the objective function and penalty
    // ---------------------------------------------
    
    l2 = sum(resid % resid); // % mean element wise multiplication
    // cout << l2 << endl;
    penalty = lambda * penalty;
    objective = l2 / 2.0 + penalty;
    
    
    // Start the main computation loop
    // -------------------------------
    
    for (int iteration = 0; iteration < 1000; iteration++)
    {
        // Update the interecept
        // ---------------------
        
        a = estimate(0, 0);
        estimate(0, 0) = a + sum(resid) / N;
        resid = resid + a - estimate(0, 0);  // Check addition of scalar to vector
        
        // Update the other regression coefficients
        // ----------------------------------------
        
        for (int i = 1; i < P; i++)
        {
          dl2 = -sum(resid % X.col(i));
          cout << dl2 << endl;
          a = estimate(i, 0);
          b = abs(a);
          if (b < epsilon)
          {
            if (dl2 + lambda >= 0.0 && -dl2 + lambda >= 0.0)
            {
              continue;
            }
          }
          // Find the root to the right of 0
          // -------------------------------
          if (sum_x_squares(i, 0) <= 0.0) 
          { 
            sum_x_squares(i, 0) = sum(X.col(i) % X.col(i));
          }
          right_root = max(a - (dl2 + lambda) / sum_x_squares(i, 0), 0.0);
          right_l2   = 0.0;
          c          = a - right_root;
          // Update the residuals to the right
          for (int j = 0; j < P; j++)
          {
            right_resid(j, 0) = resid(j, 0) + c * X(j, i);
            right_l2          = right_l2 + resid(j, 0) * resid(j, 0);
          }
          right_penalty   = penalty + lambda * (right_root - b);
          right_objective = right_l2 / 2 + right_penalty;
          // Find the root to the left of 0
          // ------------------------------
          left_root = min(a - (dl2 - lambda) / sum_x_squares(i, 0), 0.0);
          left_l2   = 0.0;
          c         = a - left_root;
          // Update the residuals to the left
          for (int j = 0; j < P; j++)
          {
            left_resid(j, 0) = resid(j, 0) + c * X(j, i);
            left_l2          = left_l2 + resid(j, 0) * resid(j, 0);
          }
          left_penalty   = penalty + lambda * (abs(left_root) - b);
          left_objective = left_l2 / 2 + left_penalty;
          # Choose between the two roots
  	      # ----------------------------
        }
  
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//
//    // WRITING ELEMENTS OF THE PROGRAM OUT
//    // -----------------------------------
//    // -----------------------------------
//    
//    
//    // Print an element to the screen to check what we are reading in
//    
//    std::cout << "First element of the A matrix: " << A[0][0] << "\n";
//    
//    
//    // Do the matrix multiplication
//    
//    //C= Multiply(A, A, nrow, ncol, nrow, ncol);
//    
//    
//    // Write the matrix result to a file
//    
//    std::ofstream write_output("/Users/hayleywise/Dropbox/Post_Doc_QBI/BayesR/Bayes_R_prog_practice/geno.raw"); //Open the write stream
//    assert(write_output.is_open());  // Make sure it's open
//    
//    for (int i=0; i<nrow; i++)
//    {
//        for (int j=0; j<ncol; j++)
//        {
//            if ((j+1)%ncol==0)
//            {
//                write_output << C[i][j] << "\n";
//            }
//            else
//            {
//                // For those not at the end of a row
//                write_output << C[i][j] << "\t";
//            }
//        }
//    }
//    
//    
//    // Close the write stream
//    
////    write_output.close();
    

    
}



