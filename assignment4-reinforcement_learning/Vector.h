#include <cmath>

class Vector
{
  public:
    double x,y;

    Vector();
    Vector(double a, double b);
    Vector operator+ (const Vector& b) ;
    Vector operator- ( Vector& b) ;
    Vector operator- () ;
    Vector operator* (const double& x) ;
    Vector operator= (const Vector& b);
    double magnitude ();
    Vector normalize ();
    bool operator< ( Vector& b);
    bool operator<= ( Vector& b);
    bool operator> ( Vector& b);
    bool operator>= ( Vector& b);
    bool operator== (const Vector& b);
};

/** Default construct, initialize to 0 **/
Vector::Vector()
{
  x = 0;
  y = 0;
}

/** Construct w/  parameter list **/
Vector::Vector(double a, double b)
{
  x = a;
  y = b;
}

/** Overloaded operator to add 2 vectors **/
Vector Vector::operator+ (const Vector& b)
{
  Vector c;
  c.x = (this->x + b.x);
  c.y = (this->y + b.y);

  return c;
}

/** Overloaded operator to subtract 2 vectors **/
 Vector Vector::operator- ( Vector& b)
{
  Vector c;
  c.x = (this->x - b.x);
  c.y = (this->y - b.y);

  return c;
}

/** Overloaded operator to negate **/
 Vector Vector::operator- ()
{
  return Vector(-this->x,-this->y);
}

/** Overloaded operator to scalar mult **/
 Vector Vector::operator* (const double& x)
{
  Vector c;
  c.x = (this->x * x);
  c.y = (this->y * x);

  return c;
}

/** Overloaded operator to assign vector b to this vector **/
Vector Vector::operator= (const Vector& b)
{
  this->x = b.x;
  this->y = b.y;

  return *this;
}

/** Find magnitude of this vector **/
double Vector::magnitude()
{
  double power = pow(this->x,2) + pow(this->y,2);

  return sqrt(power);
}

/** Find normal vector **/
 Vector Vector::normalize()
{
  Vector result;
  double magnitude = this->magnitude();
  result.x = this->x/magnitude;
  result.y = this->y/magnitude;

  return result;
}

/** Overloaded inequalities **/
bool Vector::operator< ( Vector& b)
{
  if (this->x < b.x || this->y < b.y)
    return true;

  else return false;
}

bool Vector::operator<= ( Vector& b)
{
  if (this->x <= b.x && this->y <= b.y)
    return true;

  else return false;
}


bool Vector::operator> ( Vector& b)
{
  if (this->x > b.x || this->y > b.y)
    return true;

  else return false;
}

bool Vector::operator>= ( Vector& b)
{
  if (this->x >= b.x && this->y >= b.y)
    return true;

  else return false;
}

bool Vector::operator== (const Vector& b)
{
  if (this->x == b.x && this->y == b.y)
    return true;

  else return false;
}

/** Find dot product **/
double dot( Vector& a,  Vector& b)
{
  return (a.x*b.x) + (a.y*b.y);
}

