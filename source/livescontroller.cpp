#include "livescontroller.h"
#include "UGFW.h"
#include <sstream>
#include <cstring>
#include <string>

extern int g_iScreenHeight;

oLivesController::oLivesController()
{
}

void oLivesController::DrawLives()
{
	std::stringstream str;
	str << iCurrentLives;
	std::string sCurrentLives = "Lives: " + str.str();
	const char * cCurrentLives = sCurrentLives.c_str();
	UG::DrawString(cCurrentLives, 10, g_iScreenHeight - 40);
}

void oLivesController::UpdateLives(int a_inewlives)
{
	iCurrentLives += a_inewlives;
}
