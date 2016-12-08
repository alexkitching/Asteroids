#ifndef _SPAWNCONTROLLER_H_
#define _SPAWNCONTROLLER_H_
#include "position.h"
class oSpawnController
{
public:
	oSpawnController();
	void SpawnController(int a_MaxObjects, int a_ObjectWidth, int a_ObjectHeight);

	float iSpawnPosArray[5][2] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };

private:
	float fNewPosX = 0.f;
	float fNewPosY = 0.f;
	float fOldXPosMax = 0.f;
	float fOldXPosMin = 0.f;
	float fNewXPosMax = 0.f;
	float fNewXPosMin = 0.f;
	float fOldYPosMax = 0.f;
	float fOldYPosMin = 0.f;
	float fNewYPosMax = 0.f;
	float fNewYPosMin = 0.f;
	int iObjectWidth = 0;
	int iObjectHeight = 0;

	Position pos;
};
#endif