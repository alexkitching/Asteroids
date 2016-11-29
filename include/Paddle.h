#ifndef _PADDLE_H_
#define _PADDLE_H_
#include "Position.h"

// This is our structure definition

class Paddle
{
public: //All public??

	//Paddle Data with default values assigned
	int iSpriteID = -1;
	//Width & Height variables
	int iWidth = 64;
	int iHeight = 256;
	//Paddle Speed variable
	int iSpeed = 1;
	//Paddle screen position variables
	Position pos;
	//Paddle Input Key variables
	short upKey = -1;
	short downKey = -1;

};

#endif
