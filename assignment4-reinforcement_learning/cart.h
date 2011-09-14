#pragma once
#include "pole.h"
#include "Vector.h"

class cart
{
  public:
    double current_position;
    pole p;
    Vector velocity;
    Vector acceleration;

    Vector pole_location;
    Vector cart_dim;

    cart();
    void move();
    void balance(pole &p);
    bool touchdown(pole &p);
};

cart::cart()
{
  current_position = 0;
  velocity(0,0);
  acceleration(0,0);
  
  cart_dim(10,10);
  pole_location(5,5);
}

void cart::move()
{
}

void cart::balance(pole p)
{
}

bool cart::touchdown(pole &p)
{ 
  if (p.angle >= 90 || p.angle <= -90)
    return true;
  else return false; 
}