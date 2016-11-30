#include "position.h"

Position::Position()
{
	fX = 0.f;
	fY = 0.f;
}

void Position::Set(float a_fX, float a_fY)
{
	fX = a_fX;
	fY = a_fY;
}

void Position::Get(float & a_fX, float & a_fY)
{
	a_fX = fX;
	a_fY = fY;
}
