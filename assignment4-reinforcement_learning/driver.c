#include <iostream>
#include <list>
#include "string.h"

// #include "pole.h"

#include "cell.h"
#include "cart.h"

using namespace std;

void print_table(double table[][21])
{
  for (int i=0; i<21; i++)
  {
    for (int j=0; j<21; j++)
      cout << table[i][j] << "\t";
    cout << endl;
  }
}


int main(int argc, char *argv[])
{
  cart c;
  pole p;
  
  //   string movement;
  //   double strength;
  //   double time = 0;
  
  //   while(1)
  //   {
    //     cout << "Nudge pole left or right or not at all?\t";
    //     cin >> movement;
    //     cout << "\nWith how much force?\t";
    //     cin >> strength;
    //     
    //     if (movement == "left")
    //       p.nudge(Vector(-strength,0), time);
    //     else if (movement == "right")
    //       p.nudge(Vector(strength,0), time);
    //     else continue;
    //     
    //     time++;
    //     if (c.touchdown(p))
    //     {
    //       cout << "Failed\n";
    //       return 0;
    //     }
    //   }
      
    // int length = 21;
    double rewards_table[21][21];
    double q_learning[21][21];
    // cout << "Enter length of field : ";
    // cin >> length;
    
    // initialize tables
    for (int i=0; i<21; i++)
      for (int j=0; j<21; j++)
	q_learning[i][j] = 0.0;
      
    for (int i=0; i<21; i++)
      for (int j=0; j<21; j++)
	(i == 10) ? rewards_table[i][j] = 1.0 : rewards_table[i][j] = 0.0;
      
//   // testing table population
//   cout << "rewards\n";
//   print_table(rewards_table);
//   
//   cout << "\n\nq table\n";
//   print_table(q_learning);
	
  cout << "Enter cart's position in the field (0 = middle,-10 = left side, +10 = right side): ";
  cin >> c.current_position;

  cout << "Enter the pole's position (-10 = down on left side and 10 = down on right) : ";
  cin >> p.angle;
  
  
  // cout << "\nEnter velocity (-10 = moving left quickly, 0 = not moving, 10 = moving right quickly) : ";
  // cin >> velocity;
  
  // c.balance(p)
  


  return 0;
}