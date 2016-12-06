#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "position.h"

class Background
{
public:
	Background();
	void Initialise();
	void Draw();
	void Update();
private:
	Position pos[100];
};

#endif