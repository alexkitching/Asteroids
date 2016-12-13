#ifndef _OBJECTUPDATECONTROLLER_H_
#define _OBJECTUPDATECONTROLLER_H_
#include "asteroids.h"
#include "bullet.h"
#include "spaceship.h"
#include "scorecontroller.h"
#include "livescontroller.h"
#include "GameStates.h"
#include "explosion.h"
class oObjectUpdateController
{
public:
	GameState Spaceship(oSpaceship& a_Spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, oLivesController& a_livescontroller);
	bool Bullet(oBullet& a_bullet, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray);
	void AsteroidLarge(oAsteroidLarge& a_AsteroidLarge, oAsteroidMedium* a_asteroidmediumarray, oScorecontroller& a_scorecontroller);
	void AsteroidMedium(oAsteroidMedium& a_AsteroidMedium, oAsteroidSmall* a_asteroidsmallarray, oScorecontroller& a_scorecontroller);
	void AsteroidSmall(oAsteroidSmall& a_AsteroidSmall, oScorecontroller& a_scorecontroller);
	void ReinitialiseAsteroids(oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray);
	void ResetAsteroidSpawnCount();
	bool AsteroidCheck();
	void Score(oScorecontroller& a_scorecontroller, int a_inewscore);

	int iAsteroidLargeSpawnCount = 0;
	int iAsteroidLargeDeathCount = 0;
	int iAsteroidMediumSpawnCount = 0;
	int iAsteroidMediumDeathCount = 0;
	int iAsteroidSmallSpawnCount = 0;
	int iAsteroidSmallDeathCount = 0;
	bool bAllDead = false;
private:
	

};

#endif 
