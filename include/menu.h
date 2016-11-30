#ifndef _MENU_H_
#define _MENU_H_
#include <string>
#include "GameStates.h"

class Menu
{
public:
	Menu();
	GameState Initialise();
private:
	bool onMenu;
	int selectedItem;
	GameState newState;
	std::string menuItem[3] = { "[Play Game]", "[Options]", "[Exit Game]" };

};

#endif