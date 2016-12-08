#include "position.h"
#include "stdlib.h"

extern int g_iScreenHeight;
extern int g_iScreenWidth;

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

void Position::SetRandom()
{
	fX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / ((float)g_iScreenHeight + 1.f));
	fY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / ((float)g_iScreenHeight + 1.f));
}
