#ifndef _KATANA_H                 // Prevent multiple definitions if this 
#define _KATANA_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace katanaNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const float ROTATION_RATE = 10.0;  // radians per second
	const float SPEED = 300;                // 10 pixels per second
	const float MASS = 300.0f;              // mass
	const float SCALE = 0.8;
	
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   POWER_START_FRAME = 0;      // sword starts at frame 0
	const int   POWER_END_FRAME = 0;         // sword animation frames 0
}

class Katana : public Entity
{
public:
    // constructor
    Katana();

    // inherited member functions
    void update(float frameTime);

private:
};

#endif