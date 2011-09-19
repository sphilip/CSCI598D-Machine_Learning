#include "stdio.h"
#include "cart.h"
#include "pole.h"

cart::cart()
{
  current_position = 0;
  velocity = Vector(0.0, 0.0);
  acceleration = Vector(0.0, 0.0);

  cart_dim = Vector(10.0 ,10.0);
  pole_location = Vector(5.0, 5.0);
}

void cart::nudge()
{
  printf("move\n");
  return;
}

void cart::balance()
{
 if (!touchdown())
 {
   
 }
 
}

bool cart::touchdown()
{
  if (p.angle >= 10 || p.angle <= -10)
    return true;
  else return false;
}
