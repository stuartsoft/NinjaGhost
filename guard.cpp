#include "guard.h"

Guard::Guard(){
	spriteData.width = guardNS::WIDTH;           // size of Ship1
	spriteData.height = guardNS::HEIGHT;
	spriteData.x = guardNS::X;                   // location on screen
	spriteData.y = guardNS::Y;
	spriteData.rect.bottom = guardNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = guardNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = guardNS::WIDTH/2.0;
	mass = guardNS::MASS;
	collisionType = entityNS::CIRCLE;
	setHealth(guardNS::MAX_HEALTH);
	health = guardNS::MAX_HEALTH;
	facingdir = right;
}

void Guard::draw()
{
	Image::draw();
}

direction Guard::FacingDir(){
	return facingdir;
}

void Guard::update(float frameTime){
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;							// move ship along X 
	spriteData.y += frameTime * velocity.y;						   // move ship along Y
	
	setFrameDelay(0.25);

	
	//speed cap
	if(velocity.x > guardNS::MAX_SPEED_X)
		velocity.x = guardNS::MAX_SPEED_X;
	else if (velocity.x < -guardNS::MAX_SPEED_X)
		velocity.x = -guardNS::MAX_SPEED_X;

	//acceleration of gravity
	deltaV.y = 2000*(frameTime);

	if (spriteData.x + 2*radius*getScale() < 0)	//left edge
		spriteData.x = GAME_WIDTH;
	else if (spriteData.x > GAME_WIDTH)			//right edge
		spriteData.x = -2*radius*getScale();

	if (spriteData.y > GAME_HEIGHT - getHeight()*getScale()){
		spriteData.y = GAME_HEIGHT - getHeight()*getScale();
		deltaV.y = 0;
		//velocity.y = -velocity.y/2;
		velocity.y = 0;
	}	
	//setRadians(getRadians()+0.01);
}