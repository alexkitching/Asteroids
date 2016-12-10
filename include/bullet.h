#ifndef _BULLET_H_
#define _BULLET_H_
#include "position.h"
#include "asteroids.h"
#include "vector.h"
#include <vector>
class oBullet
{
public:
	oBullet();
	~oBullet();
	bool IsActive(std::vector<oBullet>::iterator a_Bullet);
	bool IsDrawn(std::vector<oBullet>::iterator a_Bullet);
	bool Update(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet);
	void Draw(std::vector<oBullet>::iterator a_Bullet, float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY);
	void CheckLargeAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, oAsteroidLarge& a_AsteroidLarge);
	void CheckMediumAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, oAsteroidMedium& a_AsteroidMedium);
	void CheckSmallAsteroidCollision(std::vector<oBullet>& a_bulletarray, std::vector<oBullet>::iterator a_Bullet, oAsteroidSmall& a_AsteroidSmall);
	int iSpriteID = -1;
private:
	int iHeight = 3;
	int iWidth = 3;
	bool bIsActive = false;
	bool bIsDrawn = false;
	float fRadius = 1.5f;
	float fSpeed = 2.f;
	float fCurrentDistance = 0.f;
	int fMaxDistance = 400.f;
	float fPosX = 0.f;
	float fPosY = 0.f;
	float fVNewX = 0.f;
	float fVNewY = 0.f;
	Vector vNew = Vector(0.0f, 0.0f);
	Position pos;

};
#endif
