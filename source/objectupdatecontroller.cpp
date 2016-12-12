#include "objectupdatecontroller.h"
#include "UGFW.h"
extern int g_iScreenHeight;
extern int g_iScreenWidth;

void oObjectUpdateController::SpaceshipUpdate(oSpaceship& a_Spaceship, std::vector<oAsteroidLarge>& a_asteroidlargearray, std::vector<oAsteroidMedium>& a_asteroidmediumarray, std::vector<oAsteroidSmall>& a_asteroidsmallarray, oLivesController& a_livescontroller)
{
	
	if (a_Spaceship.bIsDead == false)
	{
		a_Spaceship.CheckAsteroidCollision(a_Spaceship, a_asteroidlargearray, a_livescontroller);
		a_Spaceship.CheckAsteroidCollision(a_Spaceship, a_asteroidmediumarray, a_livescontroller);
		a_Spaceship.CheckAsteroidCollision(a_Spaceship, a_asteroidsmallarray, a_livescontroller);

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
				a_Spaceship.bullets.push_back(oBullet());
				for (std::vector<oBullet>::iterator i = a_Spaceship.bullets.begin(); i != a_Spaceship.bullets.end();)
				{
					if (!i->IsDrawn(i))
					{
						i->Draw(i, a_Spaceship.fFacingAngleRad, a_Spaceship.fPosX, a_Spaceship.fPosY);
					}
					i++;
				}
				a_Spaceship.fFireDelay = 0.5f;
			}
		}
		else
		{
			a_Spaceship.fFireDelay = 0.f;
		}
		for (std::vector<oBullet>::iterator i = a_Spaceship.bullets.begin(); i != a_Spaceship.bullets.end();)
		{
			if (!i->IsActive(i))
			{
				UG::StopDrawingSprite(i->iSpriteID);
				UG::DestroySprite(i->iSpriteID);
				i = a_Spaceship.bullets.erase(i);
			}
			else
			{
				BulletUpdate(a_Spaceship.bullets, i);

				i->CheckLargeAsteroidCollision(a_Spaceship.bullets, i, a_asteroidlargearray);
				i->CheckMediumAsteroidCollision(a_Spaceship.bullets, i, a_asteroidmediumarray);
				i->CheckSmallAsteroidCollision(a_Spaceship.bullets, i, a_asteroidsmallarray);
				++i;
			}
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
	
	if (a_Spaceship.bIsDead == true)
	{
		UG::StopDrawingSprite(a_Spaceship.iSpriteID);
	}
}

bool oObjectUpdateController::BulletUpdate(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet)
{
	a_Bullet->pos.Get(a_Bullet->fPosX, a_Bullet->fPosY);
	a_Bullet->vNew.Get(a_Bullet->fVNewX, a_Bullet->fVNewY);
	a_Bullet->fPosX = a_Bullet->fPosX + a_Bullet->fVNewX;
	a_Bullet->fPosY = a_Bullet->fPosY + a_Bullet->fVNewY;
	if (a_Bullet->fPosY >= g_iScreenHeight + a_Bullet->iHeight)
	{
		a_Bullet->fPosY = (0.f * (float)g_iScreenHeight) - (float)a_Bullet->iHeight;
	}
	else if (a_Bullet->fPosY <= -a_Bullet->iHeight)
	{
		a_Bullet->fPosY = ((float)g_iScreenHeight + (float)a_Bullet->iHeight);
	}

	if (a_Bullet->fPosX >= g_iScreenWidth + a_Bullet->iWidth)
	{
		a_Bullet->fPosX = (0.f * (float)g_iScreenWidth) - (float)a_Bullet->iWidth;
	}
	else if (a_Bullet->fPosX <= -a_Bullet->iWidth)
	{
		a_Bullet->fPosX = ((float)g_iScreenWidth + (float)a_Bullet->iWidth);
	}
	UG::MoveSprite(a_Bullet->iSpriteID, a_Bullet->fPosX, a_Bullet->fPosY);
	a_Bullet->pos.Set(a_Bullet->fPosX, a_Bullet->fPosY);
	a_Bullet->fCurrentDistance += a_Bullet->vNew.Magnitude();
	if (a_Bullet->fCurrentDistance >= a_Bullet->fMaxDistance)
	{
		a_Bullet->bIsDrawn = false;
		a_Bullet->bIsActive = false;
	}
	return a_Bullet->bIsActive;
}

void oObjectUpdateController::AsteroidLargeUpdate(oAsteroidLarge & a_AsteroidLarge, std::vector<oAsteroidMedium>& a_asteroidmediumarray, oScorecontroller& a_scorecontroller)
{
	if (!a_AsteroidLarge.bIsDead)
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
	else if (a_AsteroidLarge.bIsDead)
	{
		if (!a_AsteroidLarge.bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_asteroidmediumarray.push_back(oAsteroidMedium(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY, i));
			}
			a_AsteroidLarge.bShattered = true;
		}
		if (!a_AsteroidLarge.bScoreUpdated)
		{

	 		Explosion explosion;
			explosion.Update(a_AsteroidLarge.fPosX, a_AsteroidLarge.fPosY);
			ScoreUpdate(a_scorecontroller, a_AsteroidLarge.iScore);
			a_AsteroidLarge.bScoreUpdated = true;
		}
		UG::StopDrawingSprite(a_AsteroidLarge.iSpriteID);
	}
}

void oObjectUpdateController::AsteroidMediumUpdate(std::vector<oAsteroidMedium>::iterator a_AsteroidMedium, std::vector<oAsteroidSmall>& a_asteroidsmallarray, oScorecontroller& a_scorecontroller)
{
	if (!a_AsteroidMedium->bIsDead)
	{
		a_AsteroidMedium->pos.Get(a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY);
		a_AsteroidMedium->vNew.Get(a_AsteroidMedium->fVNewX, a_AsteroidMedium->fVNewY);
		a_AsteroidMedium->fPosX = a_AsteroidMedium->fPosX + a_AsteroidMedium->fVNewX;
		a_AsteroidMedium->fPosY = a_AsteroidMedium->fPosY + a_AsteroidMedium->fVNewY;
		if (a_AsteroidMedium->fPosY >= g_iScreenHeight + a_AsteroidMedium->iHeight)
		{
			a_AsteroidMedium->fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidMedium->iHeight;
		}
		else if (a_AsteroidMedium->fPosY <= -a_AsteroidMedium->iHeight)
		{
			a_AsteroidMedium->fPosY = ((float)g_iScreenHeight + (float)a_AsteroidMedium->iHeight);
		}

		if (a_AsteroidMedium->fPosX >= g_iScreenWidth + a_AsteroidMedium->iWidth)
		{
			a_AsteroidMedium->fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidMedium->iWidth;
		}
		else if (a_AsteroidMedium->fPosX <= -a_AsteroidMedium->iWidth)
		{
			a_AsteroidMedium->fPosX = ((float)g_iScreenWidth + (float)a_AsteroidMedium->iWidth);
		}
		UG::MoveSprite(a_AsteroidMedium->iSpriteID, a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY);
		UG::RotateSprite(a_AsteroidMedium->iSpriteID, a_AsteroidMedium->fSpriteTurnRate);
		a_AsteroidMedium->pos.Set(a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY);
	}
	else if (a_AsteroidMedium->bIsDead)
	{
		if (!a_AsteroidMedium->bShattered)
		{
			for (int i = 0; i < 3; i++)
			{
				a_asteroidsmallarray.push_back(oAsteroidSmall(a_AsteroidMedium->fPosX, a_AsteroidMedium->fPosY, i));
			}
			a_AsteroidMedium->bShattered = true;
		}
		if (!a_AsteroidMedium->bScoreUpdated)
		{

			ScoreUpdate(a_scorecontroller, a_AsteroidMedium->iScore);
			a_AsteroidMedium->bScoreUpdated = true;
		}
		UG::StopDrawingSprite(a_AsteroidMedium->iSpriteID);
	}
}

void oObjectUpdateController::AsteroidSmallUpdate(std::vector<oAsteroidSmall>::iterator a_AsteroidSmall, oScorecontroller& a_scorecontroller)
{
	if (!a_AsteroidSmall->bIsDead)
	{
		a_AsteroidSmall->pos.Get(a_AsteroidSmall->fPosX, a_AsteroidSmall->fPosY);
		a_AsteroidSmall->vNew.Get(a_AsteroidSmall->fVNewX, a_AsteroidSmall->fVNewY);
		a_AsteroidSmall->fPosX = a_AsteroidSmall->fPosX + a_AsteroidSmall->fVNewX;
		a_AsteroidSmall->fPosY = a_AsteroidSmall->fPosY + a_AsteroidSmall->fVNewY;
		if (a_AsteroidSmall->fPosY >= g_iScreenHeight + a_AsteroidSmall->iHeight)
		{
			a_AsteroidSmall->fPosY = (0.f * (float)g_iScreenHeight) - (float)a_AsteroidSmall->iHeight;
		}
		else if (a_AsteroidSmall->fPosY <= -a_AsteroidSmall->iHeight)
		{
			a_AsteroidSmall->fPosY = ((float)g_iScreenHeight + (float)a_AsteroidSmall->iHeight);
		}

		if (a_AsteroidSmall->fPosX >= g_iScreenWidth + a_AsteroidSmall->iWidth)
		{
			a_AsteroidSmall->fPosX = (0.f * (float)g_iScreenWidth) - (float)a_AsteroidSmall->iWidth;
		}
		else if (a_AsteroidSmall->fPosX <= -a_AsteroidSmall->iWidth)
		{
			a_AsteroidSmall->fPosX = ((float)g_iScreenWidth + (float)a_AsteroidSmall->iWidth);
		}
		UG::MoveSprite(a_AsteroidSmall->iSpriteID, a_AsteroidSmall->fPosX, a_AsteroidSmall->fPosY);
		UG::RotateSprite(a_AsteroidSmall->iSpriteID, a_AsteroidSmall->fSpriteTurnRate);
		a_AsteroidSmall->pos.Set(a_AsteroidSmall->fPosX, a_AsteroidSmall->fPosY);
	}
	else if (a_AsteroidSmall->bIsDead)
	{
		if (!a_AsteroidSmall->bScoreUpdated)
		{
			ScoreUpdate(a_scorecontroller, a_AsteroidSmall->iScore);
			a_AsteroidSmall->bScoreUpdated = true;
		}
		UG::StopDrawingSprite(a_AsteroidSmall->iSpriteID);
	}
}

void oObjectUpdateController::ScoreUpdate(oScorecontroller & a_scorecontroller, int a_inewscore)
{
	a_scorecontroller.iCurrentScore += a_inewscore;
}
