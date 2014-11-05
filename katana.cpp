#include "katana.h"


Katana::Katana() : Entity()
{
	spriteData.width = katanaNS::WIDTH;           // size of Ship1
	spriteData.height = katanaNS::HEIGHT;
	spriteData.rect.bottom = katanaNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = katanaNS::WIDTH;
	spriteData.scale = katanaNS::SCALE;

	spriteData.x = 0;
	spriteData.y = 0;

	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = (katanaNS::WIDTH + katanaNS::HEIGHT)/4.0;

	edge.top = -katanaNS::HEIGHT/2;
	edge.bottom = katanaNS::HEIGHT/2;
	edge.left = 0;
	edge.right = katanaNS::WIDTH/2;

	collisionType = entityNS::ROTATED_BOX;
	active = false;
}


void Katana::update(float frameTime)
{
	Entity::update(frameTime);

	if(!active && input->isKeyDown(ATTACK_KEY))
	{
		setActive(true);
		setDegrees(-75);
	}
	if(active)
	{
		setX(player->getCenterX()-katanaNS::WIDTH*katanaNS::SCALE/2); //+Playerns::WIDTH/2);
		setY(player->getCenterY());
		setDegrees(getDegrees() + frameTime*katanaNS::ROTATION_RATE);
		if(getDegrees() >= 75)
		{
			setActive(false);
		}
	}

//	spriteData.x += frameTime * velocity.x;
//  spriteData.y += frameTime * velocity.y;
	
}