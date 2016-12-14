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

oSpaceshipBullet a_SpaceshipBulletArray[2];
oUFOBullet UFOEasyBullets;
oUFOBullet UFOHardBullets;

bool oObjectUpdateController::Spaceship(oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oLivescontroller& a_Livescontroller, oScorecontroller& a_Scorecontroller)
{
	a_Spaceship.CheckCollision(a_Spaceship, a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray, a_UFOEasy, a_UFOHard, a_Livescontroller, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount, iUFOEasyDeathCount, iUFOHardDeathCount);
	if (ClearedCheck())
	{
		ResetCount();
		a_UFOEasy.bCanSpawn = true;
		a_Scorecontroller.ResetRoundScore();
		for (int i = 0; i < 5; ++i)
		{
			a_aAsteroidLargeArray[i].Respawn(a_aAsteroidLargeArray[i], i);
		}
		ReinitialiseAsteroids(a_aAsteroidMediumArray, a_aAsteroidSmallArray);
		a_UFOEasy.ResetVars(a_UFOEasy);
		a_UFOHard.ResetVars(a_UFOHard);
		a_UFOEasy.Initialise(a_UFOEasy.cUFOFileName[0]);
		a_UFOHard.Initialise(a_UFOHard.cUFOFileName[1]);
		bAllDead = false;
	}

	if (a_Spaceship.bIsActive == true)
	{
		a_Spaceship.fCurrentTurnRate = 0.f;
		a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
		a_Spaceship.vNew.Get(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
		if (UG::IsKeyDown(a_Spaceship.upKey)) // Accelerate the ship in the current facing direction
		{
			a_Spaceship.fVNewX += a_Spaceship.c_fAcceleration * cosf(a_Spaceship.fFacingAngleRad);
			a_Spaceship.fVNewY += a_Spaceship.c_fAcceleration * sinf(a_Spaceship.fFacingAngleRad);
			a_Spaceship.vNew.Set(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
			a_Spaceship.fTotalVelocity = a_Spaceship.vNew.Magnitude();

			//Cap Speed at Maximum Velocity
			if (a_Spaceship.fTotalVelocity > a_Spaceship.c_fMaxVelocity)
			{
				a_Spaceship.fTotalVelocity = a_Spaceship.c_fMaxVelocity;
				a_Spaceship.fVNewX = a_Spaceship.fTotalVelocity * cosf(a_Spaceship.fMovementAngleRad);
				a_Spaceship.fVNewY = a_Spaceship.fTotalVelocity * sinf(a_Spaceship.fMovementAngleRad);
			}

			if ((a_Spaceship.fVNewX == 0.0) && (a_Spaceship.fVNewY == 0.0)) // If ship is stationary the movement angle is equal to the facing angle.
			{
				a_Spaceship.fMovementAngleRad = a_Spaceship.fFacingAngleRad;
			}
			else if ((a_Spaceship.fVNewX != 0.0) && (a_Spaceship.fVNewY != 0.0)) // Else if the ship isn't stationary the movement angle is equal to the inverse tangent of the vector components.
			{
				a_Spaceship.fMovementAngleRad = atan2f(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
			}
		}
		if (UG::IsKeyDown(a_Spaceship.rightKey))
		{
			a_Spaceship.fCurrentTurnRate = -a_Spaceship.c_fTurnRate;
			a_Spaceship.fFacingAngleDeg += a_Spaceship.fCurrentTurnRate;
			a_Spaceship.fFacingAngleDeg = a_Spaceship.AngleWrap(a_Spaceship.fFacingAngleDeg);
			a_Spaceship.fFacingAngleRad = a_Spaceship.fFacingAngleDeg * a_Spaceship.c_degtorad;
			UG::RotateSprite(a_Spaceship.iSpriteID, a_Spaceship.fCurrentTurnRate);
		}
		if (UG::IsKeyDown(a_Spaceship.leftKey))
		{
			a_Spaceship.fCurrentTurnRate = a_Spaceship.c_fTurnRate;
			a_Spaceship.fFacingAngleDeg += a_Spaceship.fCurrentTurnRate;
			a_Spaceship.fFacingAngleDeg = a_Spaceship.AngleWrap(a_Spaceship.fFacingAngleDeg);
			a_Spaceship.fFacingAngleRad = a_Spaceship.fFacingAngleDeg * a_Spaceship.c_degtorad;
			UG::RotateSprite(a_Spaceship.iSpriteID, a_Spaceship.fCurrentTurnRate);
		}
		if (UG::IsKeyDown(a_Spaceship.fireKey))
		{
			a_Spaceship.fFireDelay -= g_fDeltaTime;
			if (a_Spaceship.fFireDelay < 0.f)
			{
				for (int i = 0; i < 2; ++i)
				{
					if (!a_SpaceshipBulletArray[i].IsDrawn(a_SpaceshipBulletArray[i]))
					{
						a_SpaceshipBulletArray[i].Draw(a_SpaceshipBulletArray[i], a_Spaceship.fFacingAngleRad, a_Spaceship.fPosX, a_Spaceship.fPosY);
						break;
					}
				}
				a_Spaceship.fFireDelay = 0.5f;
			}
		}
		else
		{
			a_Spaceship.fFireDelay = 0.f;
		}
		if (UG::IsKeyDown(a_Spaceship.exitKey))
		{
			bool bQuitGameplay = true;
			return bQuitGameplay;
		}
		a_Spaceship.fVNewX *= a_Spaceship.c_fDrag;
		a_Spaceship.fVNewY *= a_Spaceship.c_fDrag;
		a_Spaceship.vNew.Set(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
		a_Spaceship.fPosX = a_Spaceship.fPosX + a_Spaceship.fVNewX;
		a_Spaceship.fPosY = a_Spaceship.fPosY + a_Spaceship.fVNewY;

		if (a_Spaceship.fPosY >= g_iScreenHeight + a_Spaceship.c_iHeight)
		{
			a_Spaceship.fPosY = (0.f * g_iScreenHeight) - a_Spaceship.c_iHeight;
		}
		else if (a_Spaceship.fPosY <= -a_Spaceship.c_iHeight)
		{
			a_Spaceship.fPosY = ((float)g_iScreenHeight + (float)a_Spaceship.c_iHeight);
		}

		if (a_Spaceship.fPosX >= g_iScreenWidth + a_Spaceship.c_iWidth)
		{
			a_Spaceship.fPosX = (0.f * g_iScreenWidth) - a_Spaceship.c_iWidth;
		}
		else if (a_Spaceship.fPosX <= -a_Spaceship.c_iWidth)
		{
			a_Spaceship.fPosX = ((float)g_iScreenWidth + (float)a_Spaceship.c_iWidth);
		}
		UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
		a_Spaceship.pos.Set(a_Spaceship.fPosX, a_Spaceship.fPosY);
	}
	if (a_Spaceship.bIsActive == false)
	{
		if (a_Livescontroller.CurrentLives() > 0)
		{
			if (a_Spaceship.fSpawnTime > a_Spaceship.c_fMaxSpawnTime)
			{
				a_Spaceship.CheckSpawnCollision(a_Spaceship, a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray);
				if (a_Spaceship.bCollision == false)
				{
					a_Spaceship.Respawn(a_Spaceship);
				}
				else if (a_Spaceship.bCollision == true)
				{
					a_Spaceship.fSpawnTime = 0.f;
				}
			}
			a_Spaceship.fSpawnTime += g_fDeltaTime;
		}
		else if (a_Livescontroller.CurrentLives() <= 0)
		{
			UG::DrawString("GAME OVER, PRESS ESCAPE TO EXIT", g_iScreenWidth * 0.18, g_iScreenHeight * 0.55);
			if (UG::IsKeyDown(a_Spaceship.exitKey))
			{
				bool bQuitGameplay = true;
				return bQuitGameplay;
			}
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		if (a_SpaceshipBulletArray[i].IsActive(a_SpaceshipBulletArray[i]))
		{
			SpaceshipBullet(a_SpaceshipBulletArray[i], a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray, a_UFOEasy, a_UFOHard, a_Scorecontroller);
		}
	}
}

void oObjectUpdateController::SpaceshipBullet(oSpaceshipBullet& a_Spaceshipbullet, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oUFOEasy& a_UFOEasy, oUFOHard& a_UFOHard, oScorecontroller& a_Scorecontroller)
{
	a_Spaceshipbullet.pos.fX = a_Spaceshipbullet.pos.fX + a_Spaceshipbullet.vNew.fX;
	a_Spaceshipbullet.pos.fY = a_Spaceshipbullet.pos.fY + a_Spaceshipbullet.vNew.fY;
	if (a_Spaceshipbullet.pos.fY >= g_iScreenHeight + a_Spaceshipbullet.iHeight)
	{
		a_Spaceshipbullet.pos.fY = (0.f * (float)g_iScreenHeight) - (float)a_Spaceshipbullet.iHeight;
	}
	else if (a_Spaceshipbullet.pos.fY <= -a_Spaceshipbullet.iHeight)
	{
		a_Spaceshipbullet.pos.fY = ((float)g_iScreenHeight + (float)a_Spaceshipbullet.iHeight);
	}

	if (a_Spaceshipbullet.pos.fX >= g_iScreenWidth + a_Spaceshipbullet.iWidth)
	{
		a_Spaceshipbullet.pos.fX = (0.f * (float)g_iScreenWidth) - (float)a_Spaceshipbullet.iWidth;
	}
	else if (a_Spaceshipbullet.pos.fX <= -a_Spaceshipbullet.iWidth)
	{
		a_Spaceshipbullet.pos.fX = ((float)g_iScreenWidth + (float)a_Spaceshipbullet.iWidth);
	}
	UG::MoveSprite(a_Spaceshipbullet.iSpriteID, a_Spaceshipbullet.pos.fX, a_Spaceshipbullet.pos.fY);
	a_Spaceshipbullet.fCurrentDistance += a_Spaceshipbullet.vNew.Magnitude();
	if (a_Spaceshipbullet.fCurrentDistance >= a_Spaceshipbullet.c_fMaxDistance)
	{
		a_Spaceshipbullet.Destroy(a_Spaceshipbullet);
	}

	a_Spaceshipbullet.CheckCollision(a_Spaceshipbullet, a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray, a_UFOEasy, a_UFOHard, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount, iUFOEasyDeathCount, iUFOHardDeathCount, a_Scorecontroller);
}

void oObjectUpdateController::AsteroidLarge(oAsteroidLarge & a_AsteroidLarge, oAsteroidMedium* a_aAsteroidMediumArray)
{
	if (!a_AsteroidLarge.HasCollided())
	{
		a_AsteroidLarge.fPosX = a_AsteroidLarge.fPosX + a_AsteroidLarge.vNew.fX;
		a_AsteroidLarge.fPosY = a_AsteroidLarge.fPosY + a_AsteroidLarge.vNew.fY;
		if (a_AsteroidLarge.fPosY >= g_iScreenHeight + a_AsteroidLarge.iHeight)
		{
			a_AsteroidLarge.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidLarge.iHeight;
		}
		else if (a_AsteroidLarge.fPosY <= -a_AsteroidLarge.iHeight)
		{
			a_AsteroidLarge.fPosY = ((float)g_iScreenHeight + (float)a_AsteroidLarge.iHeight);
		}

		if (a_AsteroidLarge.fPosX >= g_iScreenWidth + a_AsteroidLarge.iWidth)
		{
			a_AsteroidLarge.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidLarge.iWidth;
		}
		else if (a_AsteroidLarge.fPosX <= -a_AsteroidLarge.iWidth)
		{
			a_AsteroidLarge.fPosX = ((float)g_iScreenWidth + (float)a_AsteroidLarge.iWidth);
		}
		UG::MoveSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
		UG::RotateSprite(a_AsteroidLarge.iSpriteID, a_AsteroidLarge.fSpriteTurnRate);
	}
	else if (a_AsteroidLarge.HasCollided())
	{
		a_AsteroidLarge.bIsActive = false;
		if (!a_AsteroidLarge.bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_aAsteroidMediumArray[iAsteroidMediumSpawnCount].Draw(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
				++iAsteroidMediumSpawnCount;
			}
			a_AsteroidLarge.bShattered = true;
		}
		a_AsteroidLarge.ResetVars(a_AsteroidLarge);
	}
}

void oObjectUpdateController::AsteroidMedium(oAsteroidMedium& a_AsteroidMedium, oAsteroidSmall* a_aAsteroidSmallArray)
{
	if (!a_AsteroidMedium.HasCollided())
	{
		a_AsteroidMedium.fPosX = a_AsteroidMedium.fPosX + a_AsteroidMedium.vNew.fX;
		a_AsteroidMedium.fPosY = a_AsteroidMedium.fPosY + a_AsteroidMedium.vNew.fY;
		if (a_AsteroidMedium.fPosY >= g_iScreenHeight + a_AsteroidMedium.iHeight)
		{
			a_AsteroidMedium.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidMedium.iHeight;
		}
		else if (a_AsteroidMedium.fPosY <= -a_AsteroidMedium.iHeight)
		{
			a_AsteroidMedium.fPosY = ((float)g_iScreenHeight + (float)a_AsteroidMedium.iHeight);
		}

		if (a_AsteroidMedium.fPosX >= g_iScreenWidth + a_AsteroidMedium.iWidth)
		{
			a_AsteroidMedium.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidMedium.iWidth;
		}
		else if (a_AsteroidMedium.fPosX <= -a_AsteroidMedium.iWidth)
		{
			a_AsteroidMedium.fPosX = ((float)g_iScreenWidth + (float)a_AsteroidMedium.iWidth);
		}
		UG::MoveSprite(a_AsteroidMedium.iSpriteID, a_AsteroidMedium.fPosX, a_AsteroidMedium.fPosY);
		UG::RotateSprite(a_AsteroidMedium.iSpriteID, a_AsteroidMedium.fSpriteTurnRate);
	}
	else if (a_AsteroidMedium.HasCollided())
	{
		a_AsteroidMedium.bIsActive = false;
		if (!a_AsteroidMedium.bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_aAsteroidSmallArray[iAsteroidSmallSpawnCount].Draw(a_AsteroidMedium.fPosX, a_AsteroidMedium.fPosY);
				++iAsteroidSmallSpawnCount;
			}
			a_AsteroidMedium.bShattered = true;
		}
		a_AsteroidMedium.ResetVars(a_AsteroidMedium);
	}
}

void oObjectUpdateController::AsteroidSmall(oAsteroidSmall& a_AsteroidSmall)
{
	if (!a_AsteroidSmall.HasCollided())
	{
		a_AsteroidSmall.fPosX = a_AsteroidSmall.fPosX + a_AsteroidSmall.vNew.fX;
		a_AsteroidSmall.fPosY = a_AsteroidSmall.fPosY + a_AsteroidSmall.vNew.fY;
		if (a_AsteroidSmall.fPosY >= g_iScreenHeight + a_AsteroidSmall.iHeight)
		{
			a_AsteroidSmall.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidSmall.iHeight;
		}
		else if (a_AsteroidSmall.fPosY <= -a_AsteroidSmall.iHeight)
		{
			a_AsteroidSmall.fPosY = ((float)g_iScreenHeight + (float)a_AsteroidSmall.iHeight);
		}

		if (a_AsteroidSmall.fPosX >= g_iScreenWidth + a_AsteroidSmall.iWidth)
		{
			a_AsteroidSmall.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidSmall.iWidth;
		}
		else if (a_AsteroidSmall.fPosX <= -a_AsteroidSmall.iWidth)
		{
			a_AsteroidSmall.fPosX = ((float)g_iScreenWidth + (float)a_AsteroidSmall.iWidth);
		}
		UG::MoveSprite(a_AsteroidSmall.iSpriteID, a_AsteroidSmall.fPosX, a_AsteroidSmall.fPosY);
		UG::RotateSprite(a_AsteroidSmall.iSpriteID, a_AsteroidSmall.fSpriteTurnRate);
	}
	else if (a_AsteroidSmall.HasCollided())
	{
		a_AsteroidSmall.bIsActive = false;
		a_AsteroidSmall.ResetVars(a_AsteroidSmall);
	}
}

void oObjectUpdateController::UFOEasy(oUFOEasy & a_UFOEasy, oSpaceship& a_Spaceship, oAsteroidLarge* a_aAsteroidLargeArray, oAsteroidMedium* a_aAsteroidMediumArray, oAsteroidSmall* a_aAsteroidSmallArray, oLivescontroller& a_Livescontroller)
{
	if (!a_UFOEasy.HasCollided())
	{
		a_UFOEasy.pos.fX = a_UFOEasy.pos.fX + a_UFOEasy.vNew.fX;
		a_UFOEasy.pos.fY = a_UFOEasy.pos.fY + a_UFOEasy.vNew.fY;

		if (a_UFOEasy.pos.fX >= g_iScreenWidth + a_UFOEasy.iWidth) // If UFO is Off the Right hand Side of the screen
		{
			int iRandomPos = rand() % 2;
			if (iRandomPos == 0)
			{
				a_UFOEasy.pos.fX = a_UFOEasy.posLeftTop.fX;
				a_UFOEasy.pos.fY = a_UFOEasy.posLeftTop.fY;
				a_UFOEasy.vNew = a_UFOEasy.vRightDown;
			}
			else if (iRandomPos == 1)
			{
				a_UFOEasy.pos.fX = a_UFOEasy.posLeftBottom.fX;
				a_UFOEasy.pos.fY = a_UFOEasy.posLeftBottom.fY;
				a_UFOEasy.vNew = a_UFOEasy.vRightUp;
			}
		}
		else if (a_UFOEasy.pos.fX <= -a_UFOEasy.iWidth) // If UFO Off the Left hand Side
		{
			int iRandomPos = rand() % 2;
			if (iRandomPos == 0)
			{
				a_UFOEasy.pos.fX = a_UFOEasy.posRightTop.fX;
				a_UFOEasy.pos.fY = a_UFOEasy.posRightTop.fY;
				a_UFOEasy.vNew = a_UFOEasy.vLeftDown;
			}
			else if (iRandomPos == 1)
			{
				a_UFOEasy.pos.fX = a_UFOEasy.posRightBottom.fX;
				a_UFOEasy.pos.fY = a_UFOEasy.posRightBottom.fY;
				a_UFOEasy.vNew = a_UFOEasy.vLeftUp;
			}
		}
		UG::MoveSprite(a_UFOEasy.iSpriteID, a_UFOEasy.pos.fX, a_UFOEasy.pos.fY);

		if (a_UFOEasy.fThinkingTime > a_UFOEasy.fMaxThinkingTime)
		{

			a_UFOEasy.fThinkingTime = 0.f;
			if (!a_UFOEasy.bDirection) //If Moving Left
			{
				if (a_UFOEasy.vNew.fX == a_UFOEasy.vLeftUp.fX && a_UFOEasy.vNew.fY == a_UFOEasy.vLeftUp.fY) // If Moving Up
				{
					a_UFOEasy.vNew = a_UFOEasy.vLeftDown; // Move Down
				}
				else if (a_UFOEasy.vNew.fX == a_UFOEasy.vLeftDown.fX && a_UFOEasy.vNew.fY == a_UFOEasy.vLeftDown.fY) // If Moving Down
				{
					a_UFOEasy.vNew = a_UFOEasy.vLeftUp; // Move Up
				}
			}
			else if (a_UFOEasy.bDirection) //If Moving Right
			{
				if (a_UFOEasy.vNew.fX == a_UFOEasy.vRightUp.fX && a_UFOEasy.vNew.fY == a_UFOEasy.vRightUp.fY) // If Moving Up
				{
					a_UFOEasy.vNew = a_UFOEasy.vRightDown; // Move Down
				}
				else if (a_UFOEasy.vNew.fX == a_UFOEasy.vRightDown.fX && a_UFOEasy.vNew.fY == a_UFOEasy.vRightDown.fY) // If Moving Down
				{
					a_UFOEasy.vNew = a_UFOEasy.vRightUp; // Move Up
				}
			}
		}
		a_UFOEasy.fThinkingTime += g_fDeltaTime;

		if (a_UFOEasy.fShootingDelay > a_UFOEasy.fMaxShootingDelay)
		{
			if (UFOEasyBullets.bHasExpired)
			{
				UFOEasyBullets.Draw(UFOEasyBullets, a_UFOEasy.pos.fX, a_UFOEasy.pos.fY, a_UFOEasy.NewFireDirection());
				a_UFOEasy.fShootingDelay = 0.f;
			}
		}
		a_UFOEasy.fShootingDelay += g_fDeltaTime;

		if (UFOEasyBullets.IsActive(UFOEasyBullets))
		{
			UFOBullet(UFOEasyBullets, a_Spaceship, a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray, a_Livescontroller);
		}
	}
	else if (a_UFOEasy.HasCollided())
	{
		if (UFOEasyBullets.IsActive(UFOEasyBullets))
		{
			UFOEasyBullets.Destroy(UFOEasyBullets);
		}
		a_UFOEasy.SetIsActive(false);
	}
}

void oObjectUpdateController::UFOHard(oUFOHard & a_UFOHard, oSpaceship & a_Spaceship, oAsteroidLarge * a_aAsteroidLargeArray, oAsteroidMedium * a_aAsteroidMediumArray, oAsteroidSmall * a_aAsteroidSmallArray, oLivescontroller & a_Livescontroller)
{
	if (!a_UFOHard.HasCollided())
	{
		a_UFOHard.pos.fX = a_UFOHard.pos.fX + a_UFOHard.vNew.fX;
		a_UFOHard.pos.fY = a_UFOHard.pos.fY + a_UFOHard.vNew.fY;

		if (a_UFOHard.pos.fX >= g_iScreenWidth + a_UFOHard.iWidth) // If UFO is Off the Right hand Side of the screen
		{
			int iRandomPos = rand() % 2;
			if (iRandomPos == 0)
			{
				a_UFOHard.pos.fX = a_UFOHard.posLeftTop.fX;
				a_UFOHard.pos.fY = a_UFOHard.posLeftTop.fY;
				a_UFOHard.vNew = a_UFOHard.vRight;
			}
			else if (iRandomPos == 1)
			{
				a_UFOHard.pos.fX = a_UFOHard.posLeftBottom.fX;
				a_UFOHard.pos.fY = a_UFOHard.posLeftBottom.fY;
				a_UFOHard.vNew = a_UFOHard.vRight;
			}
		}
		else if (a_UFOHard.pos.fX <= -a_UFOHard.iWidth) // If UFO Off the Left hand Side
		{
			int iRandomPos = rand() % 2;
			if (iRandomPos == 0)
			{
				a_UFOHard.pos.fX = a_UFOHard.posRightTop.fX;
				a_UFOHard.pos.fY = a_UFOHard.posRightTop.fY;
				a_UFOHard.vNew = a_UFOHard.vLeft;
			}
			else if (iRandomPos == 1)
			{
				a_UFOHard.pos.fX = a_UFOHard.posRightBottom.fX;
				a_UFOHard.pos.fY = a_UFOHard.posRightBottom.fY;
				a_UFOHard.vNew = a_UFOHard.vLeft;
			}
		}
		UG::MoveSprite(a_UFOHard.iSpriteID, a_UFOHard.pos.fX, a_UFOHard.pos.fY);

		if (a_UFOHard.fThinkingTime > a_UFOHard.fMaxThinkingTime)
		{
			int iChangeDirection = rand() % 2;
			if (iChangeDirection == 0)
			{
				a_UFOHard.vNew = a_UFOHard.vLeft;
			}
			else if (iChangeDirection == 1)
			{
				a_UFOHard.vNew = a_UFOHard.vRight;
			}
			a_UFOHard.fThinkingTime = 0.f;
		}
		a_UFOHard.fThinkingTime += g_fDeltaTime;

		if (a_UFOHard.fShootingDelay > a_UFOHard.fMaxShootingDelay && a_Spaceship.bIsActive == true)
		{

			if (UFOHardBullets.bHasExpired)
			{
				UFOHardBullets.Draw(UFOHardBullets, a_UFOHard.pos.fX, a_UFOHard.pos.fY, UFOHardBullets.NewFireDirection(a_UFOHard, a_Spaceship));
				a_UFOHard.fShootingDelay = 0.f;
			}

		}

		a_UFOHard.fShootingDelay += g_fDeltaTime;

		if (UFOHardBullets.IsActive(UFOHardBullets))
		{
			UFOBullet(UFOHardBullets, a_Spaceship, a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray, a_Livescontroller);
		}

	}
	else if (a_UFOHard.HasCollided())
	{
		if (UFOHardBullets.IsActive(UFOHardBullets))
		{
			UFOHardBullets.Destroy(UFOHardBullets);
		}

		a_UFOHard.SetIsActive(false);
	}
}

void oObjectUpdateController::UFOBullet(oUFOBullet & a_UFOBullet, oSpaceship& a_Spaceship, oAsteroidLarge * a_aAsteroidLargeArray, oAsteroidMedium * a_aAsteroidMediumArray, oAsteroidSmall * a_aAsteroidSmallArray, oLivescontroller& a_Livescontroller)
{
	a_UFOBullet.pos.fX = a_UFOBullet.pos.fX + a_UFOBullet.vNew.fX;
	a_UFOBullet.pos.fY = a_UFOBullet.pos.fY + a_UFOBullet.vNew.fY;
	if (a_UFOBullet.pos.fY >= g_iScreenHeight + a_UFOBullet.iHeight)
	{
		a_UFOBullet.pos.fY = (0.f * (float)g_iScreenHeight) - (float)a_UFOBullet.iHeight;
	}
	else if (a_UFOBullet.pos.fY <= -a_UFOBullet.iHeight)
	{
		a_UFOBullet.pos.fY = ((float)g_iScreenHeight + (float)a_UFOBullet.iHeight);
	}

	if (a_UFOBullet.pos.fX >= g_iScreenWidth + a_UFOBullet.iWidth)
	{
		a_UFOBullet.pos.fX = (0.f * (float)g_iScreenWidth) - (float)a_UFOBullet.iWidth;
	}
	else if (a_UFOBullet.pos.fX <= -a_UFOBullet.iWidth)
	{
		a_UFOBullet.pos.fX = ((float)g_iScreenWidth + (float)a_UFOBullet.iWidth);
	}
	UG::MoveSprite(a_UFOBullet.iSpriteID, a_UFOBullet.pos.fX, a_UFOBullet.pos.fY);
	a_UFOBullet.fCurrentDistance += a_UFOBullet.vNew.Magnitude();
	if (a_UFOBullet.fCurrentDistance >= a_UFOBullet.c_fMaxDistance)
	{
		a_UFOBullet.Destroy(a_UFOBullet);
	}
	a_UFOBullet.CheckCollision(a_UFOBullet, a_Spaceship, a_aAsteroidLargeArray, a_aAsteroidMediumArray, a_aAsteroidSmallArray, a_Livescontroller, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount);
}

void oObjectUpdateController::ReinitialiseAsteroids(oAsteroidMedium * a_aAsteroidMediumArray, oAsteroidSmall * a_aAsteroidSmallArray)
{
	int iCycle = 0;
	//Initialise Medium Asteroids
	for (int i = 0; i < 15; i++)
	{
		if (iCycle == 0)
		{
			a_aAsteroidMediumArray[i].Initialise(a_aAsteroidMediumArray[i].c_cMediumAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_aAsteroidMediumArray[i].Initialise(a_aAsteroidMediumArray[i].c_cMediumAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_aAsteroidMediumArray[i].Initialise(a_aAsteroidMediumArray[i].c_cMediumAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise Small Asteroids
	for (int i = 0; i < 45; i++)
	{
		if (iCycle == 0)
		{
			a_aAsteroidSmallArray[i].Initialise(a_aAsteroidSmallArray[i].c_cSmallAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_aAsteroidSmallArray[i].Initialise(a_aAsteroidSmallArray[i].c_cSmallAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_aAsteroidSmallArray[i].Initialise(a_aAsteroidSmallArray[i].c_cSmallAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}
}

void oObjectUpdateController::ResetCount()
{
	iAsteroidLargeSpawnCount = 0;
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
	if (iAsteroidLargeDeathCount == 5 && iAsteroidMediumDeathCount == 15 && iAsteroidSmallDeathCount == 45 && iUFOEasyDeathCount == 1 && iUFOHardDeathCount == 1)
	{
		bAllDead = true;
	}
	return bAllDead;
}
