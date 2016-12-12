#include "asteroids.h";
#include "UGFW.h";
#include "algorithm"
#include "iostream"

extern int g_iScreenHeight;
extern int g_iScreenWidth;

oAsteroid::oAsteroid()
{
	
}

oAsteroidLarge::oAsteroidLarge(oSpawnController& a_spawncontroller, int a_currentAsteroid)
{
	iScore = 20;
	iWidth = 72;
	iHeight = 72;
	iRadius = 36;
	fSpeedMax = 1.0f;
	fSpeedMin = 0.15f;
	Initialise(a_spawncontroller, cLargeAsteroidFileName[a_currentAsteroid], a_currentAsteroid);
}

void oAsteroidLarge::Initialise(oSpawnController& a_spawncontroller, const char* a_AsteroidLargeImageFileName, int a_currentAsteroid)
{
	iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)iWidth, (float)iHeight);
	pos.Set(a_spawncontroller.iSpawnPosArray[a_currentAsteroid][0], a_spawncontroller.iSpawnPosArray[a_currentAsteroid][1]);
	pos.Get(fPosX, fPosY);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}

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
void oAsteroid::SetIsDead(bool a_IsDead)
{
	bIsDead = a_IsDead;
}
bool oAsteroid::IsDead()
{
	return bIsDead;
}
oAsteroidMedium::oAsteroidMedium(float a_AsteroidLargePosX, float a_AsteroidlargePosY, int a_currentAsteroid)
{
	iScore = 50;
	iWidth = 36;
	iHeight = 36;
	iRadius = 18;
	fSpeedMax = 1.2f;
	fSpeedMin = 0.25f;
	Initialise(cMediumAsteroidFileName[a_currentAsteroid], a_AsteroidLargePosX, a_AsteroidlargePosY);
}

void oAsteroidMedium::Initialise(const char * a_AsteroidMediumImageFileName, float a_AsteroidLargePosX, float a_AsteroidLargePosY)
{
	iSpriteID = UG::CreateSprite(a_AsteroidMediumImageFileName, (float)iWidth, (float)iHeight);
	pos.Set(a_AsteroidLargePosX, a_AsteroidLargePosY);
	pos.Get(fPosX, fPosY);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}

oAsteroidSmall::oAsteroidSmall(float a_AsteroidMediumPosX, float a_AsteroidMediumPosY, int a_currentAsteroid)
{
	iScore = 100;
	iWidth = 18;
	iHeight = 18;
	iRadius = 9;
	fSpeedMax = 1.3f;
	fSpeedMin = 0.35f;
	Initialise(cSmallAsteroidFileName[a_currentAsteroid], a_AsteroidMediumPosX, a_AsteroidMediumPosY);
}

void oAsteroidSmall::Initialise(const char * a_AsteroidSmallImageFileName, float a_AsteroidMediumPosX, float a_AsteroidMediumPosY)
{
	iSpriteID = UG::CreateSprite(a_AsteroidSmallImageFileName, (float)iWidth, (float)iHeight);
	pos.Set(a_AsteroidMediumPosX, a_AsteroidMediumPosY);
	pos.Get(fPosX, fPosY);
	vNew.SetRandom(fSpeedMin, fSpeedMax);
	SetRotation(fSpriteTurnRate);
	UG::DrawSprite(iSpriteID);
	UG::MoveSprite(iSpriteID, fPosX, fPosY);
}