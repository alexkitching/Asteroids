#include "asteroids.h";
#include "UGFW.h";
#include "algorithm"
#include "iostream"

extern int g_iScreenHeight;
extern int g_iScreenWidth;

void oAsteroid::GetDimensions(int &a_iWidth, int &a_iHeight)
{
	a_iWidth = iWidth, a_iHeight = iHeight;
}

void oAsteroid::GetPos(float & a_PosX, float & a_PosY)
{
	a_PosX = fPosX;
	a_PosY = fPosY;
}

void oAsteroid::GetRadius(int & a_Radius)
{
	a_Radius = iRadius;
}

void oAsteroid::SetRotation(float &a_CurrentRotation)
{
	int iValue = rand() % 2;
	if (iValue == 0)
	{
		a_CurrentRotation = -1.f;
	}
	else if (iValue == 1)
	{
		a_CurrentRotation = 1.f;
	}
}

void oAsteroid::SetIsActive(bool a_IsActive)
{
	bIsActive = a_IsActive;
}

void oAsteroid::SetHasCollied(bool a_HasCollided)
{
	bHasCollided = a_HasCollided;
}

bool oAsteroid::HasCollided()
{
	return bHasCollided;
}

bool oAsteroid::IsActive()
{
	return bIsActive;
}

oAsteroidLarge::oAsteroidLarge()
{
	iSpriteID = -1;
	iScore = 20;
	iWidth = 72;
	iHeight = 72;
	iRadius = 36;
	fSpeedMax = 1.0f;
	fSpeedMin = 0.15f;
	fSpriteTurnRate = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bShattered = false;
	bIsActive = false;
	bHasCollided = false;
	bScoreUpdated = false;
	vNew = Vector(0.0f, 0.0f);
}

void oAsteroidLarge::Initialise(const char* a_AsteroidLargeImageFileName)
{
	iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)iWidth, (float)iHeight);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
}

void oAsteroidLarge::Draw(oSpawnController& a_spawncontroller, int a_currentAsteroid)
{
	bHasCollided = false;
	bIsActive = true;
	bShattered = false;
	bScoreUpdated = false;
	pos.Set(a_spawncontroller.iSpawnPosArray[a_currentAsteroid][0], a_spawncontroller.iSpawnPosArray[a_currentAsteroid][1]);
	pos.Get(fPosX, fPosY);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}

void oAsteroidLarge::Destroy(oAsteroidLarge& a_asteroidlarge)
{

	a_asteroidlarge.bHasCollided = true;
	UG::StopDrawingSprite(a_asteroidlarge.iSpriteID);
	UG::DestroySprite(a_asteroidlarge.iSpriteID);
	a_asteroidlarge.iSpriteID = -1;
}

void oAsteroidLarge::ResetVars(oAsteroidLarge & a_asteroidlarge)
{
	a_asteroidlarge.fSpriteTurnRate = 0.f;
	a_asteroidlarge.fPosX = 0.f;
	a_asteroidlarge.fPosY = 0.f;
	a_asteroidlarge.fVNewX = 0.f;
	a_asteroidlarge.fVNewY = 0.f;
	a_asteroidlarge.vNew = Vector(0.0f, 0.0f);
}

void oAsteroidLarge::Respawn(oAsteroidLarge& a_asteroidlarge,int a_currentAsteroid)
{
	a_asteroidlarge.Initialise(cLargeAsteroidFileName[a_currentAsteroid]);
	a_asteroidlarge.bHasCollided = false;
	a_asteroidlarge.bIsActive = true;
	a_asteroidlarge.bShattered = false;
	a_asteroidlarge.bScoreUpdated = false;
	a_asteroidlarge.pos.Set(a_asteroidlarge.fLargeAsteroidRespawnPosArray[a_currentAsteroid][0], a_asteroidlarge.fLargeAsteroidRespawnPosArray[a_currentAsteroid][1]);
	a_asteroidlarge.pos.Get(a_asteroidlarge.fPosX, a_asteroidlarge.fPosY);
	UG::DrawSprite(a_asteroidlarge.iSpriteID);
	UG::MoveSprite(a_asteroidlarge.iSpriteID, a_asteroidlarge.fPosX, a_asteroidlarge.fPosY);
}

oAsteroidMedium::oAsteroidMedium()
{
	iSpriteID = -1;
	iScore = 50;
	iWidth = 36;
	iHeight = 36;
	iRadius = 18;
	fSpeedMax = 1.2f;
	fSpeedMin = 0.25f;
	fSpriteTurnRate = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bShattered = false;
	bIsActive = false;
	bHasCollided = false;
	bScoreUpdated = false;
	vNew = Vector(0.0f, 0.0f);
}

void oAsteroidMedium::Initialise(const char * a_AsteroidMediumImageFileName)
{
	iSpriteID = UG::CreateSprite(a_AsteroidMediumImageFileName, (float)iWidth, (float)iHeight);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
}

void oAsteroidMedium::Draw(float a_AsteroidLargePosX, float a_AsteroidLargePosY)
{
	bHasCollided = false;
	bIsActive = true;
	pos.Set(a_AsteroidLargePosX, a_AsteroidLargePosY);
	pos.Get(fPosX, fPosY);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}

void oAsteroidMedium::Destroy(oAsteroidMedium& a_asteroidmedium)
{
	a_asteroidmedium.bHasCollided = true;
	UG::StopDrawingSprite(a_asteroidmedium.iSpriteID);
	UG::DestroySprite(a_asteroidmedium.iSpriteID);
	a_asteroidmedium.iSpriteID = -1;

}

void oAsteroidMedium::ResetVars(oAsteroidMedium & a_asteroidmedium)
{
	a_asteroidmedium.fSpriteTurnRate = 0.f;
	a_asteroidmedium.fPosX = 0.f;
	a_asteroidmedium.fPosY = 0.f;
	a_asteroidmedium.fVNewX = 0.f;
	a_asteroidmedium.fVNewY = 0.f;
	a_asteroidmedium.vNew = Vector(0.0f, 0.0f);
	a_asteroidmedium.bHasCollided = false;
	a_asteroidmedium.bShattered = false;
	a_asteroidmedium.bScoreUpdated = false;
}

oAsteroidSmall::oAsteroidSmall()
{
	iSpriteID = -1;
	iScore = 100;
	iWidth = 18;
	iHeight = 18;
	iRadius = 9;
	fSpeedMax = 1.3f;
	fSpeedMin = 0.35f;
	fSpriteTurnRate = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bShattered = false;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false; 
	vNew = Vector(0.0f, 0.0f);
}

void oAsteroidSmall::Initialise(const char * a_AsteroidSmallImageFileName)
{
	iSpriteID = UG::CreateSprite(a_AsteroidSmallImageFileName, (float)iWidth, (float)iHeight);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
	
}

void oAsteroidSmall::Draw(float a_AsteroidMediumPosX, float a_AsteroidMediumPosY)
{
	bHasCollided = false;
	bIsActive = true;
	pos.Set(a_AsteroidMediumPosX, a_AsteroidMediumPosY);
	pos.Get(fPosX, fPosY);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}

void oAsteroidSmall::Destroy(oAsteroidSmall& a_asteroidsmall)
{
	a_asteroidsmall.bHasCollided = true;
	UG::StopDrawingSprite(a_asteroidsmall.iSpriteID);
	UG::DestroySprite(a_asteroidsmall.iSpriteID);
	a_asteroidsmall.iSpriteID = -1;
}

void oAsteroidSmall::ResetVars(oAsteroidSmall & a_asteroidsmall)
{
	a_asteroidsmall.fSpriteTurnRate = 0.f;
	a_asteroidsmall.fPosX = 0.f;
	a_asteroidsmall.fPosY = 0.f;
	a_asteroidsmall.fVNewX = 0.f;
	a_asteroidsmall.fVNewY = 0.f;
	a_asteroidsmall.vNew = Vector(0.0f, 0.0f);
	a_asteroidsmall.bHasCollided = false;
	a_asteroidsmall.bShattered = false;
	a_asteroidsmall.bScoreUpdated = false;
}
