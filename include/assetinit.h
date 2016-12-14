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

//Declare Function
void InitialiseGameAssets(oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray,
							oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray,
							oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oObjectUpdateController& a_rObjectUpdateController,
							oSpawncontroller& a_rSpawncontroller);

#endif // !_ASSETINIT_H_
