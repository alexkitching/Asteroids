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

void InitialiseGameAssets(oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray,
						  oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray,
						  oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oObjectUpdateController& a_rObjectUpdateController,
	                      oSpawncontroller& a_rSpawncontroller)
{
	//Initialise Spaceship
	a_rSpaceship.Initialise(a_rSpaceship, a_rSpaceship.c_cSpaceshipFileName);
	a_rSpaceship.Draw(a_rSpaceship, g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f);
	a_rSpaceship.SetSpaceshipMovementKeys(a_rSpaceship, UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_SPACE, UG::KEY_ESCAPE);

	//Initialise Large Asteroids
	const int c_iLargeAsteroidHeight = 32, c_iLargeAsteroidWidth = 32;
	a_rSpawncontroller.Spawncontroller(5, c_iLargeAsteroidWidth, c_iLargeAsteroidHeight);
	for (int i = 0; i < 5; ++i)
	{
		a_paAsteroidLargeArray[i].Initialise(a_paAsteroidLargeArray[i].c_acLargeAsteroidFileName[i]);
		// Draw Large Asteroids
		a_paAsteroidLargeArray[i].Draw(a_rSpawncontroller, i);
		++a_rObjectUpdateController.iAsteroidLargeSpawnCount;
	}

	int iCycle = 0;
	//Initialise Medium Asteroids
	for (int i = 0; i < 15; i++)
	{
		if (iCycle == 0)
		{
			a_paAsteroidMediumArray[i].Initialise(a_paAsteroidMediumArray[i].c_acMediumAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_paAsteroidMediumArray[i].Initialise(a_paAsteroidMediumArray[i].c_acMediumAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_paAsteroidMediumArray[i].Initialise(a_paAsteroidMediumArray[i].c_acMediumAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise Small Asteroids
	for (int i = 0; i < 45; i++)
	{
		if (iCycle == 0)
		{
			a_paAsteroidSmallArray[i].Initialise(a_paAsteroidSmallArray[i].c_acSmallAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_paAsteroidSmallArray[i].Initialise(a_paAsteroidSmallArray[i].c_acSmallAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_paAsteroidSmallArray[i].Initialise(a_paAsteroidSmallArray[i].c_acSmallAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise UFOs
	a_rUFOEasy.Initialise(a_rUFOEasy.cUFOFileName[0]);
	a_rUFOHard.Initialise(a_rUFOHard.cUFOFileName[1]);
}