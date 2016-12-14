////////////////////////////////////////////////////////////////////
// File: <howtoplay.h>
// Author: <Alex Kitching>
// Date Created: <14/12/16>
// Brief: <Header file for How to Play Class.>
////////////////////////////////////////////////////////////////////
#ifndef _HOWTOPLAY_H_
#define _HOWTOPLAY_H_

#include "GameStates.h"
#include <iostream>
#include <string>

class Howtoplay
{
public:

	Howtoplay() { bActive = true; iSelectedItem = 1; } //Constructor
	~Howtoplay() {}; //Destructor

	GameState Initialise();

private:

	//Variables
	bool bActive;
	int iSelectedItem;
	GameState gsNewState;
	std::string menuItem[4] = { " [Controls]", " [Goal]", " [Enemies]", " [Back to Menu]" };
	void ClearScreen();
};
#endif // !_HOWTOPLAY_H_
