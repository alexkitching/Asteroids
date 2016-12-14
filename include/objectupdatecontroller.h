////////////////////////////////////////////////////////////////////
// File: <ObjectUpdateController.h>
// Author: <Alex Kitching>
// Date Created: <10/12/16>
// Brief: <Header file for the Object Update Controller Class.>
////////////////////////////////////////////////////////////////////
#ifndef _ObjectUpdateController_H_
#define _ObjectUpdateController_H_

#include "asteroids.h"
#include "bullet.h"
#include "spaceship.h"
#include "ufo.h"
#include "scorecontroller.h"
#include "livescontroller.h"
#include "GameStates.h"

class oObjectUpdateController
{
public:

	oObjectUpdateController() {}; //Constructor
	~oObjectUpdateController() {}; //Destructor

	//Functions
	bool Spaceship(oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
		           oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oLivescontroller& a_rLivescontroller,
		           oScorecontroller& a_rScorecontroller);
	void SpaceshipBullet(oSpaceshipBullet& a_rSpaceshipBullet, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
		                 oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oScorecontroller& a_rScorecontroller);
	void AsteroidLarge(oAsteroidLarge& a_rAsteroidLarge, oAsteroidMedium* a_paAsteroidMediumArray);
	void AsteroidMedium(oAsteroidMedium& a_rAsteroidMedium, oAsteroidSmall* a_paAsteroidSmallArray);
	void AsteroidSmall(oAsteroidSmall& a_rAsteroidSmall);
	void UFOEasy(oUFOEasy& a_rUFOEasy, oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
		         oAsteroidSmall* a_paAsteroidSmallArray, oLivescontroller& a_rLivescontroller);
	void UFOHard(oUFOHard& a_rUFOHard, oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
		         oAsteroidSmall* a_paAsteroidSmallArray, oLivescontroller& a_rLivescontroller);
	void UFOBullet(oUFOBullet& a_rUFOBullet, oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray,
		           oAsteroidSmall* a_paAsteroidSmallArray, oLivescontroller& a_rLivescontroller);
	void ReinitialiseAsteroids(oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray);
	void ResetCount();
	bool ClearedCheck();

	//Object Count Variables
	int iAsteroidLargeSpawnCount = 0;
	int iAsteroidLargeDeathCount = 0;
	int iAsteroidMediumSpawnCount = 0;
	int iAsteroidMediumDeathCount = 0;
	int iAsteroidSmallSpawnCount = 0;
	int iAsteroidSmallDeathCount = 0;
	int iUFOEasyDeathCount = 0;
	int iUFOHardDeathCount = 0;
	bool bAllDead = false;

private:
	

};

#endif // !_ObjectUpdateController_H_
