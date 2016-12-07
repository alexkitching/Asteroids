#include "vector.h"
#include "math.h"
#include "stdlib.h"

//Constructor
Vector::Vector(float a_fX, float a_fY) : fX(a_fX), fY(a_fY)
{
}
//Copy Constructor
Vector::Vector(const Vector & a_vec) : fX(a_vec.fX), fY(a_vec.fY)
{
}
//Magnitude
float const Vector::Magnitude()
{
	return sqrtf(fX * fX + fY * fY);
}
//Normalisation
void const Vector::Normalise()
{
	float fMag = Magnitude();
	if (fMag != 0.f) 
	{
		fX = fX / fMag;
		fY = fY / fMag;
	}
}
void Vector::Set(float & a_fX, float & a_fY)
{
	fX = a_fX;
	fY = a_fY;
}
void Vector::Get(float & a_fX, float & a_fY)
{
	a_fX = fX;
	a_fY = fY;
}
void Vector::SetRandom(float const a_fMin, float const a_fMax)
{
	float const fRange = a_fMax - a_fMin;
	fX = fRange * ((((float)rand()) / (float)RAND_MAX)) + a_fMin;
	fY = fRange * ((((float)rand()) / (float)RAND_MAX)) + a_fMin;
	int iPosNegX = rand() % 2;
	int iPosNegY = rand() % 2;
	if (iPosNegX == 0)
	{
		fX *= -1;
	}
	else if (iPosNegX == 1)
	{
	}
	if (iPosNegY == 0)
	{
		fY *= -1;
	}
	else if (iPosNegY == 1)
	{
	}
}
//Destructor
Vector::~Vector()
{
}
//Operator Overloads
bool Vector::operator==(const Vector & a_vec)
{
	fX == a_vec.fX;
	fY == a_vec.fY;
	return this;
}
bool Vector::operator!=(const Vector & a_vec)
{
	fX != a_vec.fX;
	fY != a_vec.fY;
	return this;
}
Vector Vector::operator+(const Vector & a_vec)
{
	return Vector(fX + a_vec.fX, fY + a_vec.fY);
}
Vector Vector::operator+(const float & a_value)
{
	return Vector(fX + a_value, fY + a_value);
}
Vector Vector::operator+=(const Vector & a_vec)
{
	fX += a_vec.fX;
	fY += a_vec.fY;
	return *this;
}
Vector Vector::operator+=(const float & a_value)
{
	fX += a_value;
	fY += a_value;
	return *this;
}
Vector Vector::operator-(const Vector & a_vec)
{
	return Vector(fX - a_vec.fX, fY - a_vec.fY);
}
Vector Vector::operator-(const float & a_value)
{
	return Vector(fX - a_value, fY - a_value);
}
Vector Vector::operator-=(const Vector & a_vec)
{
	fX -= a_vec.fX;
	fY -= a_vec.fY;
	return *this;
}
Vector Vector::operator-=(const float & a_value)
{
	fX -= a_value;
	fY -= a_value;
	return *this;
}
;

