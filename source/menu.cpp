////////////////////////////////////////////////////////////////////
// File: <menu.cpp>
// Author: <Alex Kitching>
// Date Created: <30/11/16>
// Brief: <Source file for the Menu Class.>
////////////////////////////////////////////////////////////////////

#include "menu.h"
#include <iostream>
#include <string>
#include <windows.h>

Menu::Menu()
{
	bActive = true;
	iSelectedItem = 0;
}

GameState Menu::Initialise()
{
	while (bActive == true)
	{
		system("cls"); // Resets Console Window

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Sets Console Text to White

		std::cout << "     ___           _______.___________. _______ .______        ______    __   _______       _______.\n";
		std::cout << "    /   \\         /       |           ||   ____||   _  \\      /  __  \\  |  | |       \\     /       |\n";
		std::cout << "   /  ^  \\       |   (----`---|  |----`|  |__   |  |_)  |    |  |  |  | |  | |  .--.  |   |   (----`\n";
		std::cout << "  /  /_\\  \\       \\   \\       |  |     |   __|  |      /     |  |  |  | |  | |  |  |  |    \\   \\    \n";
		std::cout << " /  _____  \\  .----)   |      |  |     |  |____ |  |\\  \\----.|  `--'  | |  | |  '--'  |.----)   |   \n";
		std::cout << "/__/     \\__\\ |_______/       |__|     |_______|| _| `._____| \\______/  |__| |_______/ |_______/    \n\n";

		for (int i = 0; i < 4; ++i)
		{
			if (i == iSelectedItem) // Hightlights selected Item
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				std::cout << menuItem[i] << std::endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std::cout << menuItem[i] << std::endl;
			}
		}

		while (bActive == true)
		{
			if (GetAsyncKeyState(VK_UP) != 0) //Key Up Pressed
			{
				iSelectedItem -= 1; //Scroll Through Items
				if (iSelectedItem == -1)
				{
					iSelectedItem = 3;
				}
				break;
			}

			else if (GetAsyncKeyState(VK_DOWN) != 0) //Key Down Pressed
			{
				iSelectedItem += 1;
				if (iSelectedItem == 4)
				{
					iSelectedItem = 0;
				}
				break;
			}

			else if (GetAsyncKeyState(VK_SPACE) != 0) //Key Space Pressed
			{
				switch (iSelectedItem)
				{
				case 0:
				{
					std::cout << "\n\n\nPrepare your thrusters! - Starting Game";
					Sleep(1000);
					gsNewState = GameState::GAMEPLAY; // Load Game
					bActive = false;
					Menu::~Menu();
					break;
				}
				case 1:
				{
					std::cout << "Loading How to Play...";
					Sleep(1000);
					gsNewState = GameState::HOWTOPLAY; // Load How to Play Menu
					bActive = false;
					Menu::~Menu();
					break;
				}
				case 2:
				{
					std::cout << "Loading Scoreboard...";
					Sleep(1000);
					gsNewState = GameState::SCOREBOARD; // Load Scoreboard
					bActive = false;
					Menu::~Menu();
					break;
				}
				case 3:
				{
					gsNewState = GameState::GAMEOVER; //Quit Game
					bActive = false;
					Menu::~Menu();
					break;
				}
				}
				break;
			}
		}
		Sleep(200);
	}
	
	system("cls");
	return(gsNewState);
}