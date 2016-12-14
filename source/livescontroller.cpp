////////////////////////////////////////////////////////////////////
// File: <Livescontroller.cpp>
// Author: <Alex Kitching>
// Date Created: <12/12/16>
// Brief: <Source file for the Lives Controller Class.>
////////////////////////////////////////////////////////////////////

#include "Livescontroller.h"
#include "UGFW.h"
#include <sstream>
#include <cstring>
#include <string>

extern int g_iScreenHeight;

void oLivescontroller::DrawLives()
{
	std::stringstream str;
	str << iCurrentLives;
	std::string sCurrentLives = "Lives: " + str.str();
	const char * cCurrentLives = sCurrentLives.c_str();
	UG::DrawString(cCurrentLives, 10, g_iScreenHeight - 40);
}

int oLivescontroller::CurrentLives()
{
	return iCurrentLives;
}

void oLivescontroller::UpdateLives(int a_iNewLives)
{
	iCurrentLives += a_iNewLives;
}

void oLivescontroller::ExtraLife()
{
	++iCurrentLives;
}
