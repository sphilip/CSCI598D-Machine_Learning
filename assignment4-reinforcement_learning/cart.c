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

void cart::balance(pole &p)
{
  printf("blah\n");
  return;
}

bool cart::touchdown(pole &p)
{
  if (p.angle >= 90 || p.angle <= -90)
    return true;
  else return false;
}
