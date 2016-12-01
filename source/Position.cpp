#include "position.h"
#include "stdlib.h"
#include "ctime"

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
	srand(static_cast<unsigned int>(time(0))); //Seed
	fX = rand() % (g_iScreenWidth + 1);
	fY = rand() % (g_iScreenHeight + 1);
}
