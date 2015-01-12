//
//  RainyDays.hpp
//  practice
//
//  Created by Luke Lloyd-Jones on 5/01/2015.
//  Copyright (c) 2015 Luke Lloyd-Jones. All rights reserved.
//

#ifndef practice_RainyDays_hpp
#define practice_RainyDays_hpp

template<unsigned int N> class RainyDays
{
private:
    double mData[N];
    
public:
    double& operator[](int index)
    {
        assert(index < N);
        assert(index > -1);
        assert(mData[index]>= -0.0000001 && mData[index]<=1.000001);
        if (mData[index]>=0 && mData[index]<=1)
        {
            mData[index]= mData[index];
        }
        else if (mData[index]>=-10^(-6)&& mData[index]<=0)
        {
            mData[index]=0;
        }
        else if (mData[index]>=1&&mData[index]<=1+10^(-6))
        {
            mData[index]=1;
        }
        return(mData[index]);
    }
    
//    RainyDays& operator=(const RainyDays& rhs)
//    {
//        assert(rhs>=0 && rhs<=1);
//        //        if (value>=0&value<=1)
//        //        {
//        //            mData[i]=value;
//        //        }
//        //        else if (value>=-10^(-6)&value<=0)
//        //        {
//        //            mData[i]=0;
//        //        }
//        //        else if (value>=1&value<=1+10^(-6))
//        //        {
//        //            mData[i]=1;
//        //        }
//        //        }
//        return *this;
//    }
//    
};

#endif
