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
	playerdir = right;
	floatoffset = 0.0;
	floatdir = down;
}

void Player::draw()
{
	if (velocity.y <0.001 && velocity.y > -0.001)
		spriteData.y+=floatoffset;
	Image::draw();              // draw Player
	if (velocity.y <0.001 && velocity.y > -0.001)
		spriteData.y-=floatoffset;
}

direction Player::FacingDir(){
	return playerdir;
}

float Player::getfloatoffset(){
	return floatoffset;
}

void Player::update(float frameTime, Platform platforms[]){
	D3DXVECTOR2 inputDir(0,0);
	if (input->isKeyDown(0x41)){//left
		inputDir.x = -1;
		setFrames(4,7);
		if(playerdir!=left){
			playerdir = left;
			setCurrentFrame(4);
		}
		//setCurrentFrame(4);
	}
	else if (input->isKeyDown(0x44)){//right
		inputDir.x = 1;
		setFrames(0,3);
		if(playerdir != right){
			playerdir = right;
			setCurrentFrame(0);
		}
		//setCurrentFrame(0);
	}

		//acceleration of gravity
	deltaV.y = 2000*(frameTime);
	//while falling and pressing space, replace gravitational acceleration with static velocity
	if (velocity.y > 200  && input->isKeyDown(VK_SPACE)){
		deltaV.y = 0.0;
		velocity.y = 200;
	}

	BOOL StandingOnPlatform = FALSE;
	for (int i=0;i<NUM_PLATFORMS;i++){
		if (platforms[i].getY() == getY() + getHeight()*getScale()){
			if(getX() < platforms[i].getX()+platforms[i].getWidth()*platforms[i].getScale() && getX()+getWidth()*getScale() > platforms[i].getX()){
				deltaV.y = 0;
				velocity.y = 0;
				StandingOnPlatform = TRUE;
				break;
			}
		}
	}

	if (input->isKeyDown(VK_SPACE) && StandingOnPlatform)//up
		inputDir.y = -1;

	//D3DXVec2Normalize(&inputDir,&inputDir);
	inputDir.x *= 5;
	inputDir.y *= 5;

	if (inputDir.y !=0)
		velocity.y = inputDir.y*215;

	//speed cap
	if(velocity.x> Playerns::MAX_SPEED_X)
		velocity.x = Playerns::MAX_SPEED_X;
	else if (velocity.x < -Playerns::MAX_SPEED_X)
		velocity.x = -Playerns::MAX_SPEED_X;

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

	//====================Floating animation
	if (floatdir == up)
		floatoffset -= 20*frameTime;
	else
		floatoffset += 20*frameTime;

	if (floatoffset > 10 && floatdir ==down)
		floatdir = up;
	else if (floatoffset < -10 && floatdir == up)
		floatdir = down;

	//====================Edge wrapping

	if (spriteData.x + 2*radius*getScale() < 0)	//left edge
		spriteData.x = GAME_WIDTH;
	else if (spriteData.x > GAME_WIDTH)			//right edge
		spriteData.x = -2*radius*getScale();


	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;							// move ship along X 
	spriteData.y += frameTime * velocity.y;						   // move ship along Y
}