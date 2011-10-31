#include <iostream>
#include <cmath>
#include "stdlib.h"

using namespace std;

struct interval
{
  double min;
  double max;
};


int main()
{
  double dt = 0.5f;
  double t = 0.0f;
  double max_error = 0.1f;

  int i=0;

  double y = 0.0f;

  interval k;
  k.min = -10.0f;
  k.max = 10.0f

  interval a;
  a.min = -10.0f;
  a.max = 10.0f;

  double t_o = 0.0f;
  /*
  When 1-e<y(t_i)<1+e for the first time set t_o=t_i. Continue sampling for a sufficiently long time. If y(t) for some t_j>t_i is found to be outside the error band, reset t_o=0. Continue measurements until y(t) enters the error band again at t_k. Assign t_o to t_k
  */

  bool out_of_bounds = FALSE;
  do
  {
    double current_k = i*0.95*k.min;
    double current_a = i*0.95*a.min;

    y = 1 - (exp(-k.min*t)*cos(a.min*t));

    if ((y > (1.0f-max_error)) && (y < 1.0f+max_error)
    {
      if (!out_of_bounds)
      {
	t_o = t;
	out_of_bounds = TRUE;
      }

      else
      {
	t_o = 0.0f;
      }
    }


    i++;
    t += i*dt;
  } while( (y > (1.0f-max_error)) && (y < 1.0f+max_error));

  return 0;
}