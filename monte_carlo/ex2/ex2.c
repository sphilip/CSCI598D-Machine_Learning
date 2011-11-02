#include <iostream>
#include <cmath>
#include "rngs.h"

using namespace std;

double Uniform(double a, double b)
{
  return (a + (b - a) * Random());
}

int main()
{
  double dt = 0.5f;
  double t = 0.0f;
  double max_error = 0.1f;

  int i=0;  // counter for # of attempts made to find a stable soln
  int max_try = 1000;

  int j=0;  // counter for # of times value stays w/i error band
  int max_time = 100;

  double y = 0.0f;

  double k, k_min(0.0f), k_max(1.0f);
  double a, a_min(-1.0f), a_max(1.0f);

  double t_o(0.0f);


  bool first_bound = true;

  /*
  When 1-e<y(t_i)<1+e for the first time set t_o=t_i. Continue sampling for a sufficiently long time. If y(t) for some t_j>t_i is found to be outside the error band, reset t_o=0. Continue measurements until y(t) enters the error band again at t_k. Assign t_o to t_k
  */

  int seed;
  cout << "Enter seed (9 digits or less): ";
  cin >> seed;
  PutSeed(seed);

  int w;

  for (w=0; w < seed; w++) {
    k = Uniform(-500.0f,2000.0f);
    a = Uniform(-2000.0f,2000.0f);
    PutSeed(-1);
    if (a<0) cout << "a= " << a << endl;
    do
    {
      y = 1.0f-(exp(-k*t)*cos(a*t));

      if ((y > (1.0f-max_error)) && (y < 1.0f+max_error) )
      {
	if (first_bound)
	{
	  t_o = t;
	  first_bound = false;
	}

	j++;
      }

      else //if ((y < (1.0f-max_error)) || (y > 1.0f+max_error))
      {
	t_o = 0.0f;

	first_bound = true;
	j=0;
      }

      t += dt;
      i++;
    } while ( (j < max_time) || (i < max_try) );

    if (k > k_max) k_max = k;

    if (a < a_min) a_min = a;
    if (a > a_max) a_max = a;
  }

  cout <<  "\nResults:\n";
  cout << "After " << w << " iterations...\n";
  cout << "k values\t" << k_min << "\t" << k_max << "\n";
  cout << "a values\t" << a_min << "\t" << a_max << "\n";

  return 0;
}