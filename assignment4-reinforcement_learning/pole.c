#include "pole.h"

pole::pole()
{
  velocity(0.0, 0.0);
  initial_velocity(0.0, 0.0);
  acceleration(0.0, gravity);
  force(0.0, 0.0);
  angular_v(0.0, 0.0);
  
  mass = 10.0;
  height = 10.0;
}

void pole::nudge(Vector f, double t)
{
  acceleration = acceleration + f*(1/mass);
  velocity =  initial_velocity + (acceleration*t);
  
  angular_v = f*(1/(this->height*this->mass);
  initial_velocity = velocity;
  
  prev_time=t;
}

void pole::fall(double t)
{
  acceleration = gravity;
  velocity = initial_velocity + acceleration*(t - prev_time);
}
