#include "background.h"
#include "position.h"
#include <UGFW.h>
#include <cstdlib>

extern int g_iScreenHeight;
extern int g_iScreenWidth;

Background::Background()
{
	
}

void Background::Initialise()
{
	Position *stop = pos + (sizeof(pos) / sizeof(Position));
	for (Position *posArray = pos; posArray < stop; posArray++)
	{
		int iNewPosX = rand() % g_iScreenWidth;
		int iNewPosY = rand() % g_iScreenHeight;

		(*posArray).Set(iNewPosX, iNewPosY);
	}
}

void Background::Draw()
{
	Position *stop = pos + (sizeof(pos) / sizeof(Position));

	for (Position *posArray = pos; posArray < stop; posArray++)
	{
		float fPosX = 0.f, fPosY = 0.f;
		stop->Get(fPosX, fPosY);

		UG::DrawLine(fPosX, fPosY - 2.f, fPosX, fPosY + 2.f);
	}
}

void Background::Update()
{
	Position *stop = pos + (sizeof(pos) / sizeof(Position));
}
