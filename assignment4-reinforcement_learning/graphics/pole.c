#include "pole.h"
#include <cmath>

pole::pole()
{
  v = Vector(0.0,0.0); // velocity
  v0 = Vector (0.0,0.0); // initial velocity
  a = Vector(0.0, 0.0); // acceleration
  f = Vector(0.0,0.0); // force
  w = 0.0; // angular velocity

  mass = 5.0;
  height = 32.0; // height
  width = 1.50; // width

//   pivot = Vector(0.0,9.0);
//   pivot_radius = 0.25;
  angle = 0.0;
  prev_angle = 0.0;
}

void pole::nudge()
{
  double delta_t = t-t0;
//   f = tangential_a*mass;
  v =  v0 + (a*delta_t);
  /*
      (r x v)   |v|sin(theta)
  w = ------- =  -------------
      |r|*|r|         |r|

  */
//   Vector r = Vector(0.0,height);
  //   w = cross(r,v);
  //   w = w * (1/(r.magnitude()*r.magnitude()));
  w = v.magnitude()*sin(angle)/height;

//   angle = prev_angle + w*delta_t + (0.5*a.magnitude()*delta_t*delta_t)/height;
angle = w*delta_t;
  // set previous to current
  v0 = v;
  t0=t;
}

void pole::fall()
{
  a = Vector(0,-9.8);
//   v = v0 + a*difftime(t,t0);
}

double pole::convert_angle()
{
  return angle/M_PI;
}
