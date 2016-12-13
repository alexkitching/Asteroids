#include "assetinit.h"
#include "UGFW.h"
#include "Enumerations.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

void InitialiseGameAssets(oSpaceship& a_spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, oObjectUpdateController& a_objectupdatecontroller)
{
	//Initialise Spaceship
	a_spaceship.Initialise(a_spaceship, a_spaceship.cSpaceshipFileName);
	a_spaceship.Draw(a_spaceship, g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f);
	a_spaceship.SetSpaceshipMovementKeys(a_spaceship, UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_P, UG::KEY_SPACE, UG::KEY_ESCAPE);

	//Initialise Large Asteroids
	int iLargeAsteroidHeight = 32, iLargeAsteroidWidth = 32;
	oSpawnController spawncontroller;
	spawncontroller.SpawnController(5, iLargeAsteroidWidth, iLargeAsteroidHeight);
	for (int i = 0; i < 5; ++i)
	{
		a_asteroidlargearray[i].Initialise(a_asteroidlargearray[i].cLargeAsteroidFileName[i]);
		// Draw Large Asteroids
		a_asteroidlargearray[i].Draw(spawncontroller, i);
		++a_objectupdatecontroller.iAsteroidLargeSpawnCount;
	}

	int iCycle = 0;
	//Initialise Medium Asteroids
	for (int i = 0; i < 15; i++)
	{
		if (iCycle == 0)
		{
			a_asteroidmediumarray[i].Initialise(a_asteroidmediumarray[i].cMediumAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_asteroidmediumarray[i].Initialise(a_asteroidmediumarray[i].cMediumAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_asteroidmediumarray[i].Initialise(a_asteroidmediumarray[i].cMediumAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise Small Asteroids
	for (int i = 0; i < 45; i++)
	{
		if (iCycle == 0)
		{
			a_asteroidsmallarray[i].Initialise(a_asteroidsmallarray[i].cSmallAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_asteroidsmallarray[i].Initialise(a_asteroidsmallarray[i].cSmallAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_asteroidsmallarray[i].Initialise(a_asteroidsmallarray[i].cSmallAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}
}