#include "guard.h"

Guard::Guard()
{
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
	collisionType = entityNS::BOX;
	setHealth(guardNS::MAX_HEALTH);
	health = guardNS::MAX_HEALTH;
	facingDir = right;
	patrolDir = right;

	edge.left = -guardNS::WIDTH/2;
	edge.right = guardNS::WIDTH/2;
	edge.top = -guardNS::HEIGHT/2;
	edge.bottom = guardNS::HEIGHT/2;

	dist = 0;
	target = nullptr;
	targetAquired = false;
}

void Guard::gunInit(TextureManager* gunTM)
{
	if(!gun.initialize(graphics, gunNS::WIDTH, gunNS::HEIGHT, 0, gunTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init gun image"));
}

void Guard::bulletsInit(TextureManager* bulletTM, Game* g)
{
	for(int i=0; i<BULLETS_PER_GUARD; i++)
	{
		if(!bullets[i].initialize(g, bulletNS::WIDTH, bulletNS::HEIGHT, 0, bulletTM))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init bullets"));
	}
}

void Guard::draw()
{
	if(active)
	{
		Image::draw();
		gun.draw();
	}
	for(int i=0; i<BULLETS_PER_GUARD; i++)
	{
		if(bullets[i].getActive())
		{
			bullets[i].draw();
		}
	}
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

void Guard::update(float frameTime){
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	if(spriteData.x >= patrolAnchor + Platformns::WIDTH/2)
	{
		spriteData.x = patrolAnchor + Platformns::WIDTH/2;
	}
	else if(spriteData.x <= patrolAnchor - Platformns::WIDTH/2)
	{
		spriteData.x = patrolAnchor - Platformns::WIDTH/2;
	}

	setFrameDelay(0.25);

	if(facingDir == right)
	{
		gun.setCurrentFrame(0);
		gun.setX(getCenterX()+getScale()*guardNS::WIDTH/4-gunNS::WIDTH*gunNS::SCALE/2);
		gun.setY(getCenterY());
		setRadians(0);
	}
	if(facingDir == left)
	{
		gun.setCurrentFrame(1);
		gun.setX(getCenterX()-getScale()*guardNS::WIDTH/4-gunNS::WIDTH*gunNS::SCALE/2);
		gun.setY(getCenterY());
		setRadians(0);
	}
}

void Guard::ai()
{
	distVec = VECTOR2(target->getCenterX(),target->getCenterY()) - VECTOR2(getCenterX(),getCenterY());
	dist = D3DXVec2Length(&distVec);

	if(dist < guardNS::FLEE_DIST)				//FLEE
	{
		if((spriteData.x-target->getX()) > 0)
		{
			velocity.x = guardNS::FLEE_SPEED;
			facingDir = right;
		}
		else
		{
			velocity.x = -guardNS::FLEE_SPEED;
			facingDir = left;
		}
	}
	else if(dist < guardNS::ATTACK_DIST)		//ATTACK
	{
		velocity.x = 0;
	}
	else 										//PATROL
	{
		if(patrolDir == left)
		{
			velocity.x = -guardNS::SPEED;
			facingDir = left;
			if(spriteData.x <= patrolAnchor - patrolWidth)
			{
				patrolDir = right;
			}
		}
		else if(patrolDir == right)
		{
			velocity.x = guardNS::SPEED;
			facingDir = right;
			if(spriteData.x >= patrolAnchor + patrolWidth)
			{
				patrolDir = left;
			}
		}
	}
}