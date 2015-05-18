// ---------------------------------------------------------------------
// Author: Luke Lloyd-Jones
// Date:
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Includes and headers
// ---------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cassert>
#include <armadillo>
#define FILEPATH "/Users/uqllloyd/Desktop/mmapped.bin"

using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{
    int fd;
    int result;
    int *map;  /* mmapped array of int's */
    
    // Get the number of individuals and number of SNPs from the fam/bim files
    
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
    
    cout << "# of individuals " << N << "\n";
    cout << "# of SNPs "        << P << "\n";
    
    // Flush the read buffer
    
    read_fam.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    read_bim.close();
    std::cout.flush();
    
    
    imat geno(N, P);
    int num_ints =  N * P;
    int num_bytes = num_ints * sizeof(int);
    
    // Read in the genotype matrix and store
    
    ifstream read_geno_file ("cape_verde_r10k_raw.txt");
    assert(read_geno_file.is_open());
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            read_geno_file >> geno(i, j);
        }
    }
    
    read_geno_file.close(); // Flush the buffer. This is important so that we don't over fill the buffer
    std::cout.flush();
    
    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmaping.
     */
    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    
    /* Stretch the file size to the size of the (mmapped) array of ints
     */
    result = lseek(fd, num_bytes - 1, SEEK_SET);
    if (result == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }
    
    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
    result = write(fd, "", 1);
    if (result != 1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }
    
    /* Now the file is ready to be mmapped.
     */
    map = (int*)mmap(0, num_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    
    /* Now write int's to the file as if it were memory (an array of ints).
     */
   // for (i = 1; i <=NUMINTS; ++i) {
   //     map[i] = 2 * i;
   // }
    
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            // cout << k << endl;
            map[k] = geno(i, j);
            k++;
        }
    }
    
    /* Don't forget to free the mmapped memory
     */
    if (munmap(map, num_bytes) == -1) {
        perror("Error un-mmapping the file");
        /* Decide here whether to close(fd) and exit() or not. Depends... */
    }
    
    /* Un-mmaping doesn't close the file, so we still need to do that.
     */
    close(fd);
    return 0;
}