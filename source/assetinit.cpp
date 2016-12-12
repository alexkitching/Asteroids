#include "assetinit.h"
#include "UGFW.h"
#include "Enumerations.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

void InitialiseGameAssets(oSpaceship& a_spaceship, std::vector<oAsteroidLarge>& a_asteroidlargearray)
{
	//Initialise Spaceship
	a_spaceship.Initialise(a_spaceship, "./images/Ship.png", g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f);
	a_spaceship.SetSpaceshipMovementKeys(a_spaceship, UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_P, UG::KEY_SPACE);
	UG::DrawSprite(a_spaceship.iSpriteID);

	//Initialise Each Large Asteroid
	int iLargeAsteroidHeight = 32, iLargeAsteroidWidth = 32;
	oSpawnController spawncontroller;
	spawncontroller.SpawnController(5, iLargeAsteroidWidth, iLargeAsteroidHeight);
	for (int i = 0; i < 5; ++i)
	{
		a_asteroidlargearray.push_back(oAsteroidLarge(spawncontroller, i));
	}
}