// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Three Cs DX constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "ThreeCsDX";
const char GAME_TITLE[] = "Three Cs DirectX";
const bool FULLSCREEN = false;          // windowed or fullscreen
const UINT GAME_WIDTH = 1152;			// width of game in pixels
const UINT GAME_HEIGHT = 720;			// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

const int MAX_SHURIKEN = 10;

// audio files
const char WAVE_BANK[] = "";
const char SOUND_BANK[] = "";

// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = VK_OEM_3;    // `~ key for U.S.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key


// splash screen images
const char MAIN_MENU_IMAGE[] = "images\\menu.jpg";
const char SPLASH1_IMAGE[] = "images\\menu.jpg";
const char SPLASH2_IMAGE[] = "images\\menu.jpg";

// States
enum GameStates {MAIN_MENU, INTRO1, LEVEL1, INTRO2, LEVEL2, GAME_OVER};

// Pattern Step Actions
enum PATTERN_STEP_ACTION {NONE, LEFT, RIGHT};


#endif
