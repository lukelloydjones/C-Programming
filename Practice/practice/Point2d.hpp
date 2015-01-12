//
//  Point2d.h
//  practice
//
//  Created by Hayley Wise on 13/12/2014.
//  Copyright (c) 2014 Luke Lloyd-Jones. All rights reserved.
//

#ifndef POINT2DDEF
#define POINT2DDEF

class Point2d
{
public:
    // int x, y;
    double v,z;
    
    // Constructorn for integers
    
//    Point2d(int a, int b)
//    {
//        x=a;
//        y=b;
//    }
    
    // Constructor for floats
    
    Point2d(double a, double b)
    {
        v=a;
        z=b;
    }
    
    bool operator < (const Point2d& other) const
    {
        if ((v - other.v) < 0 )
        {
            return true;
        }
        else if ((v - other.v) > 0)
        {
            return false;
        }
        else if ((z - other.z) < 0)
        {
            // x == other.x
            return true;
        }
        else if (fabs(sqrt(pow((v-other.v),2)+pow((z-other.z),2)))<1.0e-8)
        {
            return false;
        }
        else
        {
            // x == other.x
            // y >= other.y
            return false;
        }
    }
    
};



#endif
