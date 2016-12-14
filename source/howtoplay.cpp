////////////////////////////////////////////////////////////////////
// File: <howtoplay.cpp>
// Author: <Alex Kitching>
// Date Created: <14/12/16>
// Brief: <Source file for How to Play Class.>
////////////////////////////////////////////////////////////////////

#include "howtoplay.h"
#include <iostream>
#include <windows.h>

GameState Howtoplay::Initialise()
{
	while (bActive == true)
	{
		ClearScreen();

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
				iSelectedItem += 1; //Scroll Through Items
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
					ClearScreen(); // Print Controls
					std::cout << "Controls:" << std::endl;
					std::cout << "Accelerate - Up Arrow Key" << std::endl;
					std::cout << "Turn Left and Right - Left and Right Arrow Keys" << std::endl;
					std::cout << "Fire - Spacebar" << std::endl;
					std::cout << "Exit Game - Escape" << std::endl;
					system("PAUSE");
					Sleep(1000);
					break;
				}
				case 1:
				{
					ClearScreen(); // Print Goal
					std::cout << "Goal:" << std::endl;
					std::cout << "The Aim of the Game is to Reach the Highest Score and Beat Your Friends!" << std::endl;
					std::cout << "Shoot the Various Enemies to Gain Points." << std::endl;
					std::cout << "When the Space is Clear of Enemies, the Next Round Begins." << std::endl;
					std::cout << "Every 10,000 points, You gain an Extra Life of the 3 you Begin with." << std::endl;
					system("PAUSE");
					Sleep(1000);
					break;
				}
				case 2:
				{
					ClearScreen(); // Print Enemies
					std::cout << "Enemies:" << std::endl;
					std::cout << "Asteroids:" << std::endl;
					std::cout << "Large Asteroids - Slow Speed, Worth 20 Points, Shatter into 3 Medium Asteroids." << std::endl;
					std::cout << "Medium Asteroids - Medium Speed, Worth 50 Points, Shatter into 3 Small Asteroids." << std::endl;
					std::cout << "Small Asteroids - Fast Speed, Worth 100 Points." << std::endl;
					std::cout << std::endl;
					std::cout << "Large UFO:" << std::endl;
					std::cout << "Medium Speed, Worth 200 Points, Moves Up and Down at Set Intervals," << std::endl;
					std::cout << "When off screen, appears at different location, Fires Slow Bullets Randomly." << std::endl;
					std::cout << std::endl;
					std::cout << "Small UFO:" << std::endl;
					std::cout << "Fast Speed, Worth 1000 Points, Moves Left and Right, Changes Direction Randomly, When off screen appears at different locations" << std::endl;
					std::cout << "When off screen appears at different locations, Fires Fast Bullets Towards the Player." << std::endl;
					system("PAUSE");
					Sleep(1000);
					break;
				}
				case 3:
				{
					gsNewState = GameState::MENU; //Return to Menu
					bActive = false;
					Howtoplay::~Howtoplay();
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

void Howtoplay::ClearScreen()
{
	system("cls");
	std::cout << "Asteroids - How to Play" << std::endl;
}
