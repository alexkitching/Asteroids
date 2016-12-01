#include "asteroids.h";
#include "UGFW.h";

oAsteroidLarge::oAsteroidLarge()
{

}

void oAsteroidLarge::Initialise(oAsteroidLarge & a_AsteroidLarge, const char * a_AsteroidLargeImageFileName)
{

	a_AsteroidLarge.pos.SetRandom();
	a_AsteroidLarge.iSpriteID = UG::CreateSprite(a_AsteroidLargeImageFileName, (float)a_AsteroidLarge.iWidth, (float)a_AsteroidLarge.iHeight);
	float fX = 0.f, fY = 0.f;
	a_AsteroidLarge.pos.Get(fX, fY);
	UG::MoveSprite(a_AsteroidLarge.iSpriteID, fX, fY);
	
}

void oAsteroidLarge::Update(oAsteroidLarge & a_AsteroidLarge)
{
}

void oAsteroidLarge::CheckSpawnCollision(oAsteroidLarge & a_asteroidlarge)
{
}

oAsteroidSmall::oAsteroidSmall()
{
}

void oAsteroidSmall::Initialise(oAsteroidSmall & a_AsteroidSmall, const char * a_AsteroidSmallImageFileName)
{
}

void oAsteroidSmall::Update(oAsteroidSmall & a_AsteroidSmall)
{
}
