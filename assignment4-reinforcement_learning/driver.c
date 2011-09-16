#include <iostream>
#include <list>
#include "pole.h"
#include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
  cart c;
  pole p;
//   int rewards_table = [0,0,0,0,100,0,0,0,0];
//   int q_table = [0,0,0,0,0,0,0,0,0];
  list<int>::iterator *current_state;
  
  list<int> rewards_table;
  for (int i=0; i<9; i++)
  {
    if (i==4)
      rewards_table.push_back(100);
    
    else rewards_table.push_back(0);
  }
  
  list<int> q_table(0,9);
  
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