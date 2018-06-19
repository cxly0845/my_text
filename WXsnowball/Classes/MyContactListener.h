#ifndef __MyContactListener_H__
#define __MyContactListener_H__
#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
using namespace std;

class MyContactListener :public b2ContactListener      //��ײ���
{
public:
	b2World* _world;
	CCLayer* _layer;
	MyContactListener();
	MyContactListener(b2World* world, CCLayer* layer);
	~MyContactListener();

	//��ײ��ʼ
	virtual void BeginContact(b2Contact* contact);		
	//��ײ����
	virtual void EndContact(b2Contact* contact);				
	//��ײ��ʼ֮ǰ
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);		
	//��ײ����֮��
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);		

private:

};


#endif