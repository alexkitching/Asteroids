////////////////////////////////////////////////////////////////////
// File: <ObjectUpdateController.cpp>
// Author: <Alex Kitching>
// Date Created: <10/12/16>
// Brief: <Source file for the Object Update Controller Class.>
////////////////////////////////////////////////////////////////////

#include "ObjectUpdateController.h"
#include "UGFW.h"
#include <stdlib.h>

extern int g_iScreenHeight;
extern int g_iScreenWidth;

oSpaceshipBullet a_rSpaceshipBulletArray[2];
oUFOBullet UFOEasyBullets;
oUFOBullet UFOHardBullets;

bool oObjectUpdateController::Spaceship(oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oLivescontroller& a_rLivescontroller, oScorecontroller& a_rScorecontroller)
{
	a_rSpaceship.CheckCollision(a_rSpaceship, a_paAsteroidLargeArray, a_paAsteroidMediumArray, a_paAsteroidSmallArray, a_rUFOEasy, a_rUFOHard, a_rLivescontroller, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount, iUFOEasyDeathCount, iUFOHardDeathCount);
	if (ClearedCheck())
	{
		ResetCount();
		a_rUFOEasy.bCanSpawn = true;
		a_rScorecontroller.ResetRoundScore();
		for (int i = 0; i < 5; ++i)
		{
			a_paAsteroidLargeArray[i].Respawn(a_paAsteroidLargeArray[i], i);
		}
		ReinitialiseAsteroids(a_paAsteroidMediumArray, a_paAsteroidSmallArray);
		a_rUFOEasy.ResetVars(a_rUFOEasy);
		a_rUFOHard.ResetVars(a_rUFOHard);
		a_rUFOEasy.Initialise(a_rUFOEasy.cUFOFileName[0]);
		a_rUFOHard.Initialise(a_rUFOHard.cUFOFileName[1]);
		bAllDead = false;
	}

	if (a_rSpaceship.bIsActive == true)
	{
		a_rSpaceship.fCurrentTurnRate = 0.f;
		a_rSpaceship.pos.Get(a_rSpaceship.fPosX, a_rSpaceship.fPosY);
		a_rSpaceship.vNew.Get(a_rSpaceship.fVNewX, a_rSpaceship.fVNewY);
		if (UG::IsKeyDown(a_rSpaceship.upKey)) // Accelerate the ship in the current facing direction
		{
			a_rSpaceship.fVNewX += a_rSpaceship.c_fAcceleration * cosf(a_rSpaceship.fFacingAngleRad);
			a_rSpaceship.fVNewY += a_rSpaceship.c_fAcceleration * sinf(a_rSpaceship.fFacingAngleRad);
			a_rSpaceship.vNew.Set(a_rSpaceship.fVNewX, a_rSpaceship.fVNewY);
			a_rSpaceship.fTotalVelocity = a_rSpaceship.vNew.Magnitude();

			//Cap Speed at Maximum Velocity
			if (a_rSpaceship.fTotalVelocity > a_rSpaceship.c_fMaxVelocity)
			{
				a_rSpaceship.fTotalVelocity = a_rSpaceship.c_fMaxVelocity;
				a_rSpaceship.fVNewX = a_rSpaceship.fTotalVelocity * cosf(a_rSpaceship.fMovementAngleRad);
				a_rSpaceship.fVNewY = a_rSpaceship.fTotalVelocity * sinf(a_rSpaceship.fMovementAngleRad);
			}

			if ((a_rSpaceship.fVNewX == 0.0) && (a_rSpaceship.fVNewY == 0.0)) // If ship is stationary the movement angle is equal to the facing angle.
			{
				a_rSpaceship.fMovementAngleRad = a_rSpaceship.fFacingAngleRad;
			}
			else if ((a_rSpaceship.fVNewX != 0.0) && (a_rSpaceship.fVNewY != 0.0)) // Else if the ship isn't stationary the movement angle is equal to the inverse tangent of the vector components.
			{
				a_rSpaceship.fMovementAngleRad = atan2f(a_rSpaceship.fVNewX, a_rSpaceship.fVNewY);
			}
		}
		if (UG::IsKeyDown(a_rSpaceship.rightKey)) //Turn Ship Right
		{
			a_rSpaceship.fCurrentTurnRate = -a_rSpaceship.c_fTurnRate;
			a_rSpaceship.fFacingAngleDeg += a_rSpaceship.fCurrentTurnRate;
			a_rSpaceship.fFacingAngleDeg = a_rSpaceship.AngleWrap(a_rSpaceship.fFacingAngleDeg);
			a_rSpaceship.fFacingAngleRad = a_rSpaceship.fFacingAngleDeg * a_rSpaceship.c_degtorad;
			UG::RotateSprite(a_rSpaceship.iSpriteID, a_rSpaceship.fCurrentTurnRate);
		}
		if (UG::IsKeyDown(a_rSpaceship.leftKey))//Turn Ship Left
		{
			a_rSpaceship.fCurrentTurnRate = a_rSpaceship.c_fTurnRate;
			a_rSpaceship.fFacingAngleDeg += a_rSpaceship.fCurrentTurnRate;
			a_rSpaceship.fFacingAngleDeg = a_rSpaceship.AngleWrap(a_rSpaceship.fFacingAngleDeg);
			a_rSpaceship.fFacingAngleRad = a_rSpaceship.fFacingAngleDeg * a_rSpaceship.c_degtorad;
			UG::RotateSprite(a_rSpaceship.iSpriteID, a_rSpaceship.fCurrentTurnRate);
		}
		if (UG::IsKeyDown(a_rSpaceship.fireKey)) //When Space Pressed, Fire Bullet
		{
			a_rSpaceship.fFireDelay -= g_fDeltaTime;
			if (a_rSpaceship.fFireDelay < 0.f) 
			{
				for (int i = 0; i < 2; ++i)
				{
					if (!a_rSpaceshipBulletArray[i].IsDrawn(a_rSpaceshipBulletArray[i]))
					{																		//Draw Bullet if not drawn
						a_rSpaceshipBulletArray[i].Draw(a_rSpaceshipBulletArray[i], a_rSpaceship.fFacingAngleRad, a_rSpaceship.fPosX, a_rSpaceship.fPosY);
						break;
					}
				}
				a_rSpaceship.fFireDelay = 0.5f;
			}
		}
		else
		{
			a_rSpaceship.fFireDelay = 0.f;
		}
		if (UG::IsKeyDown(a_rSpaceship.exitKey)) // If Escape Pressed, Exit Game
		{
			bool bQuitGameplay = true;
			return bQuitGameplay;
		}
		a_rSpaceship.fVNewX *= a_rSpaceship.c_fDrag; //Apply Drag to Movement Vector
		a_rSpaceship.fVNewY *= a_rSpaceship.c_fDrag;
		a_rSpaceship.vNew.Set(a_rSpaceship.fVNewX, a_rSpaceship.fVNewY);
		a_rSpaceship.fPosX = a_rSpaceship.fPosX + a_rSpaceship.fVNewX; //Add Movement Vector to Current Position
		a_rSpaceship.fPosY = a_rSpaceship.fPosY + a_rSpaceship.fVNewY;

		if (a_rSpaceship.fPosY >= g_iScreenHeight + a_rSpaceship.c_iHeight)	//If Spaceship goes off screen on either x or y axis,
																			//move position to opposite side.
		{
			a_rSpaceship.fPosY = (0.f * g_iScreenHeight) - a_rSpaceship.c_iHeight;
		}
		else if (a_rSpaceship.fPosY <= -a_rSpaceship.c_iHeight)
		{
			a_rSpaceship.fPosY = ((float)g_iScreenHeight + (float)a_rSpaceship.c_iHeight);
		}

		if (a_rSpaceship.fPosX >= g_iScreenWidth + a_rSpaceship.c_iWidth)
		{
			a_rSpaceship.fPosX = (0.f * g_iScreenWidth) - a_rSpaceship.c_iWidth;
		}
		else if (a_rSpaceship.fPosX <= -a_rSpaceship.c_iWidth)
		{
			a_rSpaceship.fPosX = ((float)g_iScreenWidth + (float)a_rSpaceship.c_iWidth);
		}
		UG::MoveSprite(a_rSpaceship.iSpriteID, a_rSpaceship.fPosX, a_rSpaceship.fPosY); //Move Spaceship
		a_rSpaceship.pos.Set(a_rSpaceship.fPosX, a_rSpaceship.fPosY);
	}
	if (a_rSpaceship.bIsActive == false)	//If Spaceship is Dead and Current Lives is Greater than 0
	{
		if (a_rLivescontroller.CurrentLives() > 0)
		{
			if (a_rSpaceship.fSpawnTime > a_rSpaceship.c_fMaxSpawnTime) //Start Spawn Countdown
			{
				a_rSpaceship.CheckSpawnCollision(a_rSpaceship, a_paAsteroidLargeArray, a_paAsteroidMediumArray, a_paAsteroidSmallArray);
				if (a_rSpaceship.bCollision == false)
				{										//Check if can spawn and then respawn.
					a_rSpaceship.Respawn(a_rSpaceship);
				}
				else if (a_rSpaceship.bCollision == true) //If Spawn Area Occupied, Reset Spawn Countdown
				{
					a_rSpaceship.fSpawnTime = 0.f;
				}
			}
			a_rSpaceship.fSpawnTime += g_fDeltaTime; 
		}
		else if (a_rLivescontroller.CurrentLives() <= 0)	//If Player has no lives
		{
			UG::DrawString("GAME OVER, PRESS ESCAPE TO EXIT", g_iScreenWidth * 0.18, g_iScreenHeight * 0.55);
			if (UG::IsKeyDown(a_rSpaceship.exitKey))
			{
				bool bQuitGameplay = true; //Gameover
				return bQuitGameplay;
			}
		}
	}
	for (int i = 0; i < 2; ++i)	//Update Active Bullets
	{
		if (a_rSpaceshipBulletArray[i].IsActive(a_rSpaceshipBulletArray[i]))
		{
			SpaceshipBullet(a_rSpaceshipBulletArray[i], a_paAsteroidLargeArray, a_paAsteroidMediumArray, a_paAsteroidSmallArray, a_rUFOEasy, a_rUFOHard, a_rScorecontroller);
		}
	}
	bool bQuitGameplay = false; //Else if not dead Game Not Over
	return bQuitGameplay;
}

void oObjectUpdateController::SpaceshipBullet(oSpaceshipBullet& a_rSpaceshipBullet, oAsteroidLarge* a_paAsteroidLargeArray, oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray, oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oScorecontroller& a_rScorecontroller)
{
	a_rSpaceshipBullet.pos.fX = a_rSpaceshipBullet.pos.fX + a_rSpaceshipBullet.vNew.fX; //Add Bullet Movement Vector to Current Position
	a_rSpaceshipBullet.pos.fY = a_rSpaceshipBullet.pos.fY + a_rSpaceshipBullet.vNew.fY;
	if (a_rSpaceshipBullet.pos.fY >= g_iScreenHeight + a_rSpaceshipBullet.iHeight) //If Bullet goes off screen, wrap around.
	{
		a_rSpaceshipBullet.pos.fY = (0.f * (float)g_iScreenHeight) - (float)a_rSpaceshipBullet.iHeight;
	}
	else if (a_rSpaceshipBullet.pos.fY <= -a_rSpaceshipBullet.iHeight)
	{
		a_rSpaceshipBullet.pos.fY = ((float)g_iScreenHeight + (float)a_rSpaceshipBullet.iHeight);
	}

	if (a_rSpaceshipBullet.pos.fX >= g_iScreenWidth + a_rSpaceshipBullet.iWidth)
	{
		a_rSpaceshipBullet.pos.fX = (0.f * (float)g_iScreenWidth) - (float)a_rSpaceshipBullet.iWidth;
	}
	else if (a_rSpaceshipBullet.pos.fX <= -a_rSpaceshipBullet.iWidth)
	{
		a_rSpaceshipBullet.pos.fX = ((float)g_iScreenWidth + (float)a_rSpaceshipBullet.iWidth);
	}
	UG::MoveSprite(a_rSpaceshipBullet.iSpriteID, a_rSpaceshipBullet.pos.fX, a_rSpaceshipBullet.pos.fY); //Move Bullet;
	a_rSpaceshipBullet.fCurrentDistance += a_rSpaceshipBullet.vNew.Magnitude();
	if (a_rSpaceshipBullet.fCurrentDistance >= a_rSpaceshipBullet.c_fMaxDistance)	// Compare Distance Travelled by Bullet To Maximum Distance
	{
		a_rSpaceshipBullet.Destroy(a_rSpaceshipBullet); //Destroy Bullet if Maximum Distance is Reached
	}

	a_rSpaceshipBullet.CheckCollision(a_rSpaceshipBullet, a_paAsteroidLargeArray, a_paAsteroidMediumArray, a_paAsteroidSmallArray,
		                              a_rUFOEasy, a_rUFOHard, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount,
		                              iUFOEasyDeathCount, iUFOHardDeathCount, a_rScorecontroller);	//Check for Bullet Collision
}

void oObjectUpdateController::AsteroidLarge(oAsteroidLarge & a_rAsteroidLarge, oAsteroidMedium* a_paAsteroidMediumArray)
{
	if (!a_rAsteroidLarge.HasCollided()) //If Asteroid Hasn't Collided
	{
		a_rAsteroidLarge.fPosX = a_rAsteroidLarge.fPosX + a_rAsteroidLarge.vNew.fX; //Add Asteroid Movement Vector to Current Position
		a_rAsteroidLarge.fPosY = a_rAsteroidLarge.fPosY + a_rAsteroidLarge.vNew.fY;
		if (a_rAsteroidLarge.fPosY >= g_iScreenHeight + a_rAsteroidLarge.iHeight)
		{
			a_rAsteroidLarge.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_rAsteroidLarge.iHeight; //If Asteroid goes off screen, wrap around.
		}
		else if (a_rAsteroidLarge.fPosY <= -a_rAsteroidLarge.iHeight)
		{
			a_rAsteroidLarge.fPosY = ((float)g_iScreenHeight + (float)a_rAsteroidLarge.iHeight);
		}

		if (a_rAsteroidLarge.fPosX >= g_iScreenWidth + a_rAsteroidLarge.iWidth)
		{
			a_rAsteroidLarge.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_rAsteroidLarge.iWidth;
		}
		else if (a_rAsteroidLarge.fPosX <= -a_rAsteroidLarge.iWidth)
		{
			a_rAsteroidLarge.fPosX = ((float)g_iScreenWidth + (float)a_rAsteroidLarge.iWidth);
		}
		UG::MoveSprite(a_rAsteroidLarge.iSpriteID, a_rAsteroidLarge.fPosX, a_rAsteroidLarge.fPosY); //Move Asteroid;
		UG::RotateSprite(a_rAsteroidLarge.iSpriteID, a_rAsteroidLarge.fSpriteTurnRate);	//Rotate Asteroid
	}
	else if (a_rAsteroidLarge.HasCollided())	//If Asteroid Has Collided
	{
		a_rAsteroidLarge.bIsActive = false;	//Set Not Active
		if (!a_rAsteroidLarge.bShattered)
		{
			for (int i = 0; i < 3; i++)	//Shatter Asteroid Into 3 Smaller ones at current position
			{
				a_paAsteroidMediumArray[iAsteroidMediumSpawnCount].Draw(a_rAsteroidLarge.fPosX, a_rAsteroidLarge.fPosY);
				++iAsteroidMediumSpawnCount;
			}
			a_rAsteroidLarge.bShattered = true; //Shatter has occured
		}
		a_rAsteroidLarge.ResetVars(a_rAsteroidLarge); //Reset Asteroid Variables
	}
}

void oObjectUpdateController::AsteroidMedium(oAsteroidMedium& a_rAsteroidMedium, oAsteroidSmall* a_paAsteroidSmallArray)
{
	if (!a_rAsteroidMedium.HasCollided()) //If Asteroid Hasn't Collided
	{
		a_rAsteroidMedium.fPosX = a_rAsteroidMedium.fPosX + a_rAsteroidMedium.vNew.fX;		//Add Asteroid Movement Vector to Current Position
		a_rAsteroidMedium.fPosY = a_rAsteroidMedium.fPosY + a_rAsteroidMedium.vNew.fY;
		if (a_rAsteroidMedium.fPosY >= g_iScreenHeight + a_rAsteroidMedium.iHeight)
		{
			a_rAsteroidMedium.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_rAsteroidMedium.iHeight; //If Asteroid goes off screen, wrap around.
		}
		else if (a_rAsteroidMedium.fPosY <= -a_rAsteroidMedium.iHeight)
		{
			a_rAsteroidMedium.fPosY = ((float)g_iScreenHeight + (float)a_rAsteroidMedium.iHeight);
		}

		if (a_rAsteroidMedium.fPosX >= g_iScreenWidth + a_rAsteroidMedium.iWidth)
		{
			a_rAsteroidMedium.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_rAsteroidMedium.iWidth;
		}
		else if (a_rAsteroidMedium.fPosX <= -a_rAsteroidMedium.iWidth)
		{
			a_rAsteroidMedium.fPosX = ((float)g_iScreenWidth + (float)a_rAsteroidMedium.iWidth);
		}
		UG::MoveSprite(a_rAsteroidMedium.iSpriteID, a_rAsteroidMedium.fPosX, a_rAsteroidMedium.fPosY); //Move Asteroid;
		UG::RotateSprite(a_rAsteroidMedium.iSpriteID, a_rAsteroidMedium.fSpriteTurnRate); 	//Rotate Asteroid
	}
	else if (a_rAsteroidMedium.HasCollided()) //If Asteroid Has Collided
	{
		a_rAsteroidMedium.bIsActive = false; //Set Not Active
		if (!a_rAsteroidMedium.bShattered)
		{
			for (int i = 0; i < 3; i++)  //Shatter Asteroid Into 3 Smaller ones at current position
			{
				a_paAsteroidSmallArray[iAsteroidSmallSpawnCount].Draw(a_rAsteroidMedium.fPosX, a_rAsteroidMedium.fPosY);
				++iAsteroidSmallSpawnCount;
			}
			a_rAsteroidMedium.bShattered = true; //Shatter has occured
		}
		a_rAsteroidMedium.ResetVars(a_rAsteroidMedium); //Reset Asteroid Variables
	}
}

void oObjectUpdateController::AsteroidSmall(oAsteroidSmall& a_rAsteroidSmall)
{
	if (!a_rAsteroidSmall.HasCollided()) //If Asteroid Hasn't Collided
	{
		a_rAsteroidSmall.fPosX = a_rAsteroidSmall.fPosX + a_rAsteroidSmall.vNew.fX; //Add Asteroid Movement Vector to Current Position
		a_rAsteroidSmall.fPosY = a_rAsteroidSmall.fPosY + a_rAsteroidSmall.vNew.fY;
		if (a_rAsteroidSmall.fPosY >= g_iScreenHeight + a_rAsteroidSmall.iHeight)
		{
			a_rAsteroidSmall.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_rAsteroidSmall.iHeight; //If Asteroid goes off screen, wrap around.
		}
		else if (a_rAsteroidSmall.fPosY <= -a_rAsteroidSmall.iHeight)
		{
			a_rAsteroidSmall.fPosY = ((float)g_iScreenHeight + (float)a_rAsteroidSmall.iHeight);
		}

		if (a_rAsteroidSmall.fPosX >= g_iScreenWidth + a_rAsteroidSmall.iWidth)
		{
			a_rAsteroidSmall.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_rAsteroidSmall.iWidth;
		}
		else if (a_rAsteroidSmall.fPosX <= -a_rAsteroidSmall.iWidth)
		{
			a_rAsteroidSmall.fPosX = ((float)g_iScreenWidth + (float)a_rAsteroidSmall.iWidth);
		}
		UG::MoveSprite(a_rAsteroidSmall.iSpriteID, a_rAsteroidSmall.fPosX, a_rAsteroidSmall.fPosY); //Move Asteroid;
		UG::RotateSprite(a_rAsteroidSmall.iSpriteID, a_rAsteroidSmall.fSpriteTurnRate); //Rotate Asteroid
	}
	else if (a_rAsteroidSmall.HasCollided()) //If Asteroid Has Collided
	{
		a_rAsteroidSmall.bIsActive = false; //Set Not Active
		a_rAsteroidSmall.ResetVars(a_rAsteroidSmall); //Reset Asteroid Variables
	}
}

void oObjectUpdateController::UFOEasy(oUFOEasy& a_rUFOEasy, oSpaceship& a_rSpaceship, oAsteroidLarge* a_paAsteroidLargeArray,
	                                 oAsteroidMedium* a_paAsteroidMediumArray, oAsteroidSmall* a_paAsteroidSmallArray, oLivescontroller& a_rLivescontroller)
{
	if (!a_rUFOEasy.HasCollided()) //If UFO Hasn't Collided
	{
		a_rUFOEasy.pos.fX = a_rUFOEasy.pos.fX + a_rUFOEasy.vNew.fX; //Add UFO Movement Vector to Current Position
		a_rUFOEasy.pos.fY = a_rUFOEasy.pos.fY + a_rUFOEasy.vNew.fY;

		if (a_rUFOEasy.pos.fX >= g_iScreenWidth + a_rUFOEasy.iWidth) // If UFO is Off the Right hand Side of the screen
		{
			int iRandomPos = rand() % 2; // Generate Random Number 0 or 1
			if (iRandomPos == 0)
			{
				a_rUFOEasy.pos.fX = a_rUFOEasy.posLeftTop.fX; //If 0, move UFO to top left.
				a_rUFOEasy.pos.fY = a_rUFOEasy.posLeftTop.fY;
				a_rUFOEasy.vNew = a_rUFOEasy.vRightDown; //Change Movement Vector to RightDown
			}
			else if (iRandomPos == 1)
			{
				a_rUFOEasy.pos.fX = a_rUFOEasy.posLeftBottom.fX; //If 1, move UFO to bottom left.
				a_rUFOEasy.pos.fY = a_rUFOEasy.posLeftBottom.fY;
				a_rUFOEasy.vNew = a_rUFOEasy.vRightUp; //Change Movement Vector to RightUp
			}
		}
		else if (a_rUFOEasy.pos.fX <= -a_rUFOEasy.iWidth) // If UFO Off the Left hand Side of the screen
		{
			int iRandomPos = rand() % 2; // Generate Random Number 0 or 1
			if (iRandomPos == 0)
			{
				a_rUFOEasy.pos.fX = a_rUFOEasy.posRightTop.fX; //If 0, move UFO to top right.
				a_rUFOEasy.pos.fY = a_rUFOEasy.posRightTop.fY;
				a_rUFOEasy.vNew = a_rUFOEasy.vLeftDown; //Change Movement Vector to LeftDown
			}
			else if (iRandomPos == 1)
			{
				a_rUFOEasy.pos.fX = a_rUFOEasy.posRightBottom.fX; //If 1, move UFO to bottom right.
				a_rUFOEasy.pos.fY = a_rUFOEasy.posRightBottom.fY;
				a_rUFOEasy.vNew = a_rUFOEasy.vLeftUp; //Change Movement Vector to LeftUp
			}
		}
		UG::MoveSprite(a_rUFOEasy.iSpriteID, a_rUFOEasy.pos.fX, a_rUFOEasy.pos.fY); //Move UFO

		if (a_rUFOEasy.fThinkingTime > a_rUFOEasy.fMaxThinkingTime) //If UFO can change direction
		{

			a_rUFOEasy.fThinkingTime = 0.f;
			if (!a_rUFOEasy.iDirection) //If Moving Left
			{
				if (a_rUFOEasy.vNew.fX == a_rUFOEasy.vLeftUp.fX && a_rUFOEasy.vNew.fY == a_rUFOEasy.vLeftUp.fY) // If Moving Up
				{
					a_rUFOEasy.vNew = a_rUFOEasy.vLeftDown; // Move Down
				}
				else if (a_rUFOEasy.vNew.fX == a_rUFOEasy.vLeftDown.fX && a_rUFOEasy.vNew.fY == a_rUFOEasy.vLeftDown.fY) // If Moving Down
				{
					a_rUFOEasy.vNew = a_rUFOEasy.vLeftUp; // Move Up
				}
			}
			else if (a_rUFOEasy.iDirection) //If Moving Right
			{
				if (a_rUFOEasy.vNew.fX == a_rUFOEasy.vRightUp.fX && a_rUFOEasy.vNew.fY == a_rUFOEasy.vRightUp.fY) // If Moving Up
				{
					a_rUFOEasy.vNew = a_rUFOEasy.vRightDown; // Move Down
				}
				else if (a_rUFOEasy.vNew.fX == a_rUFOEasy.vRightDown.fX && a_rUFOEasy.vNew.fY == a_rUFOEasy.vRightDown.fY) // If Moving Down
				{
					a_rUFOEasy.vNew = a_rUFOEasy.vRightUp; // Move Up
				}
			}
		}
		a_rUFOEasy.fThinkingTime += g_fDeltaTime; //Reset Thinkingtime

		if (a_rUFOEasy.fShootingDelay > a_rUFOEasy.fMaxShootingDelay) // If Can Shoot
		{
			if (UFOEasyBullets.bHasExpired) // If Bullet is Inactive
			{
				UFOEasyBullets.Draw(UFOEasyBullets, a_rUFOEasy.pos.fX, a_rUFOEasy.pos.fY, a_rUFOEasy.NewFireDirection()); //Draw New Bullet
				a_rUFOEasy.fShootingDelay = 0.f; //Reset Bullet Delay
			}
		}
		a_rUFOEasy.fShootingDelay += g_fDeltaTime;

		if (UFOEasyBullets.IsActive(UFOEasyBullets)) //If Bullet is Active
		{
			UFOBullet(UFOEasyBullets, a_rSpaceship, a_paAsteroidLargeArray, a_paAsteroidMediumArray, a_paAsteroidSmallArray, a_rLivescontroller); //Update Bullet
		}
	}
	else if (a_rUFOEasy.HasCollided()) //If UFO has collided
	{
		if (UFOEasyBullets.IsActive(UFOEasyBullets)) //Destroy all active bullets
		{
			UFOEasyBullets.Destroy(UFOEasyBullets);
		}
		a_rUFOEasy.SetIsActive(false); //Set UFO to inactive
	}
}

void oObjectUpdateController::UFOHard(oUFOHard& a_rUFOHard, oSpaceship & a_rSpaceship, oAsteroidLarge * a_paAsteroidLargeArray, oAsteroidMedium * a_paAsteroidMediumArray, oAsteroidSmall * a_paAsteroidSmallArray, oLivescontroller & a_rLivescontroller)
{
	if (!a_rUFOHard.HasCollided()) //If UFO hasn't collided
	{
		a_rUFOHard.pos.fX = a_rUFOHard.pos.fX + a_rUFOHard.vNew.fX; //Add Movement Vector to Current Position
		a_rUFOHard.pos.fY = a_rUFOHard.pos.fY + a_rUFOHard.vNew.fY;

		if (a_rUFOHard.pos.fX >= g_iScreenWidth + a_rUFOHard.iWidth) // If UFO is Off the Right hand Side of the screen
		{
			int iRandomPos = rand() % 2; // Generate Random Number 0 or 1
			if (iRandomPos == 0)
			{
				a_rUFOHard.pos.fX = a_rUFOHard.posLeftTop.fX; //If 0, move UFO to top left.
				a_rUFOHard.pos.fY = a_rUFOHard.posLeftTop.fY;
				a_rUFOHard.vNew = a_rUFOHard.vRight; //Set Movement Direction to Right;
			}
			else if (iRandomPos == 1)
			{
				a_rUFOHard.pos.fX = a_rUFOHard.posLeftBottom.fX; //If 1, move UFO to bottom left.
				a_rUFOHard.pos.fY = a_rUFOHard.posLeftBottom.fY;
				a_rUFOHard.vNew = a_rUFOHard.vRight; //Set Movement Direction to Right;
			}
		}
		else if (a_rUFOHard.pos.fX <= -a_rUFOHard.iWidth) // If UFO Off the Left hand Side
		{
			int iRandomPos = rand() % 2; // Generate Random Number 0 or 1
			if (iRandomPos == 0)
			{
				a_rUFOHard.pos.fX = a_rUFOHard.posRightTop.fX; // If 0, move UFO to Top Right
				a_rUFOHard.pos.fY = a_rUFOHard.posRightTop.fY;
				a_rUFOHard.vNew = a_rUFOHard.vLeft; // Set Movement Direction to Left
			}
			else if (iRandomPos == 1)
			{
				a_rUFOHard.pos.fX = a_rUFOHard.posRightBottom.fX; // If 1, move UFO to Bottom Right
				a_rUFOHard.pos.fY = a_rUFOHard.posRightBottom.fY;
				a_rUFOHard.vNew = a_rUFOHard.vLeft; // Set Movement Direction to Left
			}
		}
		UG::MoveSprite(a_rUFOHard.iSpriteID, a_rUFOHard.pos.fX, a_rUFOHard.pos.fY); // Move UFO

		if (a_rUFOHard.fThinkingTime > a_rUFOHard.fMaxThinkingTime) //If UFO can change direction
		{
			int iChangeDirection = rand() % 2; // Generate Random Number 0 or 1
			if (iChangeDirection == 0)
			{
				a_rUFOHard.vNew = a_rUFOHard.vLeft; // If 0 Change Direction to Left
			}
			else if (iChangeDirection == 1)
			{
				a_rUFOHard.vNew = a_rUFOHard.vRight; // If 1 Change Direction to Right
			}
			a_rUFOHard.fThinkingTime = 0.f;
		}
		a_rUFOHard.fThinkingTime += g_fDeltaTime; // Reset Thinking Time

		if (a_rUFOHard.fShootingDelay > a_rUFOHard.fMaxShootingDelay && a_rSpaceship.bIsActive == true) //If UFO Can Shoot
		{

			if (UFOHardBullets.bHasExpired) //And Bullet has expired
			{																							//Draw New Bullet
				UFOHardBullets.Draw(UFOHardBullets, a_rUFOHard.pos.fX, a_rUFOHard.pos.fY, UFOHardBullets.NewFireDirection(a_rUFOHard, a_rSpaceship));
				a_rUFOHard.fShootingDelay = 0.f;
			}

		}

		a_rUFOHard.fShootingDelay += g_fDeltaTime; //Reset Shoot Delay

		if (UFOHardBullets.IsActive(UFOHardBullets)) // If Bullets are active
		{
			UFOBullet(UFOHardBullets, a_rSpaceship, a_paAsteroidLargeArray, a_paAsteroidMediumArray,
										a_paAsteroidSmallArray, a_rLivescontroller); //Update Bullets
		}

	}
	else if (a_rUFOHard.HasCollided()) //If UFO has Collided
	{
		if (UFOHardBullets.IsActive(UFOHardBullets)) // Destroy any active bullets
		{
			UFOHardBullets.Destroy(UFOHardBullets);
		}

		a_rUFOHard.SetIsActive(false); // Set Active to false
	}
}

void oObjectUpdateController::UFOBullet(oUFOBullet & a_rUFOBullet, oSpaceship& a_rSpaceship, oAsteroidLarge * a_paAsteroidLargeArray,
	                          oAsteroidMedium * a_paAsteroidMediumArray, oAsteroidSmall * a_paAsteroidSmallArray, oLivescontroller& a_rLivescontroller)
{
	a_rUFOBullet.pos.fX = a_rUFOBullet.pos.fX + a_rUFOBullet.vNew.fX; //Add Movement Vector to Current Position
	a_rUFOBullet.pos.fY = a_rUFOBullet.pos.fY + a_rUFOBullet.vNew.fY;
	if (a_rUFOBullet.pos.fY >= g_iScreenHeight + a_rUFOBullet.iHeight) //If off screen, wrap around
	{
		a_rUFOBullet.pos.fY = (0.f * (float)g_iScreenHeight) - (float)a_rUFOBullet.iHeight;
	}
	else if (a_rUFOBullet.pos.fY <= -a_rUFOBullet.iHeight)
	{
		a_rUFOBullet.pos.fY = ((float)g_iScreenHeight + (float)a_rUFOBullet.iHeight);
	}

	if (a_rUFOBullet.pos.fX >= g_iScreenWidth + a_rUFOBullet.iWidth)
	{
		a_rUFOBullet.pos.fX = (0.f * (float)g_iScreenWidth) - (float)a_rUFOBullet.iWidth;
	}
	else if (a_rUFOBullet.pos.fX <= -a_rUFOBullet.iWidth)
	{
		a_rUFOBullet.pos.fX = ((float)g_iScreenWidth + (float)a_rUFOBullet.iWidth);
	}
	UG::MoveSprite(a_rUFOBullet.iSpriteID, a_rUFOBullet.pos.fX, a_rUFOBullet.pos.fY); //Move Bullet
	a_rUFOBullet.fCurrentDistance += a_rUFOBullet.vNew.Magnitude();
	if (a_rUFOBullet.fCurrentDistance >= a_rUFOBullet.c_fMaxDistance)
	{
		a_rUFOBullet.Destroy(a_rUFOBullet); //If Bullet has expired, Destroy Bullet
	}																						//Check Bullet Collision
	a_rUFOBullet.CheckCollision(a_rUFOBullet, a_rSpaceship, a_paAsteroidLargeArray, a_paAsteroidMediumArray, a_paAsteroidSmallArray,
								a_rLivescontroller, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount);
}

void oObjectUpdateController::ReinitialiseAsteroids(oAsteroidMedium * a_paAsteroidMediumArray, oAsteroidSmall * a_paAsteroidSmallArray)
{
	int iCycle = 0;
	//Initialise Medium Asteroids
	for (int i = 0; i < 15; i++)
	{
		if (iCycle == 0) //Cycles Through Sprites
		{
			a_paAsteroidMediumArray[i].Initialise(a_paAsteroidMediumArray[i].c_acMediumAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_paAsteroidMediumArray[i].Initialise(a_paAsteroidMediumArray[i].c_acMediumAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_paAsteroidMediumArray[i].Initialise(a_paAsteroidMediumArray[i].c_acMediumAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise Small Asteroids
	for (int i = 0; i < 45; i++)
	{
		if (iCycle == 0) //Cycles Through Sprites
		{
			a_paAsteroidSmallArray[i].Initialise(a_paAsteroidSmallArray[i].c_acSmallAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_paAsteroidSmallArray[i].Initialise(a_paAsteroidSmallArray[i].c_acSmallAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_paAsteroidSmallArray[i].Initialise(a_paAsteroidSmallArray[i].c_acSmallAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}
}

void oObjectUpdateController::ResetCount()
{
	iAsteroidLargeSpawnCount = 0; //Resets EnemyCounters
	iAsteroidLargeDeathCount = 0;
	iAsteroidMediumSpawnCount = 0;
	iAsteroidMediumDeathCount = 0;
	iAsteroidSmallSpawnCount = 0;
	iAsteroidSmallDeathCount = 0;
	iUFOEasyDeathCount = 0;
	iUFOHardDeathCount = 0;
}



bool oObjectUpdateController::ClearedCheck()
{
	if (iAsteroidLargeDeathCount == 5 && iAsteroidMediumDeathCount == 15 && iAsteroidSmallDeathCount == 45 &&
		iUFOEasyDeathCount == 1 && iUFOHardDeathCount == 1) //If Round is Clear
	{
		bAllDead = true; //Set All Dead True
	}
	return bAllDead;
}
