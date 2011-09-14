#pragma once
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

pole::pole()
{
  velocity(0,0);
  initial_velocity(0,0);
  acceleration(0,gravity);
  force(0,0);
  angular_v(0,0);
  
  mass = 10;
  height = 10;
}

void pole::nudge(Vector f, double t)
{
  acceleration = acceleration + f*(1/mass);
  velocity =  initial_velocity + (acceleration*t);
  
  angular_v = f*(1/(height*mass);
  initial_velocity = velocity;
  
  prev_time=t;
}

void pole::fall(double t)
{
  acceleration = gravity;
  velocity = initial_velocity + acceleration*(t - prev_time);
}