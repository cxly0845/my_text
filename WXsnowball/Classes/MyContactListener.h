#ifndef __MyContactListener_H__
#define __MyContactListener_H__
#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
using namespace std;

class MyContactListener :public b2ContactListener      //碰撞检测
{
public:
	b2World* _world;
	CCLayer* _layer;
	MyContactListener();
	MyContactListener(b2World* world, CCLayer* layer);
	~MyContactListener();

	//碰撞开始
	virtual void BeginContact(b2Contact* contact);		
	//碰撞结束
	virtual void EndContact(b2Contact* contact);				
	//碰撞开始之前
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);		
	//碰撞结束之后
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);		

private:

};


#endif