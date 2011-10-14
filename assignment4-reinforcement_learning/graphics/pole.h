#ifndef _POLE_H_
#define _POLE_H_

// #include "cart.h"
#include "Vector.h"
#include <ctime>

class pole
{
  public:
    double width;
    double height; // height
    double mass;

//     Vector f; // force
    Vector v; // velocity
    Vector v0; // initial velocity
    Vector a; // acceleration
    double w; // angular velocity in y-dir

//     Vector pivot; // location of the pin in the pole
//     double pivot_radius; // radius of the pin

    double t0; // initial time
    double t; // = current time;


    //             0 deg
    //               ||
    // -90 deg <==   || ==> 90 deg
    //             -------
    //             |     |

    double angle;
    double prev_angle;
    pole();
    void nudge();
    void fall();
    double convert_angle(double& a);
};

#endif