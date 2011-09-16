#include <iostream>
#include <list>
#include "string.h"

// #include "pole.h"

#include "cell.h"
#include "cart.h"

using namespace std;

int main(int argc, char *argv[])
{
  cart c;
  pole p;
  
  string movement;
  double strength;
  double time = 0;
  
  while(1)
  {
    cout << "Nudge pole left or right or not at all?\t";
    cin >> movement;
    cout << "\nWith how much force?\t";
    cin >> strength;
    
    if (movement == "left")
      p.nudge(Vector(-strength,0), time);
    else if (movement == "right")
      p.nudge(Vector(strength,0), time);
    else continue;
    
    time++;
    if (c.touchdown(p))
    {
      cout << "Failed\n";
      return 0;
    }
  }
  
  return 0;
}