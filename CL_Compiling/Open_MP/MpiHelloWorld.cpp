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

//int main(int argc, char* argv[])
//{
//    // Testing MPI
//    
//    MPI::Init(argc, argv); // Start the parallel process
//    int num_procs = MPI::COMM_WORLD.Get_size(); // Number of processes
//    int rank = MPI::COMM_WORLD.Get_rank(); // Identifies the process executing
//    // a given statement
//    std::cout << "Hello world from process " << rank
//    << " of " << num_procs << "\n";
//    MPI::Finalize();  // Stop the parallel process
//    
//    // Testing boost
//    
////    using namespace boost::lambda;
////    typedef std::istream_iterator<int> in;
////    
////    std::for_each(
////                  in(std::cin), in(), std::cout << (_1 * 3) << " " );
//    
//    return 0;
//}

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

//void::Send(const void* buf, int count, const Datatype& datatype, int dest, int tag) const
//void::Recv(void* buf, int count, const Datatype& datatype, int source, int tag) const

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

// The corresponding MPI datatype signatures for the types introduced in chapter 1 are
// MPI::BOOL, MPI::CHAR, MPI::INT, and MPI::DOUBLE. There is no MPI type for strings because
// std::string is a C++ class rather than a plain data-type. You can send entire classes in
// MPI message by using advanced programming features to introduce user-defined data-types
// but this is not recommended. Classes can be transferred by packing the raw data into a
// message at one end and unpacking it into a waiting class at the other end.

// Example code for sending and receiving using the MPI libraries

int main(int argc, char* argv[])
{
  MPI::Init(argc, argv);
    int tag = 30;
    if (MPI::COMM_WORLD.Get_rank() == 0)
    {
      // Specific send code for process 0
      double send_buffer[2] = {100.0, 200.0};
      MPI::COMM_WORLD.Send(send_buffer, 2, MPI::DOUBLE, 1, tag);
    }
    if (MPI::COMM_WORLD.Get_rank() == 1) // process rank guard
    {
      // Specific receive code for process 1
      double recv_buffer[2] = {0.0, 0.0};
      MPI::COMM_WORLD.Send(recv_buffer, 2, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG);
      std::cout << recv_buffer[0] << "\n";
      std::cout << recv_buffer[1] << "\n";
    }
   MPI::Finalize();
// Point to point communication is necesarily nonsymmetric: both processes are running
// exactly the same program with the same code, but parts of the program which are
// intended only for one process are placed in specific blocks guarded by their process
// rank.
    return 0;
}

// Blocking and Buffered Sends
// ---------------------------

// Point to point messaging is the default i.e., using Send and Recv. Both functions are
// blocking functions as they do not allow the program to continue until it us safe to do
// so. The Send guarantees that the contents won't be changed and that any subsequent
// changes to the buffer will not affect the message being sent. If computation is
// allowed to proceed it means that the data is already delivered or it has been saved
// into another buffer ready for delivery.

// Send is a comprimise between waiting to be sure a message has been delivered and
// getting on with other tasks. There are other functions that send messages but on
// different ends of the safety to speed spectrum

// The safest method is Ssend. The method guarantees not to continue until the message
// has been sent. Akin to a telephone call

// Second method is Bsend or buffered send. Allows the program to continue when safe to
// do so. This may happed faster because the message is copied in a separate buffer.
// This buffere must be supplied and configured by the user.

// Isend is the most efficient method for sending messages. Returns control to the program
// immediately, buffered or not yet acted on. Little like SMS. Has a handle MPI::Request
// that has a Wait method: this methid instructs execution to wait her until the message
// has been sent.

// There are others such as Ibsend

// The default Recv is alsp one of a spectrum of functions. Technically a blocking function
// There is also a non blocking Irecv or immediate receive. The program goes on occasionally
// checking back for new information that may be coming in.

// Collective Communication
// ------------------------

// Code for P-P comms is not symmetric - one process sends while the other receives. You can
// make with MPI specialised collective calls in which all the processes take part by
// executing the same commands. There are many flavours. The combined receive - where every
// process sends a message to another, while also receiving a remote message. One-to-many
// broadcast where data from one process are send to the entire group; and many-to-one
// ops such as reduction in which an operation is used to combine results from all processes
// into a single result.

// These collective calls have the advantage that the can be highly tuned to an MPI implemnt
// ation to fit the local architecture. The broadcast of a single number to all p processes
// from process 0 could be achieved by sending p-1 messages from process 0, on message to
// each of the recipients. If process 0 sends to only two processes who each send to two
// more then the informatio is broadcast to all recpients in log2p rounds of message
// sending. If a supercomputer consists of several multicore computers connected by
// Ethernet then the broadcast algorithm can be tuned to minimise the number of Ethernet
// messages while possible increasing the number of faster messages between cores in the
// same machine.

// Collective Communication - Barrier
// ------------------------ ---------

// The simplest collective method is Barrier. It says that every process should wait
// here until all processes are ready to proceed. Barriers are useful when you are
// timing certain parts of the code, printing out information to the console, or
// debugging the code

std::cout << "Processes may arrive at any time \n";
std::cout.flush();
MPI::COMM_WORLD.Barrier();
std::cout << "All processes continue together\n";
std::cout.flush();

// Collective Communication - Combined Send and Receive
// ----------------------------------------------------


// Wish to send and receive many PTP messages at the same point in a computation,
// and where every process should be involved. E.G. solving a PDE using a finite
// difference scheme over a grid, where the value dependes on a the neighbouring
// grid points. Local dependence problems. We can divide the grid into a number
// of identical vertical strips and assigning one strip to each parallel process.
// Partition into independent sets and send each set to a process.
// The local copy of remote neighbouring data is called halo data and the message
// passing process is called halo exchange.

// Is we are averaging of neighbourhoods. Used in moving window process. Sending
// edge data in both directions between processes n and n-1 is known as halo
// exchange. For the same reasons two way halo exchange is also required between
// processes n and n+1.

//For these types of problem, a more sophisticated version of point-to-point mes- sage passing is the combined send and receive, called Sendrecv. Its function pro- totype is:

void Comm::Sendrecv(const void *sendbuf, int sendcount, const Datatype& sendtype,
                    int dest, int sendtag,
                    void *recvbuf, int recvcount,
                    const Datatype& recvtype,
                    int source, int recvtag) const

// There are ten arguments which are divided into 2 groups 5 for send and 5 for
// receive. Similar to PTP, interpreted relative to the local process: if each
// process is sending to the rank above, by symmetry, then each mus be receiving from
// the rank below. * It is possible to mix the types of messages (both in terms
// of DataType and the length of the messages) so that, for example, odd-ranked processes are
// send- ing integer messages to the process above, but even-ranked processes are sending
// double precision floating point data

// The following code shows all processes communicating in a ring. Each process (with rank given by the variable rank) sends a message to its right-hand neighbour (rank + 1).
// Modular arithmetic—see Sect. 1.4.3—ensures that the left_rank and right_rank variables are set inside the range 0 ≤ rank < num_procs so that the top-most process is able to send a message to the rank 0 process

int tag = 30;
int rank = MPI::COMM_WORLD.Get_rank();
int num_procs = MPI::COMM_WORLD.Get_size();
// left_rank is rank-1
// Note modular arithmetic, so that 0 has
// neighbour num_procs-1
int left_rank = (rank-1+num_procs)%num_procs;
int right_rank = (rank+1)%num_procs;
int recv_data;
// Communicate in a ring ...->0->1->2...
MPI::COMM_WORLD.Sendrecv(&rank, 1, MPI::INT,
                         right_rank, tag,
                         &recv_data, 1, MPI::INT,
                         left_rank, tag);
std::cout << "Process " << rank << " received from "
<< recv_data << "\n";


