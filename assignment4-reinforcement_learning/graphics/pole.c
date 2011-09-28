#include "pole.h"

pole::pole()
{
  v = Vector(0.0,0.0); // velocity
  v0 = Vector (0.0,0.0); // initial velocity
  a = Vector(0.0, 0.0); // acceleration
  f = Vector(0.0,0.0); // force
  w = Vector(0.0,0.0); // angular velocity

  mass = 5.0;
  height = 32.0; // height
  width = 1.50; // width
  
  pivot = Vector(0.0,9.0);
  pivot_radius = 0.25;
  angle = 0.0;
}

void pole::nudge(Vector acceleration, double t)
{
  double delta_t = t - prev_time;
  f = acceleration*mass;
  v =  v0 + (a*delta_t);

  /*
      (r x v)
  w = -------
      |r|*|r|
      
  */
  Vector r = Vector(0.0,height); 
  w = cross(r,v);
  w = w * (1/(r.magnitude()*r.magnitude()));
  
  
  
  // set previous to current
  v0 = v;
  prev_time=t;
}

void pole::fall(double t)
{
  a = Vector(0,-9.8);
  v = v0 + a*(t - prev_time);
}
