////////////////////////////////////////////////////////////////////
// File: <Spawncontroller.h>
// Author: <Alex Kitching>
// Date Created: <6/12/16>
// Brief: <Header file for the Spawn Controller Class.>
////////////////////////////////////////////////////////////////////
#ifndef _Spawncontroller_H_
#define _Spawncontroller_H_

#include "vector.h"
#include "ufo.h"
#include "Scorecontroller.h"

class oSpawncontroller
{
public:
	oSpawncontroller() {}; //Constructor
	~oSpawncontroller() {}; //Destructor

	//Functions
	void Spawncontroller(int a_MaxObjects, const int a_ObjectWidth, const int a_ObjectHeight);
	void UFOSpawncontroller(oUFOEasy& a_rUFOEasy, oUFOHard& a_rUFOHard, oScorecontroller& a_rScorecontroller );
	float afSpawnPosArray[5][2] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } }; //Spawn Location Array

private:

	//Dimension Variables
	int iObjectWidth = 0;
	int iObjectHeight = 0;

	//Position Variables
	Vector pos;
};
#endif // !_Spawncontroller_H_
