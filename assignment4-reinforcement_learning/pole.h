#ifndef _POLE_H_
#define _POLE_H_

// #include "cart.h"
#include "Vector.h"

class pole
{
  public:
    double height;
    double mass;

    Vector force;
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
    void nudge(Vector f, double t);
    void fall(double t);
};

#endif