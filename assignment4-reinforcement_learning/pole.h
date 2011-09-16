#ifndef _POLE_H_
#define _POLE_H_

#include "cart.h"
#include "Vector.h"
  
#define gravity -9.8
class pole
{
  public:
    double height;
    
    Vector force;
    double mass;
    Vector velocity;
    Vector initial_velocity;
    Vector acceleration;
    Vector angular_v;
    
    double prev_time;
    
    
    //             0 deg
    //               ||
    // -90 deg <==   || ==> 90 deg
    //             -------
    //             |     |
    
    double angle;
    
    pole();
    
    void nudge(Vector, double);
    void fall();
};

#endif