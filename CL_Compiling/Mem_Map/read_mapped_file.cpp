// ---------------------------------------------------------------------
// Author: Luke Lloyd-Jones
// Date:
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Includes and headers
// ---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <armadillo>
#include <time.h>

using namespace std;
using namespace arma;

#define FILEPATH "/Users/uqllloyd/Desktop/mmapped.bin"
int main(int argc, char *argv[])
{
    clock_t t1, t2;
    t1 = clock();
    int fd;
    int *map;  /* mmapped array of int's */
    
    ifstream read_fam ("cape_verde_r10k.fam");
    ifstream read_bim ("cape_verde_r10k.bim");
    int N = 0;
    int P = 0;
    string line;
    if(!read_fam || !read_bim)
    {
        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
    }
    else
    {
        while(getline(read_fam, line)) // Get one line of the file and store as string
        {
            N++;
        }
        
        while(getline(read_bim, line)) // Get one line of the file and store as string
        {
            P++;
        }
        
    }
    
    // Flush the read buffer
    
    cout << "# of individuals " << N << "\n";
    cout << "# of SNPs "        << P << "\n";
    
    read_fam.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    read_bim.close();
    std::cout.flush();
    
    // The number of elements is N*P
    
    int num_ints = N * P;
    int num_bytes = num_ints * sizeof(int);
    
    fd = open(FILEPATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    
    map = (int*)mmap(0, num_bytes, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    
    /* Read the file int-by-int from the mmap
     */
//    for (i = 1; i <= num_ints; ++i) {
//        cout << map[i] << "\n";
//    }
    
    imat geno(N, P);
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            geno(i, j) = map[k];
            k++;
        }
    }
    
    cout << "We have read the file and built the genotypes" << endl;
    
    
    
    if (munmap(map, num_bytes) == -1) {
        perror("Error un-mmapping the file");
    }
    close(fd);
    
    
    t2 = clock();
    float diff ((float)t2 - (float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "File IO time took " << seconds << " seconds" << endl;
    
    
    return 0;
}


