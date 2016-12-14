////////////////////////////////////////////////////////////////////////////
// File: <asteroids.cpp>
// Author: <Alex Kitching>
// Date Created: <01/12/16>
// Brief: <Source file for all Asteroid classes and functions.>
///////////////////////////////////////////////////////////////////////////

#include "asteroids.h"
#include "UGFW.h"
#include <algorithm>
#include <iostream>

extern int g_iScreenHeight;
extern int g_iScreenWidth;

void oAsteroid::GetDimensions(int &a_riWidth, int &a_riHeight)
{
	a_riWidth = iWidth, a_riHeight = iHeight; //Retrieves Asteroid Dimensions
}

void oAsteroid::GetRadius(int & a_rRadius)
{
	a_rRadius = iRadius; //Retrieves Asteroid Radius
}

void oAsteroid::GetPos(float & a_rfPosX, float & a_rfPosY)
{
	a_rfPosX = fPosX; //Retrieves Asteroid Position
	a_rfPosY = fPosY;
}

void oAsteroid::SetRotation(float &a_rfCurrentRotation) //Randomly Generates Asteroids Sprite Rotation
{
	int iValue = rand() % 2;
	if (iValue == 0)
	{
		a_rfCurrentRotation = -1.f;
	}
	else if (iValue == 1)
	{
		a_rfCurrentRotation = 1.f;
	}
}

void oAsteroid::SetIsActive(bool a_bIsActive)
{
	bIsActive = a_bIsActive; //Sets IsActive
}

void oAsteroid::SetHasCollied(bool a_bHasCollided)
{
	bHasCollided = a_bHasCollided; //Sets HasCollided
}

void oAsteroid::SetScoreUpdated(bool a_bScoreUpdated)
{
	bScoreUpdated = a_bScoreUpdated; //Sets ScoreUpdated
}

bool oAsteroid::ScoreUpdated()
{
	return bScoreUpdated; //Checks ScoreUpdated
}

bool oAsteroid::HasCollided()
{
	return bHasCollided; //Checks Has Collided
}

bool oAsteroid::IsActive()
{
	return bIsActive; //Checks IsActive
}

oAsteroidLarge::oAsteroidLarge() //On Object Creation, Initialise Variables
{
	iSpriteID = -1;
	iScore = 20;
	iWidth = 72;
	iHeight = 72;
	iRadius = 36;
	c_fSpeedMax = 0.5f;
	c_fSpeedMin = 0.15f;
	fSpriteTurnRate = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bShattered = false;
	bIsActive = false;
	bHasCollided = false;
	bScoreUpdated = false;
	vNew = (0.0f, 0.0f);
}

void oAsteroidLarge::Initialise(const char* c_pcAsteroidLargeImageFileName)
{
	iSpriteID = UG::CreateSprite(c_pcAsteroidLargeImageFileName, (float)iWidth, (float)iHeight); //Create New Asteroid Sprite
	vNew.SetRandom(c_fSpeedMin, c_fSpeedMax);	//Set Random Movement Vector
	SetRotation(fSpriteTurnRate); //Set Asteroid Rotation
}

void oAsteroidLarge::Draw(oSpawncontroller& a_rSpawncontroller, int a_iCurrentAsteroid)
{
	bHasCollided = false; //Resets Status Variables
	bIsActive = true; //Sets Active to True
	bShattered = false;
	bScoreUpdated = false;
	pos.Set(a_rSpawncontroller.afSpawnPosArray[a_iCurrentAsteroid][0], a_rSpawncontroller.afSpawnPosArray[a_iCurrentAsteroid][1]); //Set Asteroid Position to Spawn Generated Positions
	pos.Get(fPosX, fPosY);
	UG::DrawSprite(iSpriteID); //Draw Asteroid
	UG::MoveSprite(iSpriteID, fPosX, fPosY); //Move Asteroid
}

void oAsteroidLarge::Destroy(oAsteroidLarge& a_rAsteroidLarge)
{
	a_rAsteroidLarge.bShattered = false; 
	a_rAsteroidLarge.bHasCollided = true; //Has Collided
	UG::StopDrawingSprite(a_rAsteroidLarge.iSpriteID); //Stop Drawing Asteroid
	UG::DestroySprite(a_rAsteroidLarge.iSpriteID); //Destroy Asteroid Sprite
	a_rAsteroidLarge.iSpriteID = -1; //Reset SpriteID
}

void oAsteroidLarge::ResetVars(oAsteroidLarge & a_rAsteroidLarge)
{
	a_rAsteroidLarge.fSpriteTurnRate = 0.f; //Reset Variables
	a_rAsteroidLarge.fPosX = 0.f;
	a_rAsteroidLarge.fPosY = 0.f;
	a_rAsteroidLarge.fVNewX = 0.f;
	a_rAsteroidLarge.fVNewY = 0.f;
	a_rAsteroidLarge.vNew = (0.0f, 0.0f);
	a_rAsteroidLarge.bHasCollided = false;
	a_rAsteroidLarge.bShattered = false;
	a_rAsteroidLarge.bScoreUpdated = false;
}

void oAsteroidLarge::Respawn(oAsteroidLarge& a_rAsteroidLarge,int a_iCurrentAsteroid)
{
	a_rAsteroidLarge.Initialise(c_acLargeAsteroidFileName[a_iCurrentAsteroid]); //Create New Asteroid
	a_rAsteroidLarge.bHasCollided = false;
	a_rAsteroidLarge.bIsActive = true; //Set Active
	a_rAsteroidLarge.bShattered = false;
	a_rAsteroidLarge.bScoreUpdated = false;
	a_rAsteroidLarge.pos.Set(a_rAsteroidLarge.afLargeAsteroidRespawnPosArray[a_iCurrentAsteroid][0],  //Set Asteroid Position to Spawn Generated Positions
							 a_rAsteroidLarge.afLargeAsteroidRespawnPosArray[a_iCurrentAsteroid][1]);
	UG::DrawSprite(a_rAsteroidLarge.iSpriteID); // Draw Asteroid
	UG::MoveSprite(a_rAsteroidLarge.iSpriteID, a_rAsteroidLarge.fPosX, a_rAsteroidLarge.fPosY); //Move Asteroid
}

int oAsteroidLarge::Score(oAsteroidLarge& a_rAsteroidLarge)
{
	return a_rAsteroidLarge.iScore; //Get Score
}

oAsteroidMedium::oAsteroidMedium() //On Object Creation, Initialise Variables
{
	iSpriteID = -1; 
	iScore = 50;
	iWidth = 36;
	iHeight = 36;
	iRadius = 18;
	c_fSpeedMax = 0.7f;
	c_fSpeedMin = 0.25f;
	fSpriteTurnRate = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bShattered = false;
	bIsActive = false;
	bHasCollided = false;
	bScoreUpdated = false;
	vNew = Vector(0.0f, 0.0f);
}

void oAsteroidMedium::Initialise(const char * a_rAsteroidMediumImageFileName)
{
	iSpriteID = UG::CreateSprite(a_rAsteroidMediumImageFileName, (float)iWidth, (float)iHeight); //Create New Asteroid Sprite
	vNew.SetRandom(c_fSpeedMin, c_fSpeedMax); //Set Random Velocity
	SetRotation(fSpriteTurnRate); //Set Sprite Rotation
}

void oAsteroidMedium::Draw(float a_rAsteroidLargePosX, float a_rAsteroidLargePosY)
{
	bHasCollided = false; //Set Active
	bIsActive = true;
	pos.Set(a_rAsteroidLargePosX, a_rAsteroidLargePosY);
	pos.Get(fPosX, fPosY);
	UG::DrawSprite(iSpriteID); //Draw Asteroid
	UG::MoveSprite(iSpriteID, fPosX, fPosY); //Move Asteroid
}

void oAsteroidMedium::Destroy(oAsteroidMedium& a_rAsteroidMedium)
{
	a_rAsteroidMedium.bHasCollided = true; //Asteroid Has Collided
	UG::StopDrawingSprite(a_rAsteroidMedium.iSpriteID); //Stop Drawing Asteroid
	UG::DestroySprite(a_rAsteroidMedium.iSpriteID); //Destroy Asteroid Sprite
	a_rAsteroidMedium.iSpriteID = -1; //Reset SpriteID
}

void oAsteroidMedium::ResetVars(oAsteroidMedium & a_rAsteroidMedium)
{
	a_rAsteroidMedium.fSpriteTurnRate = 0.f; //Reset Variables
	a_rAsteroidMedium.fPosX = 0.f;
	a_rAsteroidMedium.fPosY = 0.f;
	a_rAsteroidMedium.fVNewX = 0.f;
	a_rAsteroidMedium.fVNewY = 0.f;
	a_rAsteroidMedium.vNew = (0.0f, 0.0f);
	a_rAsteroidMedium.bHasCollided = false;
	a_rAsteroidMedium.bShattered = false;
	a_rAsteroidMedium.bScoreUpdated = false;
}

int oAsteroidMedium::Score(oAsteroidMedium& a_rAsteroidMedium)
{
	return a_rAsteroidMedium.iScore; // Get Score
}

oAsteroidSmall::oAsteroidSmall() //On Object Creation, Initialise Variables
{
	iSpriteID = -1;
	iScore = 100;
	iWidth = 18;
	iHeight = 18;
	iRadius = 9;
	c_fSpeedMax = 0.8f;
	c_fSpeedMin = 0.35f;
	fSpriteTurnRate = 0.f;
	fPosX = 0.f;
	fPosY = 0.f;
	fVNewX = 0.f;
	fVNewY = 0.f;
	bShattered = false;
	bHasCollided = false;
	bIsActive = false;
	bScoreUpdated = false; 
	vNew = (0.0f, 0.0f);
}

void oAsteroidSmall::Initialise(const char * c_pcAsteroidSmallImageFileName)
{
	iSpriteID = UG::CreateSprite(c_pcAsteroidSmallImageFileName, (float)iWidth, (float)iHeight);  //Create New Asteroid Sprite
	vNew.SetRandom(c_fSpeedMin, c_fSpeedMax); //Set Random Velocity
	SetRotation(fSpriteTurnRate); //Set Sprite Rotation
}

void oAsteroidSmall::Draw(float a_rAsteroidMediumPosX, float a_rAsteroidMediumPosY)
{
	bHasCollided = false;
	bIsActive = true; //Set Active
	pos.Set(a_rAsteroidMediumPosX, a_rAsteroidMediumPosY);
	pos.Get(fPosX, fPosY);
	UG::DrawSprite(iSpriteID); //Draw Asteroid
	UG::MoveSprite(iSpriteID, fPosX, fPosY); //Move Asteroid
}

void oAsteroidSmall::Destroy(oAsteroidSmall& a_rAsteroidSmall)
{
	a_rAsteroidSmall.bHasCollided = true; // Asteroid Has Collided
	UG::StopDrawingSprite(a_rAsteroidSmall.iSpriteID); //Stop Drawing Asteroid
	UG::DestroySprite(a_rAsteroidSmall.iSpriteID); //Destroy Asteroid Sprite
	a_rAsteroidSmall.iSpriteID = -1; //Reset SpriteID
}

void oAsteroidSmall::ResetVars(oAsteroidSmall & a_rAsteroidSmall)
{
	a_rAsteroidSmall.fSpriteTurnRate = 0.f; //Reset Variables
	a_rAsteroidSmall.fPosX = 0.f;
	a_rAsteroidSmall.fPosY = 0.f;
	a_rAsteroidSmall.fVNewX = 0.f;
	a_rAsteroidSmall.fVNewY = 0.f;
	a_rAsteroidSmall.vNew = (0.0f, 0.0f);
	a_rAsteroidSmall.bHasCollided = false;
	a_rAsteroidSmall.bShattered = false;
	a_rAsteroidSmall.bScoreUpdated = false;
}

int oAsteroidSmall::Score(oAsteroidSmall & a_rAsteroidSmall)
{
	return a_rAsteroidSmall.iScore; //Get Score
}
