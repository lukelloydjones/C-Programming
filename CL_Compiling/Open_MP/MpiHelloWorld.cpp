// ---------------------------------------------------------------------
// Author: Luke Lloyd-Jones
// Date: 20/03/2015
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Includes and headers
// ---------------------------------------------------------------------

#include <mpi.h>
// #include <boost/lambda/lambda.hpp>
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
//    // int rank = MPI::COMM_WORLD.Get_rank(); // Identifies the process executing
//    // a given statement
//    int world_size = 4;
//    int rank = MPI_Comm_size(MPI_COMM_WORLD, &world_size);
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


//int main(int argc, char** argv) {
//    // Initialize the MPI environment
//    MPI_Init(NULL, NULL);
//    
//    // Get the number of processes
//    int world_size;
//    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//    
//    // Get the rank of the process
//    int world_rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//    
//    // Get the name of the processor
//    char processor_name[MPI_MAX_PROCESSOR_NAME];
//    int name_len;
//    MPI_Get_processor_name(processor_name, &name_len);
//    
//    // Print off a hello world message
//    printf("Hello world from processor %s, rank %d"
//           " out of %d processors\n",
//           processor_name, world_rank, world_size);
//    
//    // Finalize the MPI environment.
//    MPI_Finalize();
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

//int main(int argc, char* argv[])
//{
//  MPI::Init(argc, argv);
//    int tag = 30;
//    if (MPI::COMM_WORLD.Get_rank() == 0)
//    {
//      // Specific send code for process 0
//      double send_buffer[2] = {100.0, 200.0};
//      MPI::COMM_WORLD.Send(send_buffer, 2, MPI::DOUBLE, 1, tag);
//    }
//    if (MPI::COMM_WORLD.Get_rank() == 1) // process rank guard
//    {
//      // Specific receive code for process 1
//      double recv_buffer[2] = {0.0, 0.0};
//      MPI::COMM_WORLD.Send(recv_buffer, 2, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG);
//      std::cout << recv_buffer[0] << "\n";
//      std::cout << recv_buffer[1] << "\n";
//    }
//   MPI::Finalize();
//// Point to point communication is necesarily nonsymmetric: both processes are running
//// exactly the same program with the same code, but parts of the program which are
//// intended only for one process are placed in specific blocks guarded by their process
//// rank.
//    return 0;
//}

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

//std::cout << "Processes may arrive at any time \n";
//std::cout.flush();
//MPI::COMM_WORLD.Barrier();
//std::cout << "All processes continue together\n";
//std::cout.flush();

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

//void Comm::Sendrecv(const void *sendbuf, int sendcount, const Datatype& sendtype,
//                    int dest, int sendtag,
//                    void *recvbuf, int recvcount,
//                    const Datatype& recvtype,
//                    int source, int recvtag) const

// There are ten arguments which are divided into 2 groups 5 for send and 5 for
// receive. Similar to PTP, interpreted relative to the local process: if each
// process is sending to the rank above, by symmetry, then each mus be receiving from
// the rank below. * It is possible to mix the types of messages (both in terms
// of DataType and the length of the messages) so that, for example, odd-ranked processes are
// send- ing integer messages to the process above, but even-ranked processes are sending
// double precision floating point data

// The following code shows all processes communicating in a ring. Each process (with rank given by the variable rank) sends a message to its right-hand neighbour (rank + 1).
// Modular arithmetic—see Sect. 1.4.3—ensures that the left_rank and right_rank variables are set inside the range 0 ≤ rank < num_procs so that the top-most process is able to send a message to the rank 0 process
//int main(int argc, char* argv[])
//{
//    MPI::Init(argc, argv);
//    int tag = 30;
//    int rank = MPI::COMM_WORLD.Get_rank();
//    int num_procs = MPI::COMM_WORLD.Get_size();
//    // std::cout << "Num process " << num_procs << "\n";
//    // left_rank is rank-1
//    // Note modular arithmetic, so that 0 has
//    // neighbour num_procs-1
//    int left_rank  = (rank - 1 + num_procs) % num_procs;
//    int right_rank = (rank + 1) % num_procs;
//    std::cout << "Num left_rank "  << left_rank << "\n";
//    std::cout << "Num right_rank " << right_rank << "\n";
//    int recv_data;
//    // Communicate in a ring ...->0->1->2...
//    MPI::COMM_WORLD.Sendrecv(&rank, 1, MPI::INT, right_rank, tag, &recv_data, 1, MPI::INT,left_rank, tag);
//    std::cout << "Process " << rank << " received from " << recv_data << "\n";
//    MPI::Finalize();
//return 0;
//}
// Ran this line mpirun -np 4 ./MpiHelloWorld

// MPI provides a special process name MPI::PROC_NULL which mean that this process does not participate
// with a send and or receive. This process name is illustrated in the following code, which is
// similar to the previous Sendrecv example except that is no closed loop: the top process does not
// send to process 0
//int main(int argc, char* argv[])
//{
//    MPI::Init(argc, argv);
//    int tag = 30;
//    int rank = MPI::COMM_WORLD.Get_rank();
//    int num_procs = MPI::COMM_WORLD.Get_size();
//    int right_rank = rank + 1;
//    // Top-most receives nothing
//    if (rank == num_procs - 1)
//    {
//        right_rank = MPI::PROC_NULL;
//    }
//    int left_rank = rank - 1;
//    // Bottom-most receives nothing
//    if (rank ==0)
//    {
//        left_rank = MPI::PROC_NULL;
//    }
//    int recv_data = 999; //This will be unchanged on proc 0
//    // Communicate 0->1->2... Final process sends nowhere
//    MPI::COMM_WORLD.Sendrecv(&rank, 1, MPI::INT, right_rank, tag,
//                             &recv_data, 1, MPI::INT, left_rank, MPI::ANY_TAG);
//    std::cout << "Process " << rank << " received from "<< recv_data << "\n";
//    MPI::Finalize();
//    return 0;
//}
//
//
//// Broadcast and Reduce
//// --------------------
//
//// The collective operations broadcast and reduce are primarily one-to-many and many-to-one operations
//// In a broadcast (Bcast) operation, data from one process are shared with all other processes in the communication group. In a reduction op- eration, all the data is concentrated to a single process.
//// There are other predefined reduction operations available including some bit-wise operations, and there is also opportu- nity to define extra operations. Note that the argument root is the source of the broadcast but the destination of the reduction
//
//void Comm::Bcast(void* buffer, int count , const MPI::Datatype& datatype, int root) const
//void Comm::educe(const void* sendbuf, void* recvbuf, int count, const MPI::Datatype datatype, const MPI::Op& op, int root) const

// Reductuion operation is given below where the partial sums of a series are summed together in a
// single reduction step. Also, below is a broadcasr example in which one process process 0 - mimics
// throwing three dice by generating integer randim numbers from 1-6, and broadcasts the results of
// all three thorws. Each process then adds their own rank to the value shown on the first
// die, and a reductions opeations reports on the maximum value attained

//int main(int argc, char* argv[])
//{
//    MPI::Init(argc, argv);
//    int dice[3] = {0, 0, 0};
//    //Proc 0 sets the dice (#sides)
//    if (MPI::COMM_WORLD.Get_rank() == 0)
//    {
//        for (int i = 0; i < 3; i ++)
//        {
//            dice[i] = (rand() % 6) + 1;
//        }
//    }
//    std::cout << "Dice " << dice[0] << " received from " "\n";
//    //Proc 0 broadcasts
//    MPI::COMM_WORLD.Bcast(dice, 3, MPI::INT, 0);
//    //Every process adds their rank to dice[0]
//    dice[0] += MPI::COMM_WORLD.Get_rank();
//    std::cout << "Dice " << dice[0] << " received from " "\n";
//    //Reduce the first value to get the maximum
//    int max;
//    MPI::COMM_WORLD.Reduce(dice, &max, 1, MPI::INT, MPI::MAX, 0);
//    std::cout << "Process " << max << "\n";
//    //On Proc 0: max = dice[0]+MPI::COMM_WORLD.Get_size()-1
//    MPI::Finalize();
//    return 0;
//}

// Scatter and Gather
// ------------------


//The scatter and gather operations are extensions to broadcast and reduction oper- ations. They are the most advanced operations which we cover in this book, and we do so because the gather operation is useful for taking data which has been distributed across processes and concentrating it onto a single process. For example, if a vector is split across processes in a similar manner to a PETSc vector we might wish to write it to a file using a single write operation using only one process.

// The scatter operation is like broadcae it is one to many process. Sends message to all other processes
// BC same entries of data of size count are sent to all processes, the first count elements are sent
// to the first process and the next count to the next and so on.

// The gather operation is similar to the reduce operation in that it is many to one. Each process
// contributes some data to the result. The data is not reduced it is concatenated. Need count
// multiplied bu num_procs elements will be stored. Can have variable data sizes with variations
// of these functions.

// Prototype signatures of the scatter and gather operations are

//void Comm::Scatter(const void* sendbuf, int sendcount,
//                   const MPI::Datatype& sendtype, void* recvbuf,
//                   int recvcount, const MPI::Datatype& recvtype,
//                   int root) const
//
//void Comm::Gather(const void* sendbuf, int sendcount,
//                  const MPI::Datatype& sendtype, void* recvbuf,
//                  int recvcount, const MPI::Datatype& recvtype,
//                  int root) const
//
//void Comm::Allgatherv(const void* sendbuf, int sendcount,
//                      const MPI::Datatype& sendtype, void* recvbuf,
//                      const int recvcounts[], const int displs[],
//                      const MPI::Datatype& recvtype) const

// The argument root always refers to the scatterer (sender) or to the gatherer (receiver). In most
// cases the types and counts of the send and receive data should be identical, with the counts
// referring to the size of the array sent to each process.



// Example MPI applications
// ------------------------

// In general, the choice of parallel algoirthm depends on how it relates to an equivalent sequenctial
// algorithm and how the data is partitioned. Minimise communication between processes and the
// the processes should be given an equivalent amount of work - load balancing.

// The measures of success in producing parallel programs are parallel speedup and parallel efficiency
// Parallel speedup is the ratio of the time it take to run the code sequentially vs the time it
// takes to run on p processes. We hopw Sp = Ts/Tp = p. Parallel efficiency scales this value by p
// so that Ep = Ts/pTp is in the range of 0 1 with 1 being ideal. It is rare but not unusual for a
// problem to scale in parallel such that Ep > 1. Happens when there are memomory constraints n
// small number of processes and is known as super-linear speedup.

// Summation of Series
// -------------------

// The summation of a series can be taken as an abstraction of a range of problems. Partition work
// and minimal communication. Termed embarrassingly parallel. Problem of summing a series, scuh as
// the approximation to pi

// pi/4 = sum(0, inf) (-1)^n/(2n + 1)

// credited to Gottfried Wilhelm Leibniz. Compute up to some max not infinity. In dividing the max
// contribtions to each process we might choose to allocate the work in blocks so that the
// first max/p contributions to the series go to process zero, and so on, or we may distribute in
// such a way to interleave processor contributions. The following code the contributions are inter
// leaved (divide (memory or processing power) between a number of tasks by allocating segments of it to each task in turn). Only parallel communication neede in this code is a reduction operation
// which combined the subtotals from the process into a grand total on process 0.


// Program to sum Pi using Leibniz formula:
// Pi = 4*Sum_n( (-1)**n/(2*n+1) )


//int main(int argc, char* argv[])
//{
//    int max_n = 10000;
//    double sum = 0;
//    MPI::Init(argc, argv);
//    
//    int num_procs = MPI::COMM_WORLD.Get_size();
//    int      rank = MPI::COMM_WORLD.Get_rank();
//    
//    std::cout << "num_procs " << num_procs << "\n";
//    std::cout << "rank " << rank  << "\n";
//    int ss = 0;
//    for (int n = rank; n < max_n; n += num_procs)
//    {
//        double temp = 1.0 / (2.0 * ((double)(n)) + 1.0);
//        if (n % 2 == 0) // n is even
//        {
//            sum += temp; }
//        else
//        {
//            // n is odd
//            sum -= temp;
//        }
//        ss += n;
//    }
//    std::cout << "Elements computed on process " << rank << "is " << ss << "\n";
//    
//    double global_sum;
//    
//    MPI::COMM_WORLD.Reduce(&sum, &global_sum, 1, MPI::DOUBLE, MPI::SUM, 0);
//    
//    if (rank == 0)
//    {
//        std::cout << "Pi is about " << 4.0 * global_sum
//                  << " with error " << 4.0 * global_sum - M_PI
//                  << "\n";
//    }
//    MPI::Finalize();
//    return 0;
//}


// Parallel Linear Algebra
// -----------------------

// We can partition the matrix into sets of rows and push these sets to different
// processes. Each process mush know all the elements of the vector that is
// being modelled. We need the following operations to do the Ax=b problem

// Scalar vector multiplication - operation on locally held data
// Vector-vector addition and subtraction - operations on locally held data
// Vector Euclidean norm - a sum of squares on local data followed by a global
// sum of squares (a parallel reduction), followed by a square root
// Matrix-vector multiplication in whch data from the vector must be
// communicated between all the processes


// Lots in the MpiVector.hpp to learn

#include <iostream>
#include <mpi.h>
#include "MpiVector.hpp"

int main(int argc, char* argv[])
{
    MPI::Init(argc, argv);
    MpiVector all_ones(200);
    std::cout << "Local has [" << all_ones.GetLo() <<
                 ", " << all_ones.GetHi() << ")\n";
    for (int i = all_ones.GetLo(); i < all_ones.GetHi(); i++)
    {
        all_ones[i] = i * 1.0;
    }
    // assert(fabs(all_ones.CalculateNorm() - 3.0) < 1.0e-6);
    // all_ones.UpdateGlobal();
    // std::cout << all_ones.UpdateGlobal() << "\n";
    MPI::Finalize();
    return 0;
}

// Debugging a parallel program
// ----------------------------

// Make an abstract program. Hard to see the communication patterns underlying
// the parallel code. They can easily get lost in the details of the calculations
// Take the time to design the communication patterns needed in your parallel
// codeand then start afresh. Write a simplified abstract program which concentrates
// on communication but neglects the main calculation. Test the safe working of the
// communication at first. Once the message passing is working correctly then it can
// be easily integrated into the main program.

// Data type mismatch
// Listing 11.2 the process 0 block has been amended so that the type of the data is
// now int and the message sent is MPI::INT. However, the receiving code is still
// MPI:: DOUBLE. The message passing may work correctly in terms of communication
// but the data received on process 1 will probably be incorrect. This may be in
// mismatches in the size of the data or it may be due to errors in the conversion
// of the data.

// Problems of data types or sizes can be hard to see especially when send and receive
// components are in separates methods or in separate files.

// Intermittent Deadlock
// Deadlock is the situation where all processes are waiting for some event to happen
// before proceeding but no process can supply that event because they are waiting
// for another process. Delib induce deadlock in ex 11.2 by never receiving any
// messages so that eventually the sender is not able to proceed because it is
// unable to send any more messages.
// Problems involving intermittent deadlock are harder to diagnose. Happens
// when you deadlock on some runs but is fine on others. For example, for some
// test data the program runs fine but for real life input it deadlocks. This
// indicates that timing and size are problems. Small amounts of data can be
// buffered but large amounts cannot. May be a threshold that induces deadlock.
// They may their programs more likely to deadlock by removing buffering and
// asynchronous messages by replacing Send with Ssend. This will lead to
// deadlock rather than Ideadlock and thus easier to identufy. You can make the
// program more synchronous by splitting calc steps up with barriers. You can then
// make the code more efficient latter.







