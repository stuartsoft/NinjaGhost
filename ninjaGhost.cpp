// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.cpp v1.0

#include "ninjaGhost.h"

//=============================================================================
// Constructor
//=============================================================================
NinjaGhost::NinjaGhost()
{
	
}

//=============================================================================
// Destructor
//=============================================================================
NinjaGhost::~NinjaGhost()
{
	releaseAll();               // call deviceLost() for every graphics item
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void NinjaGhost::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	return;
}


//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void NinjaGhost::reset()
{
	return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void NinjaGhost::update()
{

}

//=============================================================================
// render game items
//=============================================================================
void NinjaGhost::render()
{
	graphics->spriteBegin();
	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void NinjaGhost::releaseAll()
{
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void NinjaGhost::resetAll()
{
	Game::resetAll();
	return;
}
