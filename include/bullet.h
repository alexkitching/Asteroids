#ifndef _BULLET_H_
#define _BULLET_H_
#include "position.h"
#include "asteroids.h"
#include "vector.h"
class oBullet
{
public:
	oBullet() {};
	~oBullet() {};
	bool IsActive(oBullet& a_Bullet);
	bool IsDrawn(oBullet& a_Bullet);
	bool HasExpired(oBullet& a_Bullet);
	void SetIsActive(bool a_IsActive);
	void SetIsDrawn(bool a_IsDrawn);
	void SetHasExpired(bool a_HasExpired);
	void Draw(oBullet& a_Bullet, float fSpaceshipFacingAngle, float fSpaceshipPosX, float fSpaceshipPosY);
	void Destroy(oBullet& a_Bullet);
	void CheckAsteroidCollision(oBullet& a_Bullet, oAsteroidLarge* a_asteroidlargearray, oAsteroidMedium* a_asteroidmediumarray, oAsteroidSmall* a_asteroidsmallarray, int& a_asteroidlargedeathcount, int& a_asteroidmediumdeathcount, int& a_asteroidsmalldeathcount);
	void GetDimensions(int& a_iWidth, int& a_iHeight);
	void GetPos(float& a_PosX, float& a_PosY);
	void GetRadius(float &a_fRadius);
	int iSpriteID = -1;
	friend class oObjectUpdateController;
private:
	int iHeight = 3;
	int iWidth = 3;
	bool bIsActive = false;
	bool bHasExpired = false;
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
