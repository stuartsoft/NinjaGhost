#ifndef _PLAYER_H
#define _PLAYER_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

namespace Playerns{
    const int WIDTH =128;                   // image width
    const int HEIGHT = 128;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float MASS = 300.0f;              // mass
	const float MAX_HEALTH = 4.0f;
	const int MAX_SPEED_X =750;
	const int MAX_SPEED_Y = 1000;
}

enum direction {left , right};

class Player: public Entity{
private:
	direction playerdir;
public:
	Player();
	direction FacingDir();
	void Player::draw();
	void Player::update(float frameTime);
};

#endif