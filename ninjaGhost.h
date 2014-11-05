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
#include "Player.h"
#include "menu.h"
#include "katana.h"
#include "shuriken.h"

class NinjaGhost : public Game
{
private:
	// game items
	// game variables
	Player player;
	TextureManager PlayerTextureManager;

	TextureManager KatanaTM;
	TextureManager ShurikenTM;
	

	Katana katana;
	Shuriken shuriken[MAX_SHURIKEN];

	// MENU/SPLASH STUFF
	Menu *mainMenu;

	TextureManager MainMenuSplashTM;
	Image MainMenuSplash;
	TextureManager Level1SplashTM;
	Image Level1Splash;
	TextureManager Level2SplashTM;
	Image Level2Splash;
	
	// STATE STUFF
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
