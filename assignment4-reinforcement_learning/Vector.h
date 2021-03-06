#ifndef _VECTOR_H_
#define _VECTOR_H_


class Vector
{
  public:
    double x,y;

    Vector();
    Vector(double a, double b);
    Vector operator+ (const Vector& b) ;
    Vector operator- ( Vector& b) ;
    Vector operator- () ;
    Vector operator* (const double& d) ;
    Vector operator= (const Vector& b);
    double magnitude ();
    Vector normalize ();
    bool operator< ( Vector& b);
    bool operator<= ( Vector& b);
    bool operator> ( Vector& b);
    bool operator>= ( Vector& b);
    bool operator== (const Vector& b);
};



#endif