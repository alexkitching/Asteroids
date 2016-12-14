////////////////////////////////////////////////////////////////////
// File: <menu.h>
// Author: <Alex Kitching>
// Date Created: <30/11/16>
// Brief: <Header file for the Menu Class.>
////////////////////////////////////////////////////////////////////
#ifndef _MENU_H_
#define _MENU_H_

#include <string>
#include "GameStates.h"

class Menu
{
public:

	Menu(); //Constructor
	~Menu() {}; //Destructor

	GameState Initialise();
private:

	//Variables
	bool bActive;
	int iSelectedItem;
	GameState gsNewState;
	std::string menuItem[4] = { " [Play Game]", " [How to Play]", " [Scoreboard]", " [Exit Game]" };

};

#endif // !_MENU_H_