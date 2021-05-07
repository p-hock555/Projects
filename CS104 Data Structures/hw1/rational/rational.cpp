#include <stdexcept>
#include <cmath>
#include "rational.h"


Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(const int num, const int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()
    //normalize if the numerator is 0
    n = num;
    d = denom;

    if(n < 0 && d < 0)
    {
      n*=-1;
      d*=-1;
    }
    else if(n > 0 && d < 0)
    {
      n*=-1;
      d*=-1;
    }

    if(n==0)
    {
      this->normalize0();
    }
    //reduce if needed
    else if(Rational::gcd(abs(n), abs(d)) > 1)
    {
      this->reduce();
    }

}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1; //cannot have a zero denominator, normalize
}
void Rational::reduce()
{
  int g = Rational::gcd(abs(n), d); //use cmath library to reduce the rational number

  if(d == 1)
  {
    return; //if we divide d by g, we will end up with a zero as the denominator
  }

  n/=g;
  d/=g;
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r)
{
  int n = abs(r.n); 
  int d = r.d;

  if(r.n < 0)
  {
    ostr << '-' << n << '/' << d; //print out in the desired format, while also checking for neg. value
  }
  else{
    ostr << n << '/' << d;
  }
    return ostr;
}
std::istream& operator>>(std::istream& istr, Rational& r)
{
  int num, denom;
  char c;

  istr >> num >> c >> denom; //c will hold and discard any character that isn't an int.

  r = Rational(num,denom);
  return istr;
}

int Rational::gcd(int a, int b)
{
  if (a == 0){
    return b;
  }
  return gcd(b % a, a); 

}
int Rational::lcm(int a, int b)
{
  return (abs(a*b))/gcd(a, b);

}
/* if there is no scoping of the operator overloading, then we need to define
    the left hand side as an argument */
Rational operator+(int x, const Rational& rhs)
{

	int least, num1, newN, newD;

	least = rhs.d;
  newD = least;
  num1 = least * x;
  newN = num1 + rhs.n;

  Rational a(newN, newD);

	return a;

}
Rational operator+(const Rational& lhs, int x)
{
	int least, num1, newN, newD;

	least = lhs.d;
  newD = least;
  num1 = least * x;
  newN = num1 + lhs.n;

  Rational a(newN, newD);

  return a;

}
Rational Rational::operator+(const Rational& rhs)
{
  int least, mult, num1, num2, newn, newd;

  least = Rational::lcm(d, rhs.d);
  newd = least;
  mult = least/d;
  num1 = mult * n;
  mult = least/rhs.d;
  num2 = mult * rhs.n;
  newn = num1 + num2;

  Rational a(newn, newd);

  return a;
}
Rational Rational::operator*(const Rational& rhs)
{
  int newN, newD;

  newN = n * rhs.n;
  newD = d * rhs.d;

  Rational a(newN, newD);

  return a;
}
Rational operator*(int x, const Rational& rhs)
{
  int newN;

  newN = x * rhs.n;

  Rational a(newN, rhs.d);

  return a;

}
Rational operator*(const Rational& lhs, int x)
{
  int newN;

  newN = x * lhs.n;

  Rational a(newN, lhs.d);

  return a;
}
Rational Rational::operator^(int x)
{
  int newN, newD;
  if(x > 0)
  {
    newN = pow(n,x);
    newD = pow(d,x);
  }
  else if(x < 0)
  {
    if(n<0)
    {
      newN = -1*d;
      newD = -1*n;
    }
    newN = d;
    newD = n;

    newN = pow(newN, abs(x));
    newD = pow(newD, abs(x));
  }
  else{
    newN = 1;
    newD = 1;
  }

  Rational a(newN, newD);

  return a;

}
bool Rational::operator==(const Rational &rhs)
{
  return (n == rhs.n && d == rhs.d);

}
Rational& Rational::operator+=(const Rational &rhs)
{
  int least, mult, num1;

  least = Rational::lcm(d, rhs.d);
  d = least;
  mult = least/d;
  n = mult * n;
  mult = least/rhs.d;
  num1 = rhs.n * mult;
  n += num1;

  this->normalize0();
  this->reduce();

  return *this;
}
Rational& Rational::operator+=(int x)
{
  x = x * d;
  n = n + x;

  return *this;
}
Rational& Rational::operator*=(const Rational &rhs)
{
  n *= rhs.n;
  d *= rhs.d;

  this->normalize0();
  this->reduce();

  return *this;
}
Rational& Rational::operator*=(int x)
{
  n = x * n;

  return *this;
}
bool Rational::operator!=(const Rational &rhs)
{
  return !(n == rhs.n && d == rhs.d);
}
bool Rational::operator<(const Rational &rhs)
{
  int least, mult, num1, num2;

  least = Rational::lcm(d, rhs.d);
  mult = least/d;
  num1 = mult * n;
  mult = least/rhs.d;
  num2 = mult * rhs.n;

  return (num1 < num2);
}
