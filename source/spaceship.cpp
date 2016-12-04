#include "spaceship.h";
#include "UGFW.h";
#define _USE_MATH_DEFINES
#include "math.h";

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
	float fVelocityZero = 0.0;
	fCurrentTurnRate = 0.0;

	if (UG::IsKeyDown(a_Spaceship.upKey)) // Accelerate the ship in the current facing direction
	{
		VecNew.fX += fAcceleration * cosf(fFacingAngleRad);
		VecNew.fY += fAcceleration * sinf(fFacingAngleRad);

		fTotalVelocity = VecNew.Magnitude() *g_DeltaTime;

		//Cap Speed at Maximum Velocity
		if (fTotalVelocity > fMaxVelocity)
		{
			fTotalVelocity = fMaxVelocity * g_DeltaTime;
			VecNew.fX = fTotalVelocity * cosf(fMovementAngleRad);
			VecNew.fY = fTotalVelocity * sinf(fMovementAngleRad);
		}

		if ((VecNew.fX == 0.0) && (VecNew.fY == 0.0)) // If ship is stationary the movement angle is equal to the facing angle.
		{
			fMovementAngleRad = fFacingAngleRad;
		}
		else if ((VecNew.fX != 0.0) && (VecNew.fY != 0.0)) // Else if the ship isn't stationary the movement angle is equal to the inverse tangent of the vector components.
		{
			fMovementAngleRad = atan2(VecNew.fX, VecNew.fY);
		}
	}
	else if (UG::IsKeyDown(a_Spaceship.upKey) == false)
	{
		if (VecNew.fX > fVelocityZero)
		{
			VecNew.fX -= fDrag;
		}
		else if (VecNew.fX < fVelocityZero)
		{
			VecNew.fX += fDrag;
		}

		if (VecNew.fY > fVelocityZero)
		{
			VecNew.fY -= fDrag;
		}
		else if (VecNew.fY < fVelocityZero)
		{
			VecNew.fY += fDrag;
		}
	}
	if (UG::IsKeyDown(a_Spaceship.rightKey))
	{
		fCurrentTurnRate = -fTurnRate;
		fFacingAngleDeg += fCurrentTurnRate;
		fFacingAngleDeg = AngleWrap(fFacingAngleDeg);
		fFacingAngleRad = fFacingAngleDeg * degtorad;
	}
	if (UG::IsKeyDown(a_Spaceship.leftKey))
	{
		fCurrentTurnRate = fTurnRate;
		fFacingAngleDeg += fCurrentTurnRate;
		fFacingAngleDeg = AngleWrap(fFacingAngleDeg);
		fFacingAngleRad = fFacingAngleDeg * degtorad;
	}

	if (UG::IsKeyDown(a_Spaceship.breakKey))
	{
		int testint = 0;
	}

	float pX = 0.f, pY = 0.f;
	a_Spaceship.pos.Get(pX, pY);
	VecCurrent.fX = pX + VecNew.fX;
	VecCurrent.fY = pY + VecNew.fY;
	pX = VecCurrent.fX;
	pY = VecCurrent.fY;

	if (pY >= g_iScreenHeight + a_Spaceship.iHeight)
	{
		pY = (0 * g_iScreenHeight) - a_Spaceship.iHeight;
	}
	else if (pY <= -a_Spaceship.iHeight)
	{
		pY = (g_iScreenHeight + a_Spaceship.iHeight);
	}
	
	if (pX >= g_iScreenWidth + a_Spaceship.iWidth)
	{
		pX = (0 * g_iScreenWidth) - a_Spaceship.iWidth;
	}
	else if (pX <= -a_Spaceship.iWidth)
	{
		pX = (g_iScreenWidth + a_Spaceship.iWidth);
	}


	UG::MoveSprite(a_Spaceship.iSpriteID, VecCurrent.fX, VecCurrent.fY);
	UG::RotateSprite(a_Spaceship.iSpriteID, fCurrentTurnRate);
	a_Spaceship.pos.Set(pX, pY);
	

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

