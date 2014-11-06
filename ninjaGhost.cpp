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

	if(!PlayerTextureManager.initialize(graphics, "images\\player.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player texture"));
	if(!player.initialize(this, Playerns::WIDTH, Playerns::HEIGHT, 2, &PlayerTextureManager))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player texture"));
	
	player.setFrames(0,3);
	player.setCurrentFrame(0);
	player.setFrameDelay(0.25);
	
	if(!KatanaTM.initialize(graphics, KATANA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init katana texture"));
	if(!katana.initialize(this, katanaNS::WIDTH, katanaNS::HEIGHT, 0, &KatanaTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init katana"));
	katana.setActive(false);
	katana.setPlayer(&player);

	if(!ShurikenTM.initialize(graphics, SHURIKEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init shuriken texture"));
	for(int i=0; i<MAX_SHURIKEN; i++)
	{
		if(!shuriken[i].initialize(this, shurikenNS::WIDTH, shurikenNS::HEIGHT, 0, &ShurikenTM))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init shuriken"));
	}

	player.setScale(2.0);

	// splash screen init
	if(!MainMenuSplashTM.initialize(graphics, MAIN_MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init menu splash texture"));
	if(!MainMenuSplash.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &MainMenuSplashTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init menu splash image"));
	MainMenuSplash.setX(0);
	MainMenuSplash.setY(0);

	if(!Level1SplashTM.initialize(graphics, SPLASH1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level1 splash texture"));
	if(!Level1Splash.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &Level1SplashTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level1 splash image"));
	Level1Splash.setX(0);
	Level1Splash.setY(0);

	if(!Level2SplashTM.initialize(graphics, SPLASH2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level2 splash texture"));
	if(!Level2Splash.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &Level2SplashTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level2 splash image"));
	Level2Splash.setX(0);
	Level2Splash.setY(0);


	// menu init
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	// state init
	timeInState = 0;
	gameState = MAIN_MENU;

	//var init
	timeSinceThrow = 0;

	return;
}


//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void NinjaGhost::reset()
{
	return;
}



//===============================
// update game state information
//===============================
void NinjaGhost::gameStateUpdate()
{
	timeInState += frameTime;
	if(gameState == MAIN_MENU && input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 0)
	{
		gameState = INTRO1;
		timeInState = 0;
	}
	if(gameState == INTRO1 && timeInState > 1.0)
	{
		gameState = LEVEL1;
		timeInState = 0;
	}
}
//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void NinjaGhost::update()
{
	
	gameStateUpdate();
	if(input->isKeyDown(ESC_KEY))
	{
		exitGame();
	}

	switch(gameState)
	{
	case MAIN_MENU:
		mainMenu->update();
		if(input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 3)
		{
			exitGame();
		}
		break;
	case LEVEL1:
		player.update(frameTime);
		katana.update(frameTime);
		timeSinceThrow += frameTime;
		if(timeSinceThrow >= 100)
			timeSinceThrow = 30;
		if(timeSinceThrow >= THROW_COOLDOWN && input->getMouseRButton())
		{
			VECTOR2 pos = VECTOR2(player.getCenterX(),player.getCenterY());
			VECTOR2 dir = VECTOR2(input->getMouseX(),input->getMouseY()) - pos;
			dir *= shurikenNS::SPEED/GAME_WIDTH;
			spawnShuriken(pos, dir);
			timeSinceThrow = 0;
		}
		for(int i=0; i<MAX_SHURIKEN; i++)
		{
			if(shuriken[i].getActive())
			{
				shuriken[i].update(frameTime);
			}
		}
	}
	

}

//=============================================================================
// render game items
//=============================================================================
void NinjaGhost::render()
{
	graphics->spriteBegin();
	

	switch(gameState)
	{
	case MAIN_MENU:
		MainMenuSplash.draw();
		mainMenu->displayMenu();
		break;
	case INTRO1:
		Level1Splash.draw();
		break;
	case LEVEL1:
		player.draw();
		if(katana.getActive())
		{
			katana.draw();
		}
		for(int i=0; i<MAX_SHURIKEN; i++)
		{
			if(shuriken[i].getActive())
			{
				shuriken[i].draw();
			}
		}
		break;
	
	}
	
	graphics->spriteEnd();
}


//
// grab a throwing star and activate it at given position
//
void NinjaGhost::spawnShuriken(VECTOR2 pos, VECTOR2 vel)
{
	Shuriken* first = nullptr;
	for(int i=0; i<MAX_SHURIKEN; i++)
	{
		if(!(shuriken[i].getActive()))
		{
			first = &shuriken[i];
			break;
		}
	}
	if(first != nullptr)
	{
		first->setActive(true);
		first->setVelocity(vel);
		first->setX(pos.x);
		first->setY(pos.y);
	}
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void NinjaGhost::releaseAll()
{
	KatanaTM.onLostDevice();
	ShurikenTM.onLostDevice();
	PlayerTextureManager.onLostDevice();
	MainMenuSplashTM.onLostDevice();
	Level1SplashTM.onLostDevice();
	Level2SplashTM.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void NinjaGhost::resetAll()
{
	KatanaTM.onResetDevice();
	ShurikenTM.onResetDevice();
	PlayerTextureManager.onResetDevice();
	MainMenuSplashTM.onResetDevice();
	Level1SplashTM.onResetDevice();
	Level2SplashTM.onResetDevice();
	Game::resetAll();
	return;
}
