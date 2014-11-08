#ifndef _GUARD_H
#define _GUARD_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

namespace guardNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 128;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float MASS = 300.0f;              // mass
	const float MAX_HEALTH = 4.0f;
	const int SPEED = 300;
	const int MAX_SPEED_X = 750;
	const int MAX_SPEED_Y = 1000;
}

class Guard: public Entity{
private:
	direction facingdir;

	int patrolAnchor;
	int patrolWidth;
	int patrolPos;

public:
	Guard();
	direction FacingDir();
	void Guard::draw();
	void Guard::update(float frameTime);

	void initializePatrol(int pAnchor, int pWidth);
};

#endif