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
	oObjectUpdateController() {};
	~oObjectUpdateController() {};
	bool Spaceship(oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oLivescontroller& a_Livescontroller, oScorecontroller& a_Scorecontroller);
	void SpaceshipBullet(oSpaceshipBullet& a_Spaceshipbullet, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oScorecontroller& a_Scorecontroller);
	void AsteroidLarge(oAsteroidLarge& a_AsteroidLarge, oAsteroidMedium* a_aAsteroidMediumArray);
	void AsteroidMedium(oAsteroidMedium& a_AsteroidMedium, oAsteroidSmall* a_aAsteroidSmallArray);
	void AsteroidSmall(oAsteroidSmall& a_AsteroidSmall);
	void UFOEasy(oUFOEasy & a_UFOEasy, oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oLivescontroller& a_Livescontroller);
	void UFOHard(oUFOHard & a_UFOHard, oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oLivescontroller& a_Livescontroller);
	void UFOBullet(oUFOBullet& a_UFOBullet, oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oLivescontroller& a_Livescontroller);
	void ReinitialiseAsteroids(oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray);
	void ResetCount();
	bool ClearedCheck();

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
