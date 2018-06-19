#ifndef __PLANE_H__
#define __PLANE_H__
#include "cocos2d.h"

enum EmPlaneKind{SMALL,MIDDLE,BIG};			//�л��ͺŶ���

//�ҷ��ɻ���
class MyPlane : public cocos2d::Node
{
public:
	cocos2d::Sprite* planeSprite;			//�ɻ�����
	bool planeLife = true;					//�ɻ�����
	unsigned int count = 0;						//�ɻ��÷�

	int bulletSpeed = 600;										//�ӵ��ٶ�
	cocos2d::Node* bulletLayer;									//�ӵ������������ͼ��
	cocos2d::Vector<cocos2d::Sprite *> bulletManage;			//�ӵ�������

	CREATE_FUNC(MyPlane);
	bool init();
	void shoot(float time, cocos2d::Node *object);		//���(����Ƶ�ʣ��ӵ��������ͼ��)
	void stopShoot();									//ֹͣ�����ӵ�
	void addBullet(float time);							//����ӵ�
	void deleteBullet(cocos2d::Node *bulletObject);		//ɾ���ӵ�
private:

};



//�з��ɻ���
class EmPlane : public cocos2d::Node
{
public:
	unsigned char planeLife;								//�л�����
	float emPlaneTime = 20;									//�л�����ʱ��
	cocos2d::Sprite* emPlaneSprite;							//�л�����
	EmPlaneKind emPlaneKind;								//�л��ͺ�
	unsigned int emPlaneLife;								//�л�����
	cocos2d::Node* emPlaneLayer;							//�л�����ͼ��
	cocos2d::Vector<EmPlane*> *emPlaneMange;			    //�л�����������

	static EmPlane* create(EmPlaneKind emPlaneKind);		//�����ͺŴ����л�
	void flyAction(cocos2d::Node* emPlaneLayer);			//�л����ж���
	void emPlaneDelete(cocos2d::Node *bulletObject);		//ɾ���л�
	void emAnimate();										//�л���ը����
	void hitAction();										//�л������ж���
	void emPlaneDeleteToEmemAnimate(cocos2d::Node *bulletObject);//�л���ը��ɾ���л�����
private:
	bool init();

};





#endif  __PLANE_H__