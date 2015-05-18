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
#include <time.h>


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
    
    clock_t t1, t2, t3, t4;
    t1 = clock();
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
            while(getline(iss, result, ',')) // Get each element of the stream separated by space
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
    
    mat X(nrow, ncol);
    X.load(argv[1], csv_ascii);
    
//    // Read in the genotype matrix and store
//    
//    ifstream read_geno_file (argv[1]);
//    assert(read_geno_file.is_open());
//    
//    for (int i = 0; i < nrow; i++)
//    {
//        for (int j = 0; j < ncol; j++)
//        {
//            read_geno_file >> geno(i, j);
//        }
//    }
//    
//    //cout << "First column of Geno matrix " << "\n" << geno.col(1) << "\n";
//    
//    // Close and flush the read buffer
//    
//    read_geno_file.close(); // Flush the buffer. This is important so that we don't over fill the buffer
//    std::cout.flush();
    

    
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
    int N = X.n_rows;
    int P = X.n_cols;
    char geno_adjust = atoi(argv[3]);;
    // Build the new genotype matrix
    if (geno_adjust == 1)
    {
      double q;
      for (int j = 0; j < P; j++)
      {
        q = sum(X.col(j)) / (2.0 * N); // BE CAREFUL FOR A VECTOR 0 INDEX
        X.col(j) = (X.col(j) - 2.0 * q) / sqrt(2.0 * q * (1.0 - q));
      }
    } else
    {
        X = X;
    }
    // delete geno;
    // cout << X.col(0) << endl;
    t2 = clock();
    float diff ((float)t2 - (float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "File IO time took " << seconds << " seconds" << endl;
    
    // Variable definition
    // -------------------
    t3 = clock();
    double criterion = 10e-5;
    double epsilon   = 10e-8;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double dl2 = 0.0;
    double lambda = 20.0;
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
    mat mu_col = ones(N, 1);
    X.insert_cols(0, mu_col); // Add a column of ones to the X matrix
    // cout << X.col(0) << endl;
    mat estimate(P, 1);
    mat sum_x_squares(P, 1);
    colvec left_resid(N, 1);
    colvec resid(N, 1);
    colvec right_resid(N, 1);
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
    penalty = lambda * penalty;
    objective = l2 / 2.0 + penalty;
    
    //cout << "Initial objective " <<  objective << endl;
    //cout << "Initial penalty "   <<  penalty << endl;
    
    // Start the main computation loop
    // -------------------------------
    
    for (int iteration = 0; iteration < 1000; iteration++)
    {
        // Update the interecept
        // ---------------------
        
        a = estimate(0, 0);
        estimate(0, 0) = a + sum(resid) / N;
        resid = (a - estimate(0, 0)) + resid;  // Check addition of scalar to vector
    
        //cout << "a line 309 " <<  a << endl;
        //cout << "intercept "   <<  estimate(0, 0) << endl;
        //cout << "resid line 311 "   <<  resid << endl;

        // Update the other regression coefficients
        // ----------------------------------------
        
        for (int i = 1; i < P; i++)
        {
            dl2 = -sum(resid % X.col(i));
            a = estimate(i, 0);
            b = abs(a);
            //cout << dl2 << endl;
            //cout << -dl2 << endl;
             //cout << a << endl;
             //cout << b << endl;
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
          // cout << "sum_x_sqr_i" << sum_x_squares(i, 0) << endl;
          right_root = max(a - (dl2 + lambda) / sum_x_squares(i, 0), 0.0);
          // cout << "right_root " << right_root << endl;
          right_l2   = 0.0;
          c          = a - right_root;
          // Update the residuals to the right
          for (int j = 0; j < N; j++)
          {
            right_resid(j) = resid(j) + c * X(j, i);
            // cout << j << resid(j) + c * X(j, i) << endl;
            right_l2       = right_l2 + right_resid(j)  * right_resid(j);
          }
          right_penalty   = penalty + lambda * (right_root - b);
          //cout << "right penalty " << right_penalty << endl;
          //cout << "right l2 " << right_l2 << endl;
          right_objective = right_l2 / 2.0 + right_penalty;
          //cout << "Right pen " << right_penalty << endl;
          //c/out << "Right obj " << right_objective << endl;
          //cout << "Right residual " << right_resid << endl;
          // Find the root to the left of 0
          // ------------------------------
          left_root = min(a - (dl2 - lambda) / sum_x_squares(i, 0), 0.0);
          left_l2   = 0.0;
          c         = a - left_root;
          // Update the residuals to the left
          for (int j = 0; j < N; j++)
          {
            left_resid(j) = resid(j) + c * X(j, i);
            left_l2       = left_l2 + left_resid(j) * left_resid(j);
          }
          left_penalty   = penalty + lambda * (abs(left_root) - b);
          left_objective = left_l2 / 2.0 + left_penalty;
          //cout << "Left pen " << left_penalty << endl;
          //cout << "Left obj " << left_objective << endl;
          // Choose between the two roots
          // ----------------------------
          if (right_objective <= left_objective)
          {
              resid          = right_resid;
              estimate(i, 0) = right_root;
              l2             = right_l2;
              penalty        = right_penalty;
          } else
          {
              resid          = left_resid;
              estimate(i, 0) = left_root;
              l2             = left_l2;
              penalty        = left_penalty;
          }
         // cout << resid << endl;
         //cout << estimate(i, 0) << endl;
         //cout << l2 << endl;
         //cout << penalty << endl;
         }


        // Update objective function
        //cout << objective << endl;
        new_objective = l2 / 2.0 + penalty;
        //cout << new_objective << endl;
        // Check for descent failure or convergence. If neither occurs,
        // record the new value of the objective function
        cout << "Objective difference " << objective - new_objective << endl;
        if (new_objective > objective)
        {
            cout << "*** ERROR *** OBJECTIVE FUNCTION INCREASE" << endl;
            exit(1);
        }
        if (objective - new_objective < criterion)
        {
            cout << new_objective << endl;
            // cout << estimate << endl;
            cout << "We have convergence" << endl;
            // Write the estimated betas to a file
            
            std::ofstream write_output("/Users/uqllloyd/Desktop/cd_lasso_estimates.txt"); //Open the write stream
            assert(write_output.is_open());  // Make sure it's open
            
            for (int i = 0; i < P; i++)
            {
                write_output << estimate(i, 0) << "\n";
                //cout << "We are in the write loop" << endl;
            }
            
            // Close the write stream
            
            write_output.close();
            t4 = clock();
            float diff ((float)t4 - (float)t3);
            float seconds = diff / CLOCKS_PER_SEC;
            cout << "Time to estimate lasso parameters was " << seconds << " seconds" << endl;
            exit(0);
            
        } else
        {
            objective = new_objective;
            cout << new_objective << endl;
        }

    }
    
}



