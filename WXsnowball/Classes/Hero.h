#ifndef __Hero_H__
#define __Hero_H__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define NUM_PREV_VELS 5			//上一个速率
#define HERO_ID 222

USING_NS_CC;

class Hero :public CCSprite					//英雄主角
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
	bool isFly;			//是否飞行
	bool isEnd;			//是否结束
	b2Body* _myBody;

private:
	b2World* _myWorld;
	CCLayer* _myLayer;
	int _nextVel;							//下一个速度
	b2Vec2 _preVels[NUM_PREV_VELS];			//速度数组

};


#endif