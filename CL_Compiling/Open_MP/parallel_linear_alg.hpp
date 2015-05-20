//
//  parallel_linear_alg.hpp
//  
//
//  Created by Luke Lloyd-Jones on 20/05/2015.
//
//

#include <mpi.h>
#include <cmath>
#include <cassert>

class MpiVector
{
private:
    //Store components
    int mLo, mHi, mSize;
    double* mData;
    double* mGlobalData;
public:
    MpiVector(int vecSize)
    {
        int num_procs = MPI::COMM_WORLD.Get_size();
        int rank = MPI::COMM_WORLD.Get_rank();
        int ideal_local_size = vecSize / num_procs;
        assert (ideal_local_size > 0);
        mLo = ideal_local_size * rank;
        mHi = ideal_local_size * (rank + 1);
        
        //Top processor picks up extras
        if (rank == num_procs - 1)
        {
            mHi = vecSize;
        }
        assert(mHi > mLo);
        mData = new double[mHi - mLo];
        mGlobalData = new double[vecSize];
        mSize = vecSize;
    }
    ~MpiVector()
    {
        delete[] mData;
        delete[] mGlobalData;
    }
    
    double& operator[](int globalIndex)
    {
        //Make sure that this on the local vector
        assert(mLo <= globalIndex && globalIndex < mHi);
        return mData[globalIndex - mLo];
    }
    
    int GetHi()
    {
        return mHi;
    }
    
    int GetLo()
    {
        return mLo;
    }
    
    double CalculateNorm() const
    {
        double local_sum = 0.0;
        for (int i = 0; i < mHi - mLo; i++)
        {
            local_sum += mData[i] * mData[i];
        }
        double global_sum;
        MPI::COMM_WORLD.Allreduce(&local_sum, &global_sum, 1, MPI::DOUBLE, MPI::SUM);
        return sqrt(global_sum);
    }
    
    void UpdateGlobal()
    {
        int num_procs = MPI::COMM_WORLD.Get_size();
        int num_per_proc[num_procs];
        int local_size = mHi - mLo;
        MPI::COMM_WORLD.Allgather(&local_size, 1, MPI::INT, num_per_proc, 1, MPI::INT);
        int lows_per_proc[num_procs];
        MPI::COMM_WORLD.Allgather(&mLo, 1, MPI::INT, lows_per_proc, 1, MPI::INT);
        MPI::COMM_WORLD.Allgatherv(mData, local_size, MPI::DOUBLE, mGlobalData, num_per_proc,
                                   lows_per_proc, MPI::DOUBLE);
    }
    
};
    
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
    }
};
