#ifndef __PLANELAYER_H__
#define __PLANELAYER_H__
#include "cocos2d.h"
class MyPlane;
class EmPlane;
//�ɻ����࣬���Ϸ��÷ɻ�
class PlaneLayer : public cocos2d::Layer
{
public:
	MyPlane* myPlane;										//�ҷ��ɻ�
	float addEmPlaneTime = 2.0;						    	//��ӵл�ʱ��
	cocos2d::Vector<EmPlane*> emPlaneManage;				//�л�������
	CREATE_FUNC(PlaneLayer);
//	cocos2d::Vector<cocos2d::Sprite*> bulletTemp;				//��ʱ��������ӵ�����
//	cocos2d::Vector<EmPlane*> emPlaneTemp;						//��ʱ��������л�
	cocos2d::LabelBMFont* label;

private:
	virtual bool init() override;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void addEmPlane(float time);							//��ӵл�
	virtual void update(float time) override;				//��ײ���
	void addEmPlaneZ(EmPlane* emPlane);						//��ӵл�����
};

#endif __PLANELAYER_H__