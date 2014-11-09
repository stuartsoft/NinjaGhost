#ifndef _GUARD_H
#define _GUARD_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "platform.h"

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
	const float SCALE = 1.0;

	const int GUN_WIDTH = 128;
	const int GUN_HEIGHT = 32;
	const float GUN_SCALE = 1.0;

	const float PATROL_PERCENT = .8;

	const float FLEE_DIST = GAME_WIDTH/5;
	const float ATTACK_DIST = GAME_WIDTH/2;
}

class Guard: public Entity{
private:
	direction facingDir;
	direction patrolDir;

	int patrolAnchor;
	int patrolWidth;
	Platform* patrolPlatform;
	
	Entity* target;
	float dist;

	Image gun;

public:
	Guard();
	direction FacingDir();
	void Guard::draw();
	void Guard::update(float frameTime, int yOffset);
	void Guard::ai();

	void gunInit(TextureManager* gunTM);
	void setTarget();
	void initializePatrol(Platform* plat, Entity* t);
};

#endif