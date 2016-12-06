#include "menu.h"
#include <iostream>
#include <string>
#include <windows.h>
Menu::Menu()
{
	onMenu = true;
	selectedItem = 0;
}

Menu::~Menu()
{
}

GameState Menu::Initialise()
{
	while (onMenu == true)
	{
		system("cls"); // Resets Console Window

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Sets Console Text to White

		std::cout << "     ___           _______.___________. _______ .______        ______    __   _______       _______.\n";
		std::cout << "    /   \\         /       |           ||   ____||   _  \\      /  __  \\  |  | |       \\     /       |\n";
		std::cout << "   /  ^  \\       |   (----`---|  |----`|  |__   |  |_)  |    |  |  |  | |  | |  .--.  |   |   (----`\n";
		std::cout << "  /  /_\\  \\       \\   \\       |  |     |   __|  |      /     |  |  |  | |  | |  |  |  |    \\   \\    \n";
		std::cout << " /  _____  \\  .----)   |      |  |     |  |____ |  |\\  \\----.|  `--'  | |  | |  '--'  |.----)   |   \n";
		std::cout << "/__/     \\__\\ |_______/       |__|     |_______|| _| `._____| \\______/  |__| |_______/ |_______/    \n\n";

		for (int i = 0; i < 3; ++i)
		{
			if (i == selectedItem) // Hightlights selected Item
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

		while (onMenu == true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				selectedItem -= 1;
				if (selectedItem == -1)
				{
					selectedItem = 2;
				}
				break;
			}

			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				selectedItem += 1;
				if (selectedItem == 3)
				{
					selectedItem = 0;
				}
				break;
			}

			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (selectedItem)
				{
				case 0:
				{
					std::cout << "\n\n\nPrepare your thrusters! - Starting Game";
					Sleep(1000);
					newState = GameState::GAMEPLAY;
					onMenu = false;
					break;
				}
				case 1:
				{
					std::cout << "Options Menu test...";
					Sleep(1000);
					break;
				}
				case 2:
				{
					newState = GameState::GAMEOVER;
					onMenu = false;
					break;

				}
				}
				break;
			}
		}
		Sleep(200);
	}
	
	system("cls");
	return(newState);
	Menu::~Menu();
}