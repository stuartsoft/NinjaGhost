#include "katana.h"


Katana::Katana() : Entity()
{
	spriteData.width = katanaNS::WIDTH;           // size of Ship1
	spriteData.height = katanaNS::HEIGHT;
	spriteData.rect.bottom = katanaNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = katanaNS::WIDTH;
	spriteData.scale = katanaNS::SCALE;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = (katanaNS::WIDTH + katanaNS::HEIGHT)/4.0;

	edge.top = -katanaNS::HEIGHT/2;
	edge.bottom = katanaNS::HEIGHT/2;
	edge.left = -katanaNS::WIDTH/2;
	edge.right = katanaNS::WIDTH/2;

	collisionType = entityNS::ROTATED_BOX;
	active = false;
}


void Katana::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
    spriteData.y += frameTime * velocity.y;
	setDegrees(getDegrees() + katanaNS::ROTATION_RATE);
	
}