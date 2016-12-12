#include "scorecontroller.h"
#include "UGFW.h"
#include <sstream>
#include <cstring>
#include <string>

extern int g_iScreenHeight;

oScorecontroller::oScorecontroller()
{
}

void oScorecontroller::DrawScore()
{
	std::stringstream str;
	str << iCurrentScore;
	std::string sCurrentScore = str.str();
	const char * cCurrentScore = sCurrentScore.c_str();
	UG::DrawString(cCurrentScore, 10 , g_iScreenHeight - 10);
}

void oScorecontroller::UpdateScore(int a_inewscore)
{
	iCurrentScore += a_inewscore;
}
