////////////////////////////////////////////////////////////////////
// File: <Scorecontroller.cpp>
// Author: <Alex Kitching>
// Date Created: <12/12/16>
// Brief: <Source file for the Score Controller Class.>
////////////////////////////////////////////////////////////////////

#include "Scorecontroller.h"
#include "UGFW.h"
#include <sstream>
#include <cstring>
#include <string>

extern int g_iScreenHeight;

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
	iRoundScore += a_inewscore;
	iLivesScore += a_inewscore;
}

void oScorecontroller::ResetRoundScore()
{
	iRoundScore = 0;
}

void oScorecontroller::ResetLivesScore()
{
	iLivesScore = 0;
}

int oScorecontroller::CurrentScore()
{
	return iCurrentScore;
}

int oScorecontroller::RoundScore()
{
	return iRoundScore;
}

int oScorecontroller::LivesScore()
{
	return iLivesScore;
}
