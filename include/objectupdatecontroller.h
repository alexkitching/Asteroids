#ifndef _OBJECTUPDATECONTROLLER_H_
#define _OBJECTUPDATECONTROLLER_H_
#include "asteroids.h"
class oObjectUpdateController
{
public:
	void AsteroidLargeUpdate(oAsteroidLarge & a_AsteroidLarge, std::vector<oAsteroidMedium>& a_asteroidmediumarray);
	void AsteroidMediumUpdate(std::vector<oAsteroidMedium>::iterator a_AsteroidMedium, std::vector<oAsteroidSmall>& a_asteroidsmallarray);
private:

};

#endif 
