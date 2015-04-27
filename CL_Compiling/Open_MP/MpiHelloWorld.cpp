// ---------------------------------------------------------------------
// Author: Luke Lloyd-Jones
// Date: 20/03/2015
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Includes and headers
// ---------------------------------------------------------------------

#include <mpi.h>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <functional>

//#include <scythestat/algorithm.h>
//#include "scythestat/defs.h"
//#include "scythestat/matrix.h"
//#include "scythestat/rng.h"
//#include "scythestat/algorithm.h"
//#include "scythestat/defs.h"
//#include "scythestat/rng.h"
//#include "scythestat/distributions.h"
//#include "scythestat/matrix.h"
//#include "scythestat/matrix_random_access_iterator.h"

// ------------------------------------------------------------------------------------------
// Main
// ------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Testing MPI
    
    MPI::Init(argc, argv); // Start the parallel process
    int num_procs = MPI::COMM_WORLD.Get_size(); // Number of processes
    int rank = MPI::COMM_WORLD.Get_rank(); // Identifies the process executing
    // a given statement
    std::cout << "Hello world from process " << rank
    << " of " << num_procs << "\n";
    MPI::Finalize();  // Stop the parallel process
    
    // Testing boost
    
//    using namespace boost::lambda;
//    typedef std::istream_iterator<int> in;
//    
//    std::for_each(
//                  in(std::cin), in(), std::cout << (_1 * 3) << " " );
    
    return 0;
}

// All the calls to MPI in the program above used calls to specific C++ bindings in the
// MPI library. 'Finalise' if a fucntion in the MPI namespaceand Get_size is a method of
// communication object COMM_WORLD. Some people don't like these and use the plain
// C function MPI_Init, MPI_Get_size

// Essential MPI functions
// -----------------------

// MPI::Init and MPI::Finalize are required in any MPI program. Promotes the program
// from a single executable to a parallel program running as several processes. If you
// want MPI program to read some specific arguments from the command-line for use in
// your calculation the best place to do this is after MPI::Init because the MPI-
// specific arguments have been read and updated as necessary

// MPI::Finalize makes sure that the program closes down neatly

// Compiling and Running MPI code
// ------------------------------

// MPI is not part of the standard C++ libraries. Normally when you compile against a
// third party library you need to included extra compiler flags specific to the
// location of the header files, the location of the libraries themselves, and the
// names if some of the library dependencies. Probably use the wrapper bianry
// mpic++.

// To run in parallel either on the same machine or across a network or cluster
// use the mpirun command. This will if necessary launch a service on all the
// machine involved in the calculation. It will then make sure that copies of
// the executable can be run on every machine. To run the program locally us the
// number of processes flag -np.

// To run the program across a network you can give a list of machines in a host
// file or alternatively list the machine names on the command line. It is
// essential that you have an account on the remote machines that you are able
// to connect via ssh and that the machines have the same MPI implementation installed
// on them and that they are capable of running the executable file that you are
// sending. In the example ranks 0 and 2 of a 3 process job are launched on remote
// machines. The rank 1 process will run on the local machine, from where the job has
// been launched. Buffered output from the local machine has appeared on the screen
// before output that has been sent from the remote machines.

// If you are running your program on a large cluster the is it likely that the program
// will be launched from a script via a queueing system. In this case, the locations of the
// processors available to you will be determined buy the job queue manager. Need to sort
// this out if with the system itself if you want to get this running.

// 11.4 Basic MPI Communication
// ----------------------------

// The parallel Hello World program used the MPI libraries it did not make any use of the
// communication features offered by these libraries. More specifically, it did not do any
// message passing, which is the main feature of MPI.

// 11.4.1 Point-to-Point Communication

// The essential part of MPI functionality if being able to send a single message between
// processes, where one process sends while another process receives. The two functions are
// denoted Send and Recv. Their function prototypes are:

void::Send(const void* buf, int count, const Datatype& datatype, int dest, int tag) const
void::Recv(void* buf, int count, const Datatype& datatype, int source, int tag) const

// The Send method takes data on the current process from the location given by the pointer
// buf. These data are assumed to be in contiguous memory (share a common border) as an
// array of count variables. However, buf may be a pointer to a single variable. Note that the
// const keyword next to the buffer argument: MPI is making a guarantee not to alter your data
// during the message sending. The datatype field tells the system what the type of the data
// is (so that the correct number of bytes are sent in the correct format). The last two
// arguments of the Send method give the destination process number (this is the rank of the
// process we wusg to send t) and a tag. The message tag can be any nonnegative integer value
// and its purpose is to allow the user to easily identify the context of a message.

// The Recv method has the same basic arguments: a pointer to a buffer in which to store the
// message, an integer count that gives the expected number of items in the message, the data
// type for these items, the ranke of the source process which is sending the message and the
// tag value of a message. The receiver is allowed to use wild-cards for either the source of
// the message, the message tag, or both. the wild card MPI::ANY_SOURCE is useful if, for
// example, we wish to receive all the results of one phase of computation before moving on
// to the next phase. Messages sent with the next tag can then be queued until the receiving
// process is ready for them. The wild card MPI::ANY_TAG is useful if we know which process
// is sending the data, but do not know what the tag will be.




