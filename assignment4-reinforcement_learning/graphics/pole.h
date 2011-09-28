#ifndef _POLE_H_
#define _POLE_H_

// #include "cart.h"
#include "Vector.h"

class pole
{
  public:
    double width;
    double height; // height
    double mass;
    
    Vector f; // force
    Vector v; // velocity
    Vector v0; // initial velocity
    Vector a; // acceleration
    Vector w; // angular velocity
    
    Vector pivot; // location of the pin in the pole
    double pivot_radius; // radius of the pin
    
    double prev_time;
    
    
    //             0 deg
    //               ||
    // -90 deg <==   || ==> 90 deg
    //             -------
    //             |     |
    
    double angle;
    
    pole();
    void nudge(Vector f, double t);
    void fall(double t);
};

#endif