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
	gameOverFont1 = new TextDX;
	gameOverFont2 = new TextDX;
	gameCompleteFont1 = new TextDX;
	gameCompleteFont2 = new TextDX;
}

//=============================================================================
// Destructor
//=============================================================================
NinjaGhost::~NinjaGhost()
{
	releaseAll();               // call deviceLost() for every graphics item
	SAFE_DELETE(gameOverFont1);
	SAFE_DELETE(gameOverFont2);
	SAFE_DELETE(gameCompleteFont1);
	SAFE_DELETE(gameCompleteFont2);
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void NinjaGhost::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	graphics->setBackColor(0x000000);
	if(!PlayerTextureManager.initialize(graphics, "images\\PlayerB.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player texture"));
	if(!player.initialize(this, Playerns::WIDTH, Playerns::HEIGHT, 2, &PlayerTextureManager))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player"));

	player.setFrames(0,3);
	player.setCurrentFrame(0);
	player.setFrameDelay(0.33);

	if(!PlatformTM.initialize(graphics, "images\\platform.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init platform texture"));
	
	for (int i=0;i<NUM_PLATFORMS;i++){
		if(!platforms[i].initialize(this, Platformns::WIDTH, Platformns::HEIGHT, 0, &PlatformTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error init platform"));
	}

	platforms[0].setY(GAME_HEIGHT-250);
	platforms[1].setY(GAME_HEIGHT-50);
	platforms[1].setX(0);
	platforms[2].setY(GAME_HEIGHT-50);
	platforms[3].setY(GAME_HEIGHT-50);
	platforms[3].setX(GAME_WIDTH-platforms[3].getWidth()*platforms[3].getScale());

	if(!GuardTM.initialize(graphics, "images\\guard.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init guard texture"));
	if(!testDummy.initialize(this, guardNS::WIDTH, guardNS::HEIGHT, 2, &GuardTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init guard"));
	testDummy.setX(3*GAME_WIDTH/4);
	testDummy.setY(GAME_HEIGHT/2);
	
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

	//player.setScale(2.0);

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


	if(gameOverFont1->initialize(graphics, 72, true, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover font"));
	if(gameOverFont2->initialize(graphics, 36, false, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover font"));
	gameOverFont1->setFontColor(graphicsNS::RED);
	gameOverFont2->setFontColor(graphicsNS::RED);

	if(gameCompleteFont1->initialize(graphics, 72, true, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gamecomplete font"));
	if(gameCompleteFont2->initialize(graphics, 36, false, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gamecomplete font"));
	gameCompleteFont1->setFontColor(graphicsNS::BLACK);
	gameCompleteFont2->setFontColor(graphicsNS::BLACK);


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


//=================================
// initialize game items for level1
//=================================
void NinjaGhost::LoadLevel1()
{
	testDummy.initializePatrol(3*GAME_WIDTH/4, GAME_WIDTH/5);
}


//===============================
// update game state information
//===============================
void NinjaGhost::gameStateUpdate()
{
	timeInState += frameTime;
	if(gameState == MAIN_MENU && timeInState >= 1 && input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 0)
	{
		gameState = INTRO1;
		timeInState = 0;
	}
	if(gameState == INTRO1 && timeInState > 1.0)
	{
		gameState = LEVEL1;
		timeInState = 0;
		LoadLevel1();
	}
	if(gameState == GAME_OVER && input->isKeyDown(ENTER_KEY))
	{
		gameState = MAIN_MENU;
		timeInState = 0;
	}
	if(gameState == GAME_COMPLETE && input->isKeyDown(ENTER_KEY))
	{
		gameState = MAIN_MENU;
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

		if(input->isKeyDown(ENTER_KEY))
			testDummy.setActive(true);
		testDummy.update(frameTime);

		player.update(frameTime, platforms);
		katana.update(frameTime);
		timeSinceThrow += frameTime;
		if(timeSinceThrow >= 100)
			timeSinceThrow = 30;
		if(timeSinceThrow >= THROW_COOLDOWN && input->getMouseRButton())
		{
			VECTOR2 pos = VECTOR2(player.getCenterX(),player.getCenterY());
			VECTOR2 dir = VECTOR2(input->getMouseX(),input->getMouseY()) - pos;
			VECTOR2 normdir;
			D3DXVec2Normalize(&normdir,&dir);
			normdir *= min(D3DXVec2Length(&dir)*shurikenNS::SPEED/GAME_WIDTH,shurikenNS::MAX_SPEED);
			spawnShuriken(pos, normdir);
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
		
		if(testDummy.getActive())
			testDummy.draw();

		for (int i=0;i<NUM_PLATFORMS;i++)
			platforms[i].draw();
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
	case GAME_OVER:
		graphics->setBackColor(graphicsNS::BLACK);
		gameOverFont1->print("Game Over...",GAME_WIDTH/3,GAME_HEIGHT/3);
		gameOverFont2->print("Press Enter to return to main menu",GAME_WIDTH/4,2*GAME_HEIGHT/3);
		break;
	case GAME_COMPLETE:
		graphics->setBackColor(graphicsNS::WHITE);
		gameCompleteFont1->print("Victory is yours!",GAME_WIDTH/3,GAME_HEIGHT/3);
		gameCompleteFont2->print("Press Enter to return to main menu",GAME_WIDTH/3,2*GAME_HEIGHT/3);
		break;
	}
	
	graphics->spriteEnd();
}

//==================================================================
// Handle collision between entities
//==================================================================
void NinjaGhost::collisions()
{
	if(gameState == LEVEL1 || gameState == LEVEL2)
	{

		collisionVec = VECTOR2(0,0);
	
		for (int i=0;i<NUM_PLATFORMS;i++){
			if(player.collidesWith(platforms[i], collisionVec)){
				if (player.getVelocity().y >0){
					if (player.getY()+player.getHeight()*player.getScale() < platforms[i].getY()+platforms[i].getHeight()*platforms[i].getScale()){
						player.setY(platforms[i].getY()-player.getHeight()*player.getScale());
						VECTOR2 tempv = player.getVelocity();
						tempv.y = 0;
						player.setVelocity(tempv);
					}
				}
			}
		}

		if(katana.getActive() && katana.collidesWith(testDummy,collisionVec))
		{
			testDummy.setActive(false);
		}
		for(int i=0; i<MAX_SHURIKEN; i++)
		{
			if(shuriken[i].getActive() && shuriken[i].collidesWith(testDummy,collisionVec))
			{
				testDummy.setActive(false);
				shuriken[i].setActive(false);
			}
		}
		if(player.collidesWith(testDummy,collisionVec))
		{
			gameState = GAME_OVER;
			timeInState = 0;
		}
	}
}

//==================================================================
// grab a throwing star and activate it w/ given position & velocity
//==================================================================
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
	gameOverFont1->onLostDevice();
	gameOverFont2->onLostDevice();
	gameCompleteFont1->onLostDevice();
	gameCompleteFont2->onLostDevice();
	GuardTM.onLostDevice();
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
	gameOverFont1->onResetDevice();
	gameOverFont2->onResetDevice();
	gameCompleteFont1->onResetDevice();
	gameCompleteFont2->onResetDevice();
	GuardTM.onResetDevice();
	KatanaTM.onResetDevice();
	ShurikenTM.onResetDevice();
	PlayerTextureManager.onResetDevice();
	MainMenuSplashTM.onResetDevice();
	Level1SplashTM.onResetDevice();
	Level2SplashTM.onResetDevice();
	Game::resetAll();
	return;
}
