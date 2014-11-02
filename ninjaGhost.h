// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.h v1.0

#ifndef _THREECS_H              // Prevent multiple definitions if this 
#define _THREECS_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "entity.h"

class NinjaGhost : public Game
{
private:
	// game items
	// game variables

	//STATE STUFF
	GameStates gameState;
	float timeInState;
	void gameStateUpdate();

public:
	NinjaGhost();
	virtual ~NinjaGhost();
	void initialize(HWND hwnd);
	void reset();
	void update();
	void ai() {};
	void collisions() {};
	void render();
	void releaseAll();
	void resetAll();
};

#endif
