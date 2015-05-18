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
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <cmath>
#include <functional>
#include <boost/iostreams/device/mapped_file.hpp>
// using namespace boost::iostreams;
using namespace std;


// ------------------------------------------------------------------------------------------
// Main
// ------------------------------------------------------------------------------------------

//int main(int argc, char* argv[])
//{
//    
//    // Get the number of individuals and number of SNPs from the fam/bim files
//    
//    ifstream read_fam ("cape_verde_r10k.fam");
//    ifstream read_bim ("cape_verde_r10k.bim");
//    int N = 0;
//    int P = 0;
//    string line;
//    if(!read_fam || !read_bim)
//    {
//        std::cout << "ERROR: Unable to open file." << endl; //Make sure the file can be read
//    }
//    else
//    {
//        while(getline(read_fam, line)) // Get one line of the file and store as string
//        {
//            N++;
//        }
//        
//        while(getline(read_bim, line)) // Get one line of the file and store as string
//        {
//            P++;
//        }
//        
//    }
//    
//    cout << "# of individuals " << N << "\n";
//    cout << "# of SNPs "        << P << "\n";
//
//    
////    // Open the read file stream and read in the genotype matrix
//    boost::iostreams::mapped_file_source file("cape_verde_r10k_raw.txt");
//    int numberOfElements = N * P;
//    int numberOfBytes = numberOfElements * sizeof(int);
//    std::cout << file.size() << endl;
//    // file.open("cape_verde_r10k_raw.txt");
//
////    boost::iostreams::mapped_file mmap("cape_verde_r10k.bim", boost::iostreams::mapped_file::readonly);
////    auto f = mmap.const_data();
////    auto l = f + mmap.size();
////    
////    uintmax_t m_numLines = 0;
////    while (f && f!=l)
////        if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
////            m_numLines++, f++;
////    
////    std::cout << "m_numLines = " << m_numLines << "\n";
//    
//    
//    //
////    // Check if file was successfully opened
////    if(file.is_open()) {
////        boost::iostreams::filtering_streambuf< boost::iostreams::input > in;
////        in.push(boost::iostreams::gzip_decompressor());
////        in.push(file);
////        
////        std::istream std_str(&in);
////        std::string buffer;
////        while(1) {
////            std::getline(std_str, buffer);
////            if (std_str.eof()) break;
////            // do something with buffer
////        }
////    } else {
////        std::cout << "could not map the genotype file" << std::endl;
////    }
//
//    
//    return 0;
//}



//// for mmap:
//#include <sys/mman.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//
//const char* map_file(const char* fname, size_t& length);
//
//int main()
//{
//    size_t length;
//    auto f = map_file("cape_verde_r10k_raw.txt", length);
//    auto l = f + length;
//    
//    uintmax_t m_numLines = 0;
//    while (f && f!=l)
//    {
//        if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
//        {
//            std::cout << "m_numLines = " << &f << "\n";
//            m_numLines++, f++;
//        }
//    }
//    std::cout << "m_numLines = " << m_numLines << "\n";
//    std::cout << "m_numLines = " << &f << "\n";
//}
//
//void handle_error(const char* msg) {
//    perror(msg);
//    exit(255);
//}
//
//const char* map_file(const char* fname, size_t& length)
//{
//    int fd = open(fname, O_RDONLY);
//    if (fd == -1)
//        handle_error("open");
//    
//    // obtain file size
//    struct stat sb;
//    if (fstat(fd, &sb) == -1)
//        handle_error("fstat");
//    
//    length = sb.st_size;
//    
//    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
//    if (addr == MAP_FAILED)
//        handle_error("mmap");
//    
//    // TODO close fd at some point in time, call munmap(...)
//    return addr;
//}



#include <boost/spirit/include/qi.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <chrono>

namespace qi = boost::spirit::qi;

typedef std::vector<uint32_t> data_t;

using hrclock = std::chrono::high_resolution_clock;

int main(int argc, char** argv) {
    data_t data;
    int numberOfBytes = 684*10000 * sizeof(int);
    data.reserve(numberOfBytes);   // for the  45 GiB file benchmark
    // data.reserve(402653284); // for the 4.5 GiB file benchmark
    
    boost::iostreams::mapped_file mmap("/Users/uqllloyd/Dropbox/Git_Repos/CPP_Programming/CL_Compiling/Mem_Map/cape_verde_r10k_raw.txt", boost::iostreams::mapped_file::readonly);
    auto f = mmap.const_data();
    auto l = f + mmap.size();
    
    using namespace qi;
    
    auto start_parse = hrclock::now();
    bool ok = phrase_parse(f,l,int_parser<uint32_t, 10>() % eol, blank, data);
    auto stop_time = hrclock::now();
    
    if (ok)
        std::cout << "Parse success\n";
    else
        std::cerr << "Parse failed at #" << std::distance(mmap.const_data(), f) << " around '" << std::string(f,f+50) << "'\n";
    
    if (f!=l)
        std::cerr << "Trailing unparsed: " << std::distance(f,l) << " characters\n";
    
    std::cout << "Data.size():   " << data.size() << "\n";
    std::cout << "Time taken by parsing: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop_time-start_parse).count() / 1000.0 << "s\n";
}



