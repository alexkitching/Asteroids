#include "UGFW.h"
#include "Enumerations.h"

#include <time.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <iostream>

#include "GameStates.h"
#include "menu.h"
#include "spaceship.h"
#include "asteroids.h"

void InitialiseGameAssets(oSpaceship& a_spaceship, oAsteroidLarge& a_asteroidlarge);

int g_iScreenWidth = 0;
int g_iScreenHeight = 0;
float g_DeltaTime = 0.0f;

int main(int argv, char* argc[])
{
	GameState currentState = MENU;
	bool bShouldQuit = false;
	
	do
	{
		switch (currentState)
		{
		case MENU:
		{
			Menu menu;
			currentState = menu.Initialise();
			break;
		}
		case GAMEPLAY:
		{
			//Screen Dimensions
			

			

			if (UG::Create(1024, 768, false, "Asteroids", 100, 100))
			{
				UG::GetScreenSize(g_iScreenWidth, g_iScreenHeight);

				UG::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));
				//UG::AddFont("./fonts/pixel.ttf");

				//Create Spaceship Sprite
				oSpaceship spaceship;
				oAsteroidLarge asteroid[4];
				InitialiseGameAssets(spaceship, asteroid[4]);
				
				do
				{
					g_DeltaTime = UG::GetDeltaTime();
					spaceship.MoveSpaceship(spaceship);
					UG::ClearScreen();
				} while (UG::Process());
			}
			UG::Dispose();
			break;
		}
		case GAMEOVER:
		{
			bShouldQuit = true;
			break;
		}
		}
	} while (!bShouldQuit);

	return 0;
}


#pragma region Initialisation - Initialisation of Assets
void InitialiseGameAssets(oSpaceship& a_spaceship, oAsteroidLarge& a_AsteroidLarge)
{
	//Initialise Spaceship
	oSpaceship spaceship;
	spaceship.Initialise(a_spaceship, "./images/Ship.png", g_iScreenWidth * 0.5f, g_iScreenHeight *0.1f);
	spaceship.SetSpaceshipMovementKeys(a_spaceship, UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_P);
	UG::DrawSprite(a_spaceship.iSpriteID);
	//Initialise Large Asteroids
	oAsteroidLarge asteroid[4];
	char cSpriteFileName[4][28] = { { "./images/LargeAsteroid1.png" },{ "./images/LargeAsteroid2.png" },{ "./images/LargeAsteroid3.png" },{ "./images/LargeAsteroid4.png" } };
	for (int i = 0; i < 4; ++i)
	{
		
		asteroid[i].Initialise(a_AsteroidLarge, cSpriteFileName[i]);
	}
	
}
#pragma endregion

