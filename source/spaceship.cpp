#include "spaceship.h";
#include "UGFW.h";
#define _USE_MATH_DEFINES
#include "math.h";

oSpaceship::oSpaceship()
{

}

void oSpaceship::Initialise(oSpaceship& a_spaceship, const char* a_spaceshipImageFileName, float a_fXPos, float a_fYPos)
{
	a_spaceship.pos.Set(a_fXPos, a_fYPos);
	a_spaceship.iSpriteID = UG::CreateSprite(a_spaceshipImageFileName, (float)a_spaceship.iWidth, (float)a_spaceship.iHeight);
	float fX = 0.f, fY = 0.f;
	a_spaceship.pos.Get(fX, fY);
	UG::MoveSprite(a_spaceship.iSpriteID, fX, fY);
}

void oSpaceship::SetSpaceshipMovementKeys(oSpaceship & a_spaceship, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, short a_breakKey)
{
	a_spaceship.upKey = a_upKey;
	a_spaceship.downKey = a_downKey;
	a_spaceship.leftKey = a_leftKey;
	a_spaceship.rightKey = a_rightKey;
	a_spaceship.breakKey = a_breakKey;

}

void oSpaceship::MoveSpaceship(oSpaceship & a_spaceship)
{
	int iDirection = 0;
	float iSpriteTurnRate = 0;
	if (UG::IsKeyDown(a_spaceship.upKey)) // Accelerate the ship in the current facing direction
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
	}
	if (UG::IsKeyDown(a_spaceship.rightKey))
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
	if (UG::IsKeyDown(a_spaceship.leftKey))
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

	if (UG::IsKeyDown(a_spaceship.breakKey))
	{
		int testint = 0;
	}
	

	float pX = 0.f, pY = 0.f;
	a_spaceship.pos.Get(pX, pY);


	float newPositionY = pY + iyVelocity;
	float newPositionX = pX + ixVelocity;

	pY = newPositionY;
	pX = newPositionX;

	UG::MoveSprite(a_spaceship.iSpriteID, pX, pY);
	UG::RotateSprite(a_spaceship.iSpriteID,iSpriteTurnRate);
	a_spaceship.pos.Set(pX, pY);

	
}
