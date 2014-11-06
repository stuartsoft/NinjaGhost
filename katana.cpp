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

	player = nullptr;
	swingAngle = 0;
}


void Katana::update(float frameTime)
{
	Entity::update(frameTime);

	if(!active && input->getMouseLButton())
	{
		setActive(true);
		swingAngle = katanaNS::SWING_START;
		setDegrees(swingAngle);
	}
	if(active)
	{
		swingAngle += frameTime*katanaNS::ROTATION_RATE;
		if(player->FacingDir() == right)
		{
			setCurrentFrame(0);
			setX(player->getCenterX()+Playerns::WIDTH/2-katanaNS::WIDTH*katanaNS::SCALE/2); //+Playerns::WIDTH/2);
			setY(player->getCenterY());
			setDegrees(swingAngle);
			if(getDegrees() >= katanaNS::SWING_END)
			{
				setActive(false);
			}
		}
		if(player->FacingDir() == left)
		{
			setCurrentFrame(1);
			setX(player->getCenterX()-Playerns::WIDTH/2-katanaNS::WIDTH*katanaNS::SCALE/2); //+Playerns::WIDTH/2);
			setY(player->getCenterY());
			setDegrees(-swingAngle);
			if(getDegrees() <= -katanaNS::SWING_END)
			{
				setActive(false);
			}
		}
	}
	
}