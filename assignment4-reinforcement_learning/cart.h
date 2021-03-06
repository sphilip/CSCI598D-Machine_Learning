#ifndef _CART_H_
#define _CART_H_

#include "pole.h"
#include "Vector.h"

class pole;

class cart
{
  public:
    double current_position;
    pole p();
    Vector velocity;
    Vector acceleration;

    Vector pole_location;
    Vector cart_dim;

    cart();
    void nudge();
    void balance(pole &p);
    bool touchdown(pole &p);
};

#endif

