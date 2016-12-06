#include "spawncontroller.h"
#define NOMINMAX
#include "algorithm"

oSpawnController::oSpawnController()
{
}

void oSpawnController::SpawnController(int a_MaxObjects, int a_ObjectWidth, int a_ObjectHeight)
{
	iObjectWidth = a_ObjectWidth;
	iObjectHeight = a_ObjectHeight;
	for (int i = 0; i < 4;)
	{
		pos.SetRandom();
		pos.Get(fNewPosX, fNewPosY);
		if (i > 0)
		{
			fOldXPosMax = (iSpawnPosArray[i - 1][0] + 0.5*iObjectWidth);
			fOldXPosMin = (iSpawnPosArray[i - 1][0] - 0.5*iObjectWidth);
			fNewXPosMax = (fNewPosX + 0.5*iObjectWidth);
			fNewXPosMin = (fNewPosX - 0.5*iObjectWidth);
			fOldYPosMax = (iSpawnPosArray[i - 1][1] + 0.5*iObjectHeight);
			fOldYPosMin = (iSpawnPosArray[i - 1][1] - 0.5*iObjectHeight);
			fNewYPosMax = (fNewPosY + 0.5*iObjectHeight);
			fNewYPosMin = (fNewPosY - 0.5*iObjectHeight);

			//Checks for Overlap between the widths and heights of asteroids
			if (std::max(fOldXPosMax, fNewXPosMax) - std::min(fOldXPosMin, fNewXPosMin) < (fOldXPosMax - fOldXPosMin) + (fNewXPosMax - fNewXPosMin) && std::max(fOldYPosMax, fNewYPosMax) - std::min(fOldYPosMin, fNewYPosMin) < (fOldYPosMax - fOldYPosMin) + (fNewYPosMax - fNewYPosMin))
			{
			//Do Nothing
			}
			else if (std::max(fOldXPosMax, fNewXPosMax) - std::min(fOldXPosMin, fNewXPosMin) > (fOldXPosMax - fOldXPosMin) + (fNewXPosMax - fNewXPosMin) && std::max(fOldYPosMax, fNewYPosMax) - std::min(fOldYPosMin, fNewYPosMin) > (fOldYPosMax - fOldYPosMin) + (fNewYPosMax - fNewYPosMin))
			{
				iSpawnPosArray[i][0] = fNewPosX;
				iSpawnPosArray[i][1] = fNewPosY;
				i++;
			}
		}
		else if (i == 0)
		{
			iSpawnPosArray[i][0] = fNewPosX;
			iSpawnPosArray[i][1] = fNewPosY;
			i++;
		}

	}
}
