#ifndef _OBJECTUPDATECONTROLLER_H_
#define _OBJECTUPDATECONTROLLER_H_
#include "asteroids.h"
#include "bullet.h"
#include "spaceship.h"
#include "scorecontroller.h"
#include "livescontroller.h"
#include "explosion.h"
class oObjectUpdateController
{
public:
	void SpaceshipUpdate(oSpaceship& a_Spaceship, std::vector<oAsteroidLarge>& a_asteroidlargearray, std::vector<oAsteroidMedium>& a_asteroidmediumarray, std::vector<oAsteroidSmall>& a_asteroidsmallarray, oLivesController& a_livescontroller);
	bool BulletUpdate(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet);
	void AsteroidLargeUpdate(oAsteroidLarge & a_AsteroidLarge, std::vector<oAsteroidMedium>& a_asteroidmediumarray, oScorecontroller& a_scorecontroller);
	void AsteroidMediumUpdate(std::vector<oAsteroidMedium>::iterator a_AsteroidMedium, std::vector<oAsteroidSmall>& a_asteroidsmallarray, oScorecontroller& a_scorecontroller);
	void AsteroidSmallUpdate(std::vector<oAsteroidSmall>::iterator a_AsteroidSmall, oScorecontroller& a_scorecontroller);
	void ScoreUpdate(oScorecontroller& a_scorecontroller, int a_inewscore);
private:

};

#endif 
