#ifndef _ASSETINIT_H_
#define _ASSETINIT_H_

#include "asteroids.h"
#include "spaceship.h"
#include "objectupdatecontroller.h"

void InitialiseGameAssets(oSpaceship& a_spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, oObjectUpdateController& a_objectupdatecontroller);

#endif // !_ASSETINIT_H_
