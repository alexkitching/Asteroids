////////////////////////////////////////////////////////////////////
// File: <assetinit.cpp>
// Author: <Alex Kitching>
// Date Created: <10/12/16>
// Brief: <Source file for the function to Initialise Game Objects.>
////////////////////////////////////////////////////////////////////

#include "assetinit.h"
#include "UGFW.h"
#include <Enumerations.h>

extern int g_iScreenHeight;
extern int g_iScreenWidth;

void InitialiseGameAssets(oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oObjectUpdateController& a_ObjectUpdateController, oSpawncontroller a_Spawncontroller)
{
	//Initialise Spaceship
	a_Spaceship.Initialise(a_Spaceship, a_Spaceship.c_cSpaceshipFileName);
	a_Spaceship.Draw(a_Spaceship, g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f);
	a_Spaceship.SetSpaceshipMovementKeys(a_Spaceship, UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_SPACE, UG::KEY_ESCAPE);

	//Initialise Large Asteroids
	const int c_iLargeAsteroidHeight = 32, const c_iLargeAsteroidWidth = 32;
	a_Spawncontroller.Spawncontroller(5, c_iLargeAsteroidWidth, c_iLargeAsteroidHeight);
	for (int i = 0; i < 5; ++i)
	{
		a_aAsteroidLargeArray[i].Initialise(a_aAsteroidLargeArray[i].c_cLargeAsteroidFileName[i]);
		// Draw Large Asteroids
		a_aAsteroidLargeArray[i].Draw(a_Spawncontroller, i);
		++a_ObjectUpdateController.iAsteroidLargeSpawnCount;
	}

	int iCycle = 0;
	//Initialise Medium Asteroids
	for (int i = 0; i < 15; i++)
	{
		if (iCycle == 0)
		{
			a_aAsteroidMediumArray[i].Initialise(a_aAsteroidMediumArray[i].c_cMediumAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_aAsteroidMediumArray[i].Initialise(a_aAsteroidMediumArray[i].c_cMediumAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_aAsteroidMediumArray[i].Initialise(a_aAsteroidMediumArray[i].c_cMediumAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise Small Asteroids
	for (int i = 0; i < 45; i++)
	{
		if (iCycle == 0)
		{
			a_aAsteroidSmallArray[i].Initialise(a_aAsteroidSmallArray[i].c_cSmallAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_aAsteroidSmallArray[i].Initialise(a_aAsteroidSmallArray[i].c_cSmallAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_aAsteroidSmallArray[i].Initialise(a_aAsteroidSmallArray[i].c_cSmallAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise UFOs
	a_UFOEasy.Initialise(a_UFOEasy.cUFOFileName[0]);
	a_UFOHard.Initialise(a_UFOHard.cUFOFileName[1]);
}