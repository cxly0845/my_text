#include "MyContactListener.h"
#include "MyTerrain.h"
#include "Hero.h"
#include "Obstacle.h"

MyContactListener::MyContactListener()
{}
MyContactListener::MyContactListener(b2World* world, CCLayer* layer)
{
	_world = world;
	_layer = layer;
}
MyContactListener::~MyContactListener()
{}

void MyContactListener::BeginContact(b2Contact* contact)
{}
void MyContactListener::EndContact(b2Contact* contact)
{}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{


}
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	float force = impulse->normalImpulses[0];
	if (force > 0)				//主角和地形碰撞
	{
		CCSprite* spriteA = (CCSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
		CCSprite* spriteB = (CCSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
		if (spriteA && spriteB)
		{
			if (spriteA->getTag() == HERO_ID && spriteB->getTag() == 111)
			{
				Hero* h = (Hero*)spriteA;
				h->isFly = false;
			}
			if (spriteA->getTag() == 111 && spriteB->getTag() == HERO_ID)
			{
				Hero* h = (Hero*)spriteB;
				h->isFly = false;
			}
		}
	}
	if (force > 0)		//主角和障碍物碰撞
	{
		CCSprite* spriteA = (CCSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
		CCSprite* spriteB = (CCSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
		if (spriteA && spriteB)
		{
			if (spriteA->getTag() == HERO_ID && spriteB->getTag() == 333)
			{
				Obstacle* sp = (Obstacle*)spriteB;
				Hero* he = (Hero*)spriteA;
				if (sp->spType == obstacle_bird)
				{
					sp->isFllow = true;
				}
				else if (sp->spType == obstacle_box)
				{
					sp->isContact = true;
					sp->boxAnimation();
				}

				else if (sp->spType == obstacle_penguin)
				{
					sp->ispenguinContace = true;
				}
				else if (sp->spType == obstacle_snowball)
				{
					he->isEnd = true;
				}

			}
			if (spriteA->getTag() == 333 && spriteB->getTag() == HERO_ID)
			{
				Obstacle* sp = (Obstacle*)spriteA;
				Hero* he = (Hero*)spriteB;
				if (sp->spType == obstacle_bird)
				{
					sp->isFllow = true;
				}
				else if (sp->spType == obstacle_box)
				{
					sp->boxAnimation();
					sp->isContact = true;

				}

				else if (sp->spType == obstacle_penguin)
				{
					sp->ispenguinContace = true;
				}
				else if (sp->spType == obstacle_snowball)
				{
					he->isEnd = true;
				}

			}


		}
	}

}