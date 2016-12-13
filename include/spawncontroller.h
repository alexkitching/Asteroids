#ifndef _SPAWNCONTROLLER_H_
#define _SPAWNCONTROLLER_H_
#include "position.h"
class oSpawnController
{
public:
	oSpawnController() {};
	void SpawnController(int a_MaxObjects, int a_ObjectWidth, int a_ObjectHeight);
	float iSpawnPosArray[5][2] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };

private:
	int iObjectWidth = 0;
	int iObjectHeight = 0;

	Position pos;
};
#endif