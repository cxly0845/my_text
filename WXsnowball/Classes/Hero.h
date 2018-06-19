#ifndef __Hero_H__
#define __Hero_H__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define NUM_PREV_VELS 5			//��һ������
#define HERO_ID 222

USING_NS_CC;

class Hero :public CCSprite					//Ӣ������
{
public:
	static Hero* createHero();
	void initHero(CCPoint p, b2World* world);

	void skiSpeed();			
	void flySpeed();
	void standSpeed();
	void highSpeed();
	void update(float dt);
	void limitVelocity();
	void jump();
public:
	bool isFly;			//�Ƿ����
	bool isEnd;			//�Ƿ����
	b2Body* _myBody;

private:
	b2World* _myWorld;
	CCLayer* _myLayer;
	int _nextVel;							//��һ���ٶ�
	b2Vec2 _preVels[NUM_PREV_VELS];			//�ٶ�����

};


#endif