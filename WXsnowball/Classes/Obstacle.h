#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
#include<iostream>
#include"cocos2d.h"
#include"Box2D/Box2D.h"

USING_NS_CC;

typedef enum
{
	obstacle_house = 0,				//����
	obstacle_bird,					//��
	obstacle_guideboard,			//·��
	obstacle_box,					//����
	obstacle_gold,					//�ƽ�
	obstacle_fire,					//��
	obstacle_snowball,				//ѩ��
	obstacle_penguin,				//���
	obstacle_icepiton,				//����
	obstacle_xin,					//����
	obstacle_diamond				//��ʯ

}ObstacleType;

class Obstacle :public CCSprite							//�ϰ������
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
	b2Body *Obstacle_body;			//�ϰ������
	bool isContact;					//�Ƿ�����
	bool isFllow;					//�Ƿ�Ư��			
	bool ispenguinContace;			//�Ƿ��������
	b2Body * ballBody;				//�����
	b2Body * birdBody;				//�����
	b2Body *penguinBody;			//������
private:
	b2World * world;				//��������
	CCPoint point;
	CCLayer * layer;

};

#endif