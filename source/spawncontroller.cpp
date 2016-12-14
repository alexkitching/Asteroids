////////////////////////////////////////////////////////////////////
// File: <Spawncontroller.cpp>
// Author: <Alex Kitching>
// Date Created: <6/12/16>
// Brief: <Source file for the Spawn Controller Class.>
////////////////////////////////////////////////////////////////////

#include "Spawncontroller.h"
#define NOMINMAX
#include <algorithm>

void oSpawncontroller::Spawncontroller(int a_MaxObjects, const int a_ObjectWidth, const int a_ObjectHeight)
{
	iObjectWidth = a_ObjectWidth;
	iObjectHeight = a_ObjectHeight;
	float fNewPosX = 0.f;
	float fNewPosY = 0.f;
	float fOldXPosMax = 0.f;
	float fOldXPosMin = 0.f;
	float fNewXPosMax = 0.f;
	float fNewXPosMin = 0.f;
	float fOldYPosMax = 0.f;
	float fOldYPosMin = 0.f;
	float fNewYPosMax = 0.f;
	float fNewYPosMin = 0.f;
	for (int i = 0; i < 5;)
	{
		pos.SetRandomAsteroidSpawn();
		pos.Get(fNewPosX, fNewPosY);
		if (i > 0)
		{
			fOldXPosMax = (afSpawnPosArray[i - 1][0] + 0.5f*iObjectWidth);
			fOldXPosMin = (afSpawnPosArray[i - 1][0] - 0.5f*iObjectWidth);
			fNewXPosMax = (fNewPosX + 0.5f*iObjectWidth);
			fNewXPosMin = (fNewPosX - 0.5f*iObjectWidth);
			fOldYPosMax = (afSpawnPosArray[i - 1][1] + 0.5f*iObjectHeight);
			fOldYPosMin = (afSpawnPosArray[i - 1][1] - 0.5f*iObjectHeight);
			fNewYPosMax = (fNewPosY + 0.5f*iObjectHeight);
			fNewYPosMin = (fNewPosY - 0.5f*iObjectHeight);

			//Checks for Overlap between the widths and heights of asteroids
			if (std::max(fOldXPosMax, fNewXPosMax) - std::min(fOldXPosMin, fNewXPosMin) < (fOldXPosMax - fOldXPosMin) + (fNewXPosMax - fNewXPosMin) && std::max(fOldYPosMax, fNewYPosMax) - std::min(fOldYPosMin, fNewYPosMin) < (fOldYPosMax - fOldYPosMin) + (fNewYPosMax - fNewYPosMin))
			{
				//Do Nothing
			}
			else if (std::max(fOldXPosMax, fNewXPosMax) - std::min(fOldXPosMin, fNewXPosMin) > (fOldXPosMax - fOldXPosMin) + (fNewXPosMax - fNewXPosMin) && std::max(fOldYPosMax, fNewYPosMax) - std::min(fOldYPosMin, fNewYPosMin) > (fOldYPosMax - fOldYPosMin) + (fNewYPosMax - fNewYPosMin))
			{
				afSpawnPosArray[i][0] = fNewPosX;
				afSpawnPosArray[i][1] = fNewPosY;
				i++;
			}
		}
		else if (i == 0)
		{
			afSpawnPosArray[i][0] = fNewPosX;
			afSpawnPosArray[i][1] = fNewPosY;
			i++;
		}

	}
}

void oSpawncontroller::UFOSpawncontroller(oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oScorecontroller& a_Scorecontroller)
{
	
	if (a_Scorecontroller.RoundScore() > 1200 && a_UFOEasy.CanSpawn())
	{
			a_UFOEasy.Draw();
			a_UFOEasy.SetCanSpawn(false);
	}
	if (a_Scorecontroller.RoundScore() > 2200 && a_UFOHard.CanSpawn())
	{
		a_UFOHard.Draw();
		a_UFOHard.SetCanSpawn(false);
	}

	
}
