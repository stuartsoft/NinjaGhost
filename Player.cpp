#include "player.h"

Player::Player(){
	spriteData.width = Playerns::WIDTH;           // size of Ship1
	spriteData.height = Playerns::HEIGHT;
	spriteData.x = Playerns::X;                   // location on screen
	spriteData.y = Playerns::Y;
	spriteData.rect.bottom = Playerns::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = Playerns::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = Playerns::WIDTH/2.0;
	mass = Playerns::MASS;
	collisionType = entityNS::CIRCLE;
	setHealth(Playerns::MAX_HEALTH);
	health = Playerns::MAX_HEALTH;
}

void Player::draw()
{
	Image::draw();              // draw Player
}

void Player::update(float frameTime){
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y

	D3DXVECTOR2 inputDir(0,0);
	if (input->isKeyDown(0x41))//left
		inputDir.x = -1;
	else if (input->isKeyDown(0x44))//right
		inputDir.x = 1;

	if (input->isKeyDown(VK_SPACE) && velocity.y ==0)//up
		inputDir.y = -1;

	D3DXVec2Normalize(&inputDir,&inputDir);
	inputDir.x *= 5;
	inputDir.y *= 5;

	if (inputDir.y !=0)
		velocity.y = inputDir.y*250;

	//speed cap
	if(velocity.x> Playerns::MAX_SPEED_X)
		velocity.x = Playerns::MAX_SPEED_X;
	else if (velocity.x < -Playerns::MAX_SPEED_X)
		velocity.x = -Playerns::MAX_SPEED_X;
	//if (velocity.y>Playerns::MAX_SPEED_Y)
	//	velocity.y = Playerns::MAX_SPEED_Y;
	//else if (velocity.y <-Playerns::MAX_SPEED_Y)
	//	velocity.y = -Playerns::MAX_SPEED_Y;

	//x acceleration
	if (inputDir.x!=0)
		deltaV.x = inputDir.x;
	else if (velocity.x < 2.5 && velocity.x > -2.5 && inputDir.x ==0){
		velocity.x = 0;
		deltaV.x = 0;
	}
	else if (inputDir.x ==0 && velocity.x > 0)
		deltaV.x-=1.5;
	else if(inputDir.x ==0 && velocity.x < 0)
		deltaV.x+=2.5;

	//acceleration of gravity
	deltaV.y = 9.8;
	

	if (spriteData.x + 2*radius*getScale()< 0)	//left edge
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