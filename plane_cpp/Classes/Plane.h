#ifndef __PLANE_H__
#define __PLANE_H__
#include "cocos2d.h"

enum EmPlaneKind{SMALL,MIDDLE,BIG};			//敌机型号定义

//我方飞机类
class MyPlane : public cocos2d::Node
{
public:
	cocos2d::Sprite* planeSprite;			//飞机精灵
	bool planeLife = true;					//飞机生命
	unsigned int count = 0;						//飞机得分

	int bulletSpeed = 600;										//子弹速度
	cocos2d::Node* bulletLayer;									//子弹发射出后所在图层
	cocos2d::Vector<cocos2d::Sprite *> bulletManage;			//子弹管理器

	CREATE_FUNC(MyPlane);
	bool init();
	void shoot(float time, cocos2d::Node *object);		//射击(发射频率，子弹射出所在图层)
	void stopShoot();									//停止发射子弹
	void addBullet(float time);							//添加子弹
	void deleteBullet(cocos2d::Node *bulletObject);		//删除子弹
private:

};



//敌方飞机类
class EmPlane : public cocos2d::Node
{
public:
	unsigned char planeLife;								//敌机生命
	float emPlaneTime = 20;									//敌机飞行时间
	cocos2d::Sprite* emPlaneSprite;							//敌机精灵
	EmPlaneKind emPlaneKind;								//敌机型号
	unsigned int emPlaneLife;								//敌机生命
	cocos2d::Node* emPlaneLayer;							//敌机所在图层
	cocos2d::Vector<EmPlane*> *emPlaneMange;			    //敌机管理器代理

	static EmPlane* create(EmPlaneKind emPlaneKind);		//根据型号创建敌机
	void flyAction(cocos2d::Node* emPlaneLayer);			//敌机飞行动作
	void emPlaneDelete(cocos2d::Node *bulletObject);		//删除敌机
	void emAnimate();										//敌机爆炸动画
	void hitAction();										//敌机被击中动画
	void emPlaneDeleteToEmemAnimate(cocos2d::Node *bulletObject);//敌机爆炸后删除敌机方法
private:
	bool init();

};





#endif  __PLANE_H__