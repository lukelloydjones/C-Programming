//
//  Simple_Bayes_R.cpp
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
#include <ostream>
#include <array>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <iomanip>  // setprecision()
#include <string>
#include <vector>
#include <cerrno> // something to help with reading in buffers
#include "/usr/include/armadillo"

// Probably going to need armadillo



// Set the namespace std

using namespace std;
using namespace arma;




/************************************************************************
 ************************************************************************
 **                                                                    **
 **                    BEGIN SIMPLE BAYES R                            **
 **                                                                    **
 ************************************************************************
 ************************************************************************/
                                                                                            




// MAIN COMPUTATION BLOCK
// ----------------------
// ----------------------
// ----------------------



int main(int argc, char* argv[])
{

    
    
    // READ IN THE GENOTYPE AND PHENOTYPE MATRICES
    // -------------------------------------------
    // -------------------------------------------
    
    
    // GENOTYPE MATRIX
    // ---------------
    
    
    // Open the read file stream and read in the genotype matrix
    
    ifstream read_file_size ("/Users/uqllloyd/Dropbox/Git_Repos/CPP_Programming/Basic_BayesR/R_Code_Data/M500_N100_GA1.raw");
    
    // Set some variables
    string line;
    int ncol;
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
            while(getline(iss, result, ' ')) // Get each element of the stream separated by space
            {
                ncol++;                      // Increment the columns
            }
            nrow++;                          // Increment the rows
            
        }
        
    }
    
    
    cout << "# of Rows in the genotype matrix " << nrow << "\n";
    cout << "# of Cols in the genotype matrix " << ncol << "\n";
    
    
    // Flush the read buffer
    
    read_file_size.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    mat geno(nrow, ncol);

    
    // Read in the genotype matrix and store
    
    ifstream read_geno_file ("/Users/uqllloyd/Dropbox/Git_Repos/CPP_Programming/Basic_BayesR/R_Code_Data/M500_N100_GA1.raw");
    assert(read_geno_file.is_open());
    
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            read_geno_file >> geno(i, j);
        }
    }
    
    cout << "# of Rows in the genotype matrix " << geno.col(1) << "\n";
    
    // Close and flush the read buffer
    
    read_geno_file.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    
    // PHENOTYPE VECTOR
    // ----------------
    
    
    // Open the read file stream and read in the genotype matrix
    
    ifstream read_pheno_size("/Users/uqllloyd/Dropbox/Git_Repos/CPP_Programming/Basic_BayesR/R_Code_Data/M500_N100_GA1.phen");
    
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
    
    read_pheno_size.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    
    // Assign a matrix to the phenotype
    
    mat pheno(nrow, ncol);


    // Read in the phenotype matrix
    
    ifstream read_pheno("/Users/uqllloyd/Dropbox/Git_Repos/CPP_Programming/Basic_BayesR/R_Code_Data/M500_N100_GA1.phen");
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
    
    
    // Define the phenotype to be the third column of the larger pheno matrix
    
    mat Y(nrow, 1);
    Y = pheno.col(2);
    cout << "pheno.col(3): " << endl << Y << endl;
    
    
    // Set some integer parameters
    
    int numit = 50000;			// Number of iterations
    int burn  = 10000;			// Number of iterations which are burn in
    int ndist = 4;  			// Number of normal distributions to model
    int seeds = 222;			// Seed used
    int ninds = Y.n_rows;       // Number of individuals
    
    // Print how many individuals there are
    cout << "How many inds? " << ninds << endl;
    
    
    // Correct geno for allele frequencies
    // (currently coded 0,1,2) and store in X
    
    mat X(geno.n_rows, geno.n_cols);
    mat temp(1, geno.n_cols);
    
        
    // Calculate the allele frequencies
    
    temp = (1.0 / (2.0 * ninds)) * sum(geno);
    cout << temp << endl;
    
    // Build the new genotype matrix
    
    for (int j = 0; j < geno.n_cols; j++) {
    
        double q = temp(0, j); // BE CAREFUL FOR A VECTOR 0 INDEX
        X.col(j) = (geno.col(j) - 2.0 * q) / sqrt(2.0 * q * (1.0 - q));
    }
    
    cout << X.col(1) << endl;
    
    
    
    
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



