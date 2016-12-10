#include "assetinit.h"
#include "UGFW.h"
#include "Enumerations.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

void InitialiseGameAssets(oSpaceship& a_spaceship, oAsteroidLarge* a_asteroidlargearray)
{

	//Initialise Spaceship
	float fHalfSize = 0.5f;
	a_spaceship.Initialise(a_spaceship, "./images/Ship.png", g_iScreenWidth * fHalfSize, g_iScreenHeight *fHalfSize);
	a_spaceship.SetSpaceshipMovementKeys(a_spaceship, UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_P, UG::KEY_SPACE);
	UG::DrawSprite(a_spaceship.iSpriteID);

	//Initialise Each Large Asteroid
	int iLargeAsteroidHeight = 0, iLargeAsteroidWidth = 0;
	a_asteroidlargearray[1].GetDimensions(iLargeAsteroidWidth, iLargeAsteroidHeight);
	oSpawnController spawncontroller;
	spawncontroller.SpawnController(5, iLargeAsteroidWidth, iLargeAsteroidHeight);
	char cSpriteFileName[5][35] = { { "./images/LargeAsteroid1.png" },{ "./images/LargeAsteroid2.png" },{ "./images/LargeAsteroid3.png" },{ "./images/LargeAsteroid4.png" },{ "./images/LargeAsteroid1.png" } };
	for (int i = 0; i < 5; ++i)
	{
		a_asteroidlargearray[i].Initialise(spawncontroller, i, cSpriteFileName[i]);
	}
}