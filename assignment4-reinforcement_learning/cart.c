#include "cart.h"
#include "pole.h"

cart::cart()
{
  current_position = 0;
  velocity(0.0, 0.0);
  acceleration(0.0, 0.0);
  
  cart_dim(10.0 ,10.0);
  pole_location(5.0, 5.0);
}

void cart::move()
{
  std::cout << "move";
  return;
}

void cart::balance(pole &p)
{
  std::cout << "blah\n";
  return;
}

bool cart::touchdown(pole &p)
{ 
  if (p.angle >= 90 || p.angle <= -90)
    return true;
  else return false; 
}
