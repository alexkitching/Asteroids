#include "UGFW.h"
#include "Enumerations.h"

#include <time.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <iostream>

#include "GameStates.h"

int main(int argv, char* argc[])
{
	GameState currentState = MENU;
	bool bShouldQuit = false;
	bool onMenu = true;
	do
	{
		switch (currentState)
		{
		case MENU:
		{
			std::string menuItem[3] = { "[Play Game]", "[Options]", "[Exit Game]" };
			int selectedItem = 0;
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
								currentState = GAMEPLAY;
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
								currentState = GAMEOVER;
								onMenu = false;
								break;
							}
						}
						break;
					}
				}
				Sleep(200);
			}
		}
		case GAMEPLAY:
		{

			if (UG::Create(1024, 768, false, "Asteroids", 100, 100))
			{
				do
				{

				} while (UG::Process);
			}
			UG::Dispose();
		}
		case GAMEOVER:
		{
			bShouldQuit = true;
		}
		}
	} while (!bShouldQuit);

	return 0;
}



