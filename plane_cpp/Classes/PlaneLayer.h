#ifndef __PLANELAYER_H__
#define __PLANELAYER_H__
#include "cocos2d.h"
class MyPlane;
class EmPlane;
//飞机层类，其上放置飞机
class PlaneLayer : public cocos2d::Layer
{
public:
	MyPlane* myPlane;										//我方飞机
	float addEmPlaneTime = 2.0;						    	//添加敌机时间
	cocos2d::Vector<EmPlane*> emPlaneManage;				//敌机管理器
	CREATE_FUNC(PlaneLayer);
//	cocos2d::Vector<cocos2d::Sprite*> bulletTemp;				//临时存放死亡子弹对象
//	cocos2d::Vector<EmPlane*> emPlaneTemp;						//临时存放死亡敌机
	cocos2d::LabelBMFont* label;

private:
	virtual bool init() override;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void addEmPlane(float time);							//添加敌机
	virtual void update(float time) override;				//碰撞检测
	void addEmPlaneZ(EmPlane* emPlane);						//添加敌机属性
};

#endif __PLANELAYER_H__