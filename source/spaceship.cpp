#include "spaceship.h";
#include "UGFW.h";
#define _USE_MATH_DEFINES
#include "math.h";

extern float g_DeltaTime;

oSpaceship::oSpaceship()
{

}

void oSpaceship::Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName, float a_fXPos, float a_fYPos)
{
	a_Spaceship.pos.Set(a_fXPos, a_fYPos);
	a_Spaceship.iSpriteID = UG::CreateSprite(a_SpaceshipImageFileName, (float)a_Spaceship.iWidth, (float)a_Spaceship.iHeight);
	float fX = 0.f, fY = 0.f;
	a_Spaceship.pos.Get(fX, fY);
	UG::MoveSprite(a_Spaceship.iSpriteID, fX, fY);
}

void oSpaceship::SetSpaceshipMovementKeys(oSpaceship & a_Spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short a_breakKey)
{
	a_Spaceship.upKey = a_upKey;
	a_Spaceship.downKey = a_downKey;
	a_Spaceship.leftKey = a_leftKey;
	a_Spaceship.rightKey = a_rightKey;
	a_Spaceship.breakKey = a_breakKey;

}

void oSpaceship::MoveSpaceship(oSpaceship & a_Spaceship)
{
	int iDirection = 0;
	float iSpriteTurnRate = 0;
	if (UG::IsKeyDown(a_Spaceship.upKey)) // Accelerate the ship in the current facing direction
	{
		ixVelocity += iAcceleration*cos(iMovementAngleRad);
		iyVelocity += iAcceleration*sin(iMovementAngleRad);
		
		if ((iyVelocity == 0.0) && (ixVelocity == 0.0))
		{
			iFacingAngleRad = iMovementAngleRad;
		}
		else
		{
			iFacingAngleRad = atan2(iyVelocity, ixVelocity);
		}

		iCurrentVelocity = sqrt(ixVelocity*ixVelocity + iyVelocity*iyVelocity);

		//Cap Speed
		if (iCurrentVelocity > iMaxVelocity)
		{
			iCurrentVelocity = iMaxVelocity;
			ixVelocity = iCurrentVelocity*cos(iFacingAngleRad);
			iyVelocity = iCurrentVelocity*sin(iFacingAngleRad);
		}
		iCurrentVelocity;
	}
	if (UG::IsKeyDown(a_Spaceship.rightKey))
	{
		iMovementAngleDeg -= iTurnRate;
		//Wrap Angle up to 360 if Below 0
		if (iMovementAngleDeg < 0.0) {
			iMovementAngleDeg += 360.0*((float)((int)iMovementAngleDeg / 360.0) + 1);
		}
		//Angle Recalculation
		iMovementAngleRad = iMovementAngleDeg *degtorad;

		iSpriteTurnRate = -1.0;
	}
	if (UG::IsKeyDown(a_Spaceship.leftKey))
	{
		iMovementAngleDeg += iTurnRate;
		//Wrap Angle down to 0 if above 360
		if (iMovementAngleDeg >= 360.0)
		{
			iMovementAngleDeg -= 360.0*((float)(int)(iMovementAngleDeg / 360.0));
		}
		//Angle Recalulation
		iMovementAngleRad = iMovementAngleDeg*degtorad;

		iSpriteTurnRate = 1.0;
	}

	if (UG::IsKeyDown(a_Spaceship.breakKey))
	{
		int testint = 0;
	}

	float pX = 0.f, pY = 0.f;
	a_Spaceship.pos.Get(pX, pY);


	float newPositionY = pY + iyVelocity;
	float newPositionX = pX + ixVelocity;

	pY = newPositionY;
	pX = newPositionX;

	UG::MoveSprite(a_Spaceship.iSpriteID, pX, pY);
	UG::RotateSprite(a_Spaceship.iSpriteID,iSpriteTurnRate);
	a_Spaceship.pos.Set(pX, pY);

	
}

void oSpaceship::SetSpriteID(int a_id)
{
	iSpriteID = a_id;
}
