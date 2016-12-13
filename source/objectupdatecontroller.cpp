#include "objectupdatecontroller.h"
#include "UGFW.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

oBullet bulletarray[2];

GameState oObjectUpdateController::Spaceship(oSpaceship& a_Spaceship, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, oLivesController& a_livescontroller)
{
	//a_Spaceship.CheckAsteroidCollision(a_Spaceship, a_asteroidlargearray, a_asteroidmediumarray, a_asteroidsmallarray, a_livescontroller, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount);
	if (AsteroidCheck())
	{
		ResetAsteroidSpawnCount();
		for (int i = 0; i < 5; ++i)
		{
			a_asteroidlargearray[i].Respawn(a_asteroidlargearray[i], i);
		}
		ReinitialiseAsteroids(a_asteroidmediumarray, a_asteroidsmallarray);
		bAllDead = false;
	}
	if (a_Spaceship.bIsActive == true)
	{
		a_Spaceship.fCurrentTurnRate = 0.f;
		a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
		a_Spaceship.vNew.Get(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
		if (UG::IsKeyDown(a_Spaceship.upKey)) // Accelerate the ship in the current facing direction
		{
			a_Spaceship.fVNewX += a_Spaceship.fAcceleration * cosf(a_Spaceship.fFacingAngleRad);
			a_Spaceship.fVNewY += a_Spaceship.fAcceleration * sinf(a_Spaceship.fFacingAngleRad);
			a_Spaceship.vNew.Set(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
			a_Spaceship.fTotalVelocity = a_Spaceship.vNew.Magnitude();

			//Cap Speed at Maximum Velocity
			if (a_Spaceship.fTotalVelocity > a_Spaceship.fMaxVelocity)
			{
				a_Spaceship.fTotalVelocity = a_Spaceship.fMaxVelocity;
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
			a_Spaceship.fCurrentTurnRate = -a_Spaceship.fTurnRate;
			a_Spaceship.fFacingAngleDeg += a_Spaceship.fCurrentTurnRate;
			a_Spaceship.fFacingAngleDeg = a_Spaceship.AngleWrap(a_Spaceship.fFacingAngleDeg);
			a_Spaceship.fFacingAngleRad = a_Spaceship.fFacingAngleDeg * a_Spaceship.degtorad;
			UG::RotateSprite(a_Spaceship.iSpriteID, a_Spaceship.fCurrentTurnRate);
		}
		if (UG::IsKeyDown(a_Spaceship.leftKey))
		{
			a_Spaceship.fCurrentTurnRate = a_Spaceship.fTurnRate;
			a_Spaceship.fFacingAngleDeg += a_Spaceship.fCurrentTurnRate;
			a_Spaceship.fFacingAngleDeg = a_Spaceship.AngleWrap(a_Spaceship.fFacingAngleDeg);
			a_Spaceship.fFacingAngleRad = a_Spaceship.fFacingAngleDeg * a_Spaceship.degtorad;
			UG::RotateSprite(a_Spaceship.iSpriteID, a_Spaceship.fCurrentTurnRate);
		}
		if (UG::IsKeyDown(a_Spaceship.breakKey))
		{
			int testint = 0;
		}
		if (UG::IsKeyDown(a_Spaceship.fireKey))
		{
			a_Spaceship.fFireDelay -= g_DeltaTime;
			if (a_Spaceship.fFireDelay < 0.f)
			{
				for (int i = 0; i <2; ++i)
				{
					if (!bulletarray[i].IsDrawn(bulletarray[i]))
					{
						bulletarray[i].Draw(bulletarray[i], a_Spaceship.fFacingAngleRad, a_Spaceship.fPosX, a_Spaceship.fPosY);
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
		a_Spaceship.fVNewX *= a_Spaceship.fDrag;
		a_Spaceship.fVNewY *= a_Spaceship.fDrag;
		a_Spaceship.vNew.Set(a_Spaceship.fVNewX, a_Spaceship.fVNewY);
		a_Spaceship.fPosX = a_Spaceship.fPosX + a_Spaceship.fVNewX;
		a_Spaceship.fPosY = a_Spaceship.fPosY + a_Spaceship.fVNewY;

		if (a_Spaceship.fPosY >= g_iScreenHeight + a_Spaceship.iHeight)
		{
			a_Spaceship.fPosY = (0.f * g_iScreenHeight) - a_Spaceship.iHeight;
		}
		else if (a_Spaceship.fPosY <= -a_Spaceship.iHeight)
		{
			a_Spaceship.fPosY = ((float)g_iScreenHeight + (float)a_Spaceship.iHeight);
		}

		if (a_Spaceship.fPosX >= g_iScreenWidth + a_Spaceship.iWidth)
		{
			a_Spaceship.fPosX = (0.f * g_iScreenWidth) - a_Spaceship.iWidth;
		}
		else if (a_Spaceship.fPosX <= -a_Spaceship.iWidth)
		{
			a_Spaceship.fPosX = ((float)g_iScreenWidth + (float)a_Spaceship.iWidth);
		}
		UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
		a_Spaceship.pos.Set(a_Spaceship.fPosX, a_Spaceship.fPosY);
	}
	
	if (a_Spaceship.bIsActive == false)
	{
		if (a_livescontroller.CurrentLives() > 0)
		{
			if (a_Spaceship.fSpawnTime > a_Spaceship.fMaxSpawnTime)
			{
				a_Spaceship.CheckSpawnCollision(a_Spaceship, a_asteroidlargearray, a_asteroidmediumarray, a_asteroidsmallarray);
				if (a_Spaceship.bCollision == false)
				{
					a_Spaceship.Respawn(a_Spaceship);
				}
				else if (a_Spaceship.bCollision == true)
				{
					a_Spaceship.fSpawnTime = 0.f;
				}
			}
			a_Spaceship.fSpawnTime += g_DeltaTime;
		}
		else if (a_livescontroller.CurrentLives() == 0)
		{
			UG::DrawString("GAME OVER, PRESS ESCAPE TO EXIT", g_iScreenWidth * 0.18, g_iScreenHeight * 0.55);
			if (UG::IsKeyDown(a_Spaceship.exitKey))
			{
				GameState newState = GameState::GAMEOVER;
				return newState;
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		if (bulletarray[i].IsActive(bulletarray[i]))
		{
			Bullet(bulletarray[i], a_asteroidlargearray, a_asteroidmediumarray, a_asteroidsmallarray);
		}
		else
		{
			//Do Nothing
		}
	}
}

bool oObjectUpdateController::Bullet(oBullet& a_bullet, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray)
{
	a_bullet.pos.Get(a_bullet.fPosX, a_bullet.fPosY);
	a_bullet.vNew.Get(a_bullet.fVNewX, a_bullet.fVNewY);
	a_bullet.fPosX = a_bullet.fPosX + a_bullet.fVNewX;
	a_bullet.fPosY = a_bullet.fPosY + a_bullet.fVNewY;
	if (a_bullet.fPosY >= g_iScreenHeight + a_bullet.iHeight)
	{
		a_bullet.fPosY = (0.f * (float)g_iScreenHeight) - (float)a_bullet.iHeight;
	}
	else if (a_bullet.fPosY <= -a_bullet.iHeight)
	{
		a_bullet.fPosY = ((float)g_iScreenHeight + (float)a_bullet.iHeight);
	}

	if (a_bullet.fPosX >= g_iScreenWidth + a_bullet.iWidth)
	{
		a_bullet.fPosX = (0.f * (float)g_iScreenWidth) - (float)a_bullet.iWidth;
	}
	else if (a_bullet.fPosX <= -a_bullet.iWidth)
	{
		a_bullet.fPosX = ((float)g_iScreenWidth + (float)a_bullet.iWidth);
	}
	UG::MoveSprite(a_bullet.iSpriteID, a_bullet.fPosX, a_bullet.fPosY);
	a_bullet.pos.Set(a_bullet.fPosX, a_bullet.fPosY);
	a_bullet.fCurrentDistance += a_bullet.vNew.Magnitude();
	if (a_bullet.fCurrentDistance >= a_bullet.fMaxDistance)
	{
		a_bullet.Destroy(a_bullet);
		return a_bullet.bIsActive;
	}

	a_bullet.CheckAsteroidCollision(a_bullet, a_asteroidlargearray, a_asteroidmediumarray, a_asteroidsmallarray, iAsteroidLargeDeathCount, iAsteroidMediumDeathCount, iAsteroidSmallDeathCount);

	return a_bullet.bIsActive;
}

void oObjectUpdateController::AsteroidLarge(oAsteroidLarge & a_AsteroidLarge, oAsteroidMedium* a_asteroidmediumarray, oScorecontroller& a_scorecontroller)
{
	if (!a_AsteroidLarge.HasCollided())
	{
		a_AsteroidLarge.pos.Get(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
		a_AsteroidLarge.vNew.Get(a_AsteroidLarge.fVNewX, a_AsteroidLarge.fVNewY);
		a_AsteroidLarge.fPosX = a_AsteroidLarge.fPosX + a_AsteroidLarge.fVNewX;
		a_AsteroidLarge.fPosY = a_AsteroidLarge.fPosY + a_AsteroidLarge.fVNewY;
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
		a_AsteroidLarge.pos.Set(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
	}
	else if (a_AsteroidLarge.HasCollided())
	{
		a_AsteroidLarge.bIsActive = false;
		if (!a_AsteroidLarge.bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_asteroidmediumarray[iAsteroidMediumSpawnCount].Draw(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
				++iAsteroidMediumSpawnCount;
			}
			a_AsteroidLarge.ResetVars(a_AsteroidLarge);
			a_AsteroidLarge.bShattered = true;
		}
		if (!a_AsteroidLarge.bScoreUpdated)
		{
			Score(a_scorecontroller, a_AsteroidLarge.iScore);
			a_AsteroidLarge.bScoreUpdated = true;
		}
	}
}

void oObjectUpdateController::AsteroidMedium(oAsteroidMedium& a_AsteroidMedium, oAsteroidSmall* a_asteroidsmallarray, oScorecontroller& a_scorecontroller)
{
	if (!a_AsteroidMedium.HasCollided())
	{
		a_AsteroidMedium.pos.Get(a_AsteroidMedium.fPosX, a_AsteroidMedium.fPosY);
		a_AsteroidMedium.vNew.Get(a_AsteroidMedium.fVNewX, a_AsteroidMedium.fVNewY);
		a_AsteroidMedium.fPosX = a_AsteroidMedium.fPosX + a_AsteroidMedium.fVNewX;
		a_AsteroidMedium.fPosY = a_AsteroidMedium.fPosY + a_AsteroidMedium.fVNewY;
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
		a_AsteroidMedium.pos.Set(a_AsteroidMedium.fPosX, a_AsteroidMedium.fPosY);
	}
	else if (a_AsteroidMedium.HasCollided())
	{
		a_AsteroidMedium.bIsActive = false;
		if (!a_AsteroidMedium.bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_asteroidsmallarray[iAsteroidSmallSpawnCount].Draw(a_AsteroidMedium.fPosX, a_AsteroidMedium.fPosY);
				++iAsteroidSmallSpawnCount;
			}
			a_AsteroidMedium.ResetVars(a_AsteroidMedium);
			a_AsteroidMedium.bShattered = true;
		}
		if (!a_AsteroidMedium.bScoreUpdated)
		{
			Score(a_scorecontroller, a_AsteroidMedium.iScore);
			a_AsteroidMedium.bScoreUpdated = true;
		}
	}
}

void oObjectUpdateController::AsteroidSmall(oAsteroidSmall& a_AsteroidSmall, oScorecontroller& a_scorecontroller)
{
	if (!a_AsteroidSmall.HasCollided())
	{
		a_AsteroidSmall.pos.Get(a_AsteroidSmall.fPosX, a_AsteroidSmall.fPosY);
		a_AsteroidSmall.vNew.Get(a_AsteroidSmall.fVNewX, a_AsteroidSmall.fVNewY);
		a_AsteroidSmall.fPosX = a_AsteroidSmall.fPosX + a_AsteroidSmall.fVNewX;
		a_AsteroidSmall.fPosY = a_AsteroidSmall.fPosY + a_AsteroidSmall.fVNewY;
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
		a_AsteroidSmall.pos.Set(a_AsteroidSmall.fPosX, a_AsteroidSmall.fPosY);
	}
	else if (a_AsteroidSmall.HasCollided())
	{
		a_AsteroidSmall.bIsActive = false;
		a_AsteroidSmall.ResetVars(a_AsteroidSmall);
		if (!a_AsteroidSmall.bScoreUpdated)
		{
			Score(a_scorecontroller, a_AsteroidSmall.iScore);
			a_AsteroidSmall.bScoreUpdated = true;
		}
	}
}

void oObjectUpdateController::ReinitialiseAsteroids(oAsteroidMedium * a_asteroidmediumarray, oAsteroidSmall * a_asteroidsmallarray)
{
	int iCycle = 0;
	//Initialise Medium Asteroids
	for (int i = 0; i < 15; i++)
	{
		if (iCycle == 0)
		{
			a_asteroidmediumarray[i].Initialise(a_asteroidmediumarray[i].cMediumAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_asteroidmediumarray[i].Initialise(a_asteroidmediumarray[i].cMediumAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_asteroidmediumarray[i].Initialise(a_asteroidmediumarray[i].cMediumAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}

	//Initialise Small Asteroids
	for (int i = 0; i < 45; i++)
	{
		if (iCycle == 0)
		{
			a_asteroidsmallarray[i].Initialise(a_asteroidsmallarray[i].cSmallAsteroidFileName[iCycle]);
			iCycle = 1;
		}
		else if (iCycle == 1)
		{
			a_asteroidsmallarray[i].Initialise(a_asteroidsmallarray[i].cSmallAsteroidFileName[iCycle]);
			iCycle = 2;
		}
		else if (iCycle == 2)
		{
			a_asteroidsmallarray[i].Initialise(a_asteroidsmallarray[i].cSmallAsteroidFileName[iCycle]);
			iCycle = 0;
		}
	}
}

void oObjectUpdateController::ResetAsteroidSpawnCount()
{
	iAsteroidLargeSpawnCount = 0;
	iAsteroidLargeDeathCount = 0;
	iAsteroidMediumSpawnCount = 0;
	iAsteroidMediumDeathCount = 0;
	iAsteroidSmallSpawnCount = 0;
	iAsteroidSmallDeathCount = 0;
}

bool oObjectUpdateController::AsteroidCheck()
{
	if (iAsteroidLargeDeathCount == 5 && iAsteroidMediumDeathCount == 15 && iAsteroidSmallDeathCount == 45)
	{
		bAllDead = true;
	}
	return bAllDead;
}

void oObjectUpdateController::Score(oScorecontroller & a_scorecontroller, int a_inewscore)
{
	a_scorecontroller.iCurrentScore += a_inewscore;
}
