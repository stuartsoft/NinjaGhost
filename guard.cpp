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
	facingDir = right;
	patrolDir = right;

	edge.left = -guardNS::WIDTH/2;
	edge.right = guardNS::WIDTH/2;
	edge.top = -guardNS::HEIGHT/2;
	edge.bottom = guardNS::HEIGHT/2;

	dist = 0;
}

void Guard::gunInit(TextureManager* gunTM)
{
	if(!gun.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, gunTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level2 splash image"));
}

void Guard::draw()
{
	Image::draw();
	gun.draw();
}

direction Guard::FacingDir()
{
	return facingDir;
}

void Guard::initializePatrol(Platform* plat, Entity* t)
{
	patrolPlatform = plat;
	patrolAnchor = patrolPlatform->getCenterX();
	patrolWidth = Platformns::WIDTH/2 * guardNS::PATROL_PERCENT;
	spriteData.y = patrolPlatform->getY()-guardNS::HEIGHT*guardNS::SCALE;
	spriteData.x = patrolAnchor;

	target = t;
}

void Guard::update(float frameTime, int yOffset){
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += yOffset;

	setFrameDelay(0.25);

	if(facingDir == right)
	{
		gun.setCurrentFrame(0);
		gun.setX(getCenterX()+getScale()*guardNS::WIDTH/4-guardNS::GUN_WIDTH*guardNS::GUN_SCALE/2);
		gun.setY(getCenterY());
		setDegrees(0);
	}
	if(facingDir == left)
	{
		gun.setCurrentFrame(1);
		gun.setX(getCenterX()-getScale()*guardNS::WIDTH/4-guardNS::WIDTH*guardNS::GUN_SCALE/2);
		gun.setY(getCenterY());
		setDegrees(0);
	}

	if(patrolDir == left)
	{
		velocity.x = -guardNS::SPEED;
		facingDir = left;
	}
	else if(patrolDir == right)
	{
		velocity.x = guardNS::SPEED;
		facingDir = right;
	}
	if(spriteData.x >= patrolAnchor + patrolWidth)
	{
		patrolDir = left;
	}
	else if(spriteData.x <= patrolAnchor - patrolWidth)
	{
		patrolDir = right;
	}

	if (spriteData.x + 2*radius*getScale() < 0)	//left edge
		spriteData.x = GAME_WIDTH;
	else if (spriteData.x > GAME_WIDTH)			//right edge
		spriteData.x = -2*radius*getScale();
	
}

void Guard::ai()
{
	dist = D3DXVec2LengthSq(&(VECTOR2(target->getX(),target->getY()) - VECTOR2(spriteData.x,spriteData.y)));
	
	if(dist < guardNS::FLEE_DIST)				//FLEE
	{
		if((spriteData.x-target->getX()) > 0)
		{
			velocity.x = guardNS::SPEED;
			facingDir = right;
		}
		else
		{
			velocity.x = -guardNS::SPEED;
			facingDir = left;
		}
	}
	else if(dist < guardNS::ATTACK_DIST)		//ATTACK
	{
		if((spriteData.x-target->getX()) > 0)
		{
			velocity.x = -guardNS::SPEED;
			facingDir = left;
		}
		else
		{
			velocity.x = guardNS::SPEED;
			facingDir = right;
		}
	}
	else										//PATROL
	{
		
	}
}