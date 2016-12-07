#include "spaceship.h"
#include "UGFW.h"
#define _USE_MATH_DEFINES
#include "math.h"

extern float g_DeltaTime;
extern int g_iScreenHeight;
extern int g_iScreenWidth;


oSpaceship::oSpaceship()
{

}

void oSpaceship::Initialise(oSpaceship& a_Spaceship, const char* a_SpaceshipImageFileName, float a_fXPos, float a_fYPos)
{
	a_Spaceship.pos.Set(a_fXPos, a_fYPos);
	a_Spaceship.iSpriteID = UG::CreateSprite(a_SpaceshipImageFileName, (float)a_Spaceship.iWidth, (float)a_Spaceship.iHeight);
	a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
	UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
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
	a_Spaceship.fCurrentTurnRate = 0.f;
	
	
	a_Spaceship.pos.Get(a_Spaceship.fPosX, a_Spaceship.fPosY);
	a_Spaceship.VecNew.Get(a_Spaceship.fNewVecX, a_Spaceship.fNewVecY);
	if (UG::IsKeyDown(a_Spaceship.upKey)) // Accelerate the ship in the current facing direction
	{
		a_Spaceship.fNewVecX += fAcceleration * cosf(a_Spaceship.fFacingAngleRad);
		a_Spaceship.fNewVecY += fAcceleration * sinf(a_Spaceship.fFacingAngleRad);
		a_Spaceship.VecNew.Set(a_Spaceship.fNewVecX, a_Spaceship.fNewVecY);
		a_Spaceship.fTotalVelocity = a_Spaceship.VecNew.Magnitude();

		//Cap Speed at Maximum Velocity
		if (a_Spaceship.fTotalVelocity > fMaxVelocity)
		{
			a_Spaceship.fTotalVelocity = fMaxVelocity;
			a_Spaceship.fNewVecX = a_Spaceship.fTotalVelocity * cosf(a_Spaceship.fMovementAngleRad);
			a_Spaceship.fNewVecY = a_Spaceship.fTotalVelocity * sinf(a_Spaceship.fMovementAngleRad);
		}

		if ((fNewVecX == 0.0) && (fNewVecY == 0.0)) // If ship is stationary the movement angle is equal to the facing angle.
		{
			a_Spaceship.fMovementAngleRad = a_Spaceship.fFacingAngleRad;
		}
		else if ((fNewVecX != 0.0) && (fNewVecY != 0.0)) // Else if the ship isn't stationary the movement angle is equal to the inverse tangent of the vector components.
		{
			a_Spaceship.fMovementAngleRad = atan2(a_Spaceship.fNewVecX, a_Spaceship.fNewVecY);
		}
	}
	if (UG::IsKeyDown(a_Spaceship.rightKey))
	{
		a_Spaceship.fCurrentTurnRate = -fTurnRate;
		a_Spaceship.fFacingAngleDeg += a_Spaceship.fCurrentTurnRate;
		a_Spaceship.fFacingAngleDeg = AngleWrap(a_Spaceship.fFacingAngleDeg);
		fFacingAngleRad = a_Spaceship.fFacingAngleDeg * degtorad;
	}
	if (UG::IsKeyDown(a_Spaceship.leftKey))
	{
		a_Spaceship.fCurrentTurnRate = fTurnRate;
		a_Spaceship.fFacingAngleDeg += a_Spaceship.fCurrentTurnRate;
		a_Spaceship.fFacingAngleDeg = AngleWrap(a_Spaceship.fFacingAngleDeg);
		fFacingAngleRad = a_Spaceship.fFacingAngleDeg * degtorad;
	}

	if (UG::IsKeyDown(a_Spaceship.breakKey))
	{
		int testint = 0;
	}
	
	a_Spaceship.fNewVecX *= fDrag;
	a_Spaceship.fNewVecY *= fDrag;
	a_Spaceship.VecNew.Set(a_Spaceship.fNewVecX, a_Spaceship.fNewVecY);
	a_Spaceship.fCurrentVecX = a_Spaceship.fPosX + a_Spaceship.fNewVecX;
	a_Spaceship.fCurrentVecY = a_Spaceship.fPosY + a_Spaceship.fNewVecY;
	a_Spaceship.fPosX = a_Spaceship.fCurrentVecX;
	a_Spaceship.fPosY = a_Spaceship.fCurrentVecY;
	

	if (a_Spaceship.fPosY >= g_iScreenHeight + iHeight)
	{
		a_Spaceship.fPosY = (0 * g_iScreenHeight) - iHeight;
	}
	else if (a_Spaceship.fPosY <= -iHeight)
	{
		a_Spaceship.fPosY = (g_iScreenHeight + iHeight);
	}
	
	if (a_Spaceship.fPosX >= g_iScreenWidth + iWidth)
	{
		a_Spaceship.fPosX = (0 * g_iScreenWidth) - iWidth;
	}
	else if (a_Spaceship.fPosX <= -iWidth)
	{
		a_Spaceship.fPosX = (g_iScreenWidth + iWidth);

	}


	UG::MoveSprite(a_Spaceship.iSpriteID, a_Spaceship.fPosX, a_Spaceship.fPosY);
	UG::RotateSprite(a_Spaceship.iSpriteID, a_Spaceship.fCurrentTurnRate);
	a_Spaceship.pos.Set(a_Spaceship.fPosX, a_Spaceship.fPosY);
	

}

float oSpaceship::AngleWrap(float x)
{
	float y;
	y = fmodf(x, 360);
	if (y < 0)
	{
		y += 360;
		return y;
	}
	else if (y > 1)
	{
		y -= 360;
		return y;
	}
	return x;
}

