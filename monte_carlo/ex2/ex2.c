#include <iostream>
#include <cmath>
#include "rngs.h"

using namespace std;

bool x2or(bool a, bool b) 
{ 
//   ((a && !b) || (!a && b)) ? return true : return false; 
}

int main()
{
  double dt = 0.5f;
  double t = 0.0f;
  double max_error = 0.1f;

  int j=0;  // counter for # of times value stays w/i error band
  
  double y = 0.0f;

  double k, k_min(0.0f), k_max(2000.0f);
  double a, a_min(0.0f), a_max(2000.0f);

  double t_o = 0.0f;
  
  double max_time = 100.0f;
  bool first_bound = true;
  bool second_bound = false;

 
  /*
  When 1-e<y(t_i)<1+e for the first time set t_o=t_i. Continue sampling for a sufficiently long time. If y(t) for some t_j>t_i is found to be outside the error band, reset t_o=0. Continue measurements until y(t) enters the error band again at t_k. Assign t_o to t_k
  */

  PutSeed(-1);
  k = ( k_max + ((k_min-k_max) * Random()) );
  a = ( a_max + ((a_min-a_max) * Random()) );
  
  do 
  {
    y = 1.0f-(exp(-k*t)*cos(a*t));
  
    if ((y > (1.0f-max_error)) && (y < 1.0f+max_error) )
    {
      if (first_bound)
      {
        t_o = t;
        first_bound = false;
        second_bound = true;
      }
      
      if (second_bound)
      {
        t_o = t;
      }
      j++;
    }
    
    else if ((y < (1.0f-max_error)) || (y > 1.0f+max_error))
    {
      t_o = 0.0f;
      first_bound = true;
      second_bound = false;
      j=0;
    }
    
    t += dt;
    
  } while ( ((t_o-t) < max_time)&&(j < 1000.0f) );
  
  if (k > k_min) k_min = k;
  if (k < k_max) k_max = k;
  
  if (a > a_min) a_min = a;
  if (a < a_max) a_max = a;
      
  cout << t << "\t"<< y << "\t" << k << "\t" << a << endl;
  return 0;
}