////////////////////////////////////////////////////////////////////
// File: <assetinit.h>
// Author: <Alex Kitching>
// Date Created: <10/12/16>
// Brief: <Header file for the function to Initialise Game Objects.>
////////////////////////////////////////////////////////////////////
#ifndef _ASSETINIT_H_
#define _ASSETINIT_H_

#include "asteroids.h"
#include "Spaceship.h"
#include "ObjectUpdateController.h"

void InitialiseGameAssets(oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oObjectUpdateController& a_ObjectUpdateController, oSpawncontroller a_Spawncontroller);

#endif // !_ASSETINIT_H_
