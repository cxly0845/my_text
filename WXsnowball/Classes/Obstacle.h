#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
#include<iostream>
#include"cocos2d.h"
#include"Box2D/Box2D.h"

USING_NS_CC;

typedef enum
{
	obstacle_house = 0,				//房子
	obstacle_bird,					//鸟
	obstacle_guideboard,			//路牌
	obstacle_box,					//箱子
	obstacle_gold,					//黄金
	obstacle_fire,					//火
	obstacle_snowball,				//雪球
	obstacle_penguin,				//企鹅
	obstacle_icepiton,				//冰块
	obstacle_xin,					//心心
	obstacle_diamond				//钻石

}ObstacleType;

class Obstacle :public CCSprite							//障碍物对象
{
public:
	Obstacle(ObstacleType spriteType, b2World * _world, CCLayer * _layer, CCPoint p);
	void init_obstacle_house();
	void init_obstacle_bird();
	void init_obstacle_guideboard();
	void init_obstacle_box();
	void init_obstacle_gold();
	void init_obstacle_fire();
	void init_obstacle_snowball();
	void init_obstacle_penguin();
	void init_obstacle_icepiton();
	void init_obstacle_xin();
	void init_obstacle_diamond();

	void goldAnimation();			
	void RemoveAnimation(CCNode * sender);
	void boxAnimation();
	void ballRoll();
	void BirdFlay();
	void createJoin(b2Body * body1, b2Body * body2);
	void _obstacleskiSpeed1();

public:
	ObstacleType spType;
	b2Body *Obstacle_body;			//障碍物刚体
	bool isContact;					//是否连接
	bool isFllow;					//是否漂浮			
	bool ispenguinContace;			//是否连接企鹅
	b2Body * ballBody;				//球刚体
	b2Body * birdBody;				//鸟刚体
	b2Body *penguinBody;			//企鹅刚体
private:
	b2World * world;				//物理世界
	CCPoint point;
	CCLayer * layer;

};

#endif