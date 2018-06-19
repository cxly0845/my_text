#include "Plane.h"
#include "SimpleAudioEngine.h"
#include "stdio.h"


using namespace CocosDenshion;

USING_NS_CC;

//************�ҷ��ɻ�****************

bool MyPlane::init()
{
	if (!Node::init())
	{
		return false;
	}

	//���ɻ�������뵽MyPlane�ڵ�
	planeSprite = Sprite::createWithSpriteFrameName("hero1.png");
	planeSprite->setIgnoreAnchorPointForPosition(true);
	this->setContentSize(Size(planeSprite->getContentSize().width, planeSprite->getContentSize().height));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Point(240, 50));
	this->addChild(planeSprite);

	//�ɻ�����
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.07f);

	auto cache = SpriteFrameCache::getInstance();
	animation->addSpriteFrame(cache->getSpriteFrameByName("hero1.png"));
	animation->addSpriteFrame(cache->getSpriteFrameByName("hero2.png"));

	auto animate = Animate::create(animation);
	planeSprite->runAction(RepeatForever::create(animate));

	return true;
}

void MyPlane::shoot(float time, cocos2d::Node* object)
{
	this->bulletLayer = object;
	this->schedule(schedule_selector(MyPlane::addBullet,this),time,kRepeatForever,0);
}

void MyPlane::stopShoot()
{
	this->unschedule(schedule_selector(MyPlane::addBullet,this));
}


void MyPlane::addBullet(float time)
{
	//SimpleAudioEngine::getInstance()->playEffect("AirplaneResource/sound/bullet.mp3");							 //�����ӵ�����

	auto bullet = Sprite::createWithSpriteFrameName("bullet2.png");
	bulletLayer->addChild(bullet);
	this->bulletManage.pushBack(bullet);																			 //���ӵ����������
	bullet->setPosition(Vec2(this->getPositionX(), this->getPositionY() + this->getContentSize().height / 2 + 2));

	float bulletTime = (852 - bullet->getPositionY()) / this->bulletSpeed;											 //�ӵ�����ʱ��
	auto action = MoveTo::create(bulletTime,Vec2(bullet->getPositionX(),852));										 //�ӵ��ƶ�����
	auto actionFinish = CallFuncN::create(this,callfuncN_selector(MyPlane::deleteBullet));						   	 //�ӵ��Ƴ���Ļ��ɾ���ӵ�������
	bullet->runAction(Sequence::create(action, actionFinish, NULL));
}
int temp = 1;
void MyPlane::deleteBullet(Node *bulletObject)
{
	if (bulletObject != nullptr)
	{
		Sprite* bullet = (Sprite*)bulletObject;
		this->bulletManage.eraseObject(bullet);
		bulletLayer->removeChild(bullet);
	}
}





//***********�з��ɻ�*****************

EmPlane* EmPlane::create(EmPlaneKind emPlaneKind)
{
	EmPlane* emPlane = new EmPlane();
	emPlane->emPlaneKind = emPlaneKind;
	if (emPlane && emPlane->init())
	{ 
		emPlane->autorelease();
		return emPlane;
	} 
	else 
	{ 
		delete emPlane;
		emPlane = nullptr;
		return nullptr; 
	}
}

bool EmPlane::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->setAnchorPoint(Vec2(0.5, 0.5));				//�����л��ڵ��ê��

	if (this->emPlaneKind == SMALL)						//��ʼ��С�͵л�
	{
		this->emPlaneSprite = Sprite::createWithSpriteFrameName("enemy1.png");
		this->emPlaneLife = 1;
		emPlaneSprite->setIgnoreAnchorPointForPosition(true);
		this->setContentSize(Size(emPlaneSprite->getContentSize().width, emPlaneSprite->getContentSize().height));
		this->addChild(emPlaneSprite);

		float count = ((rand() % ((int)(461 - (this->getContentSize().width)))) + this->getContentSize().width / 2 + 10);			//�������λ��
		this->setPosition(Vec2(count, 852 + this->getContentSize().height / 2));

	}
	else if (this->emPlaneKind == MIDDLE)				//��ʼ�����͵л�
	{
		this->emPlaneSprite = Sprite::createWithSpriteFrameName("enemy2.png");
		this->emPlaneLife = 6;
		emPlaneSprite->setIgnoreAnchorPointForPosition(true);
		this->setContentSize(Size(emPlaneSprite->getContentSize().width, emPlaneSprite->getContentSize().height));
		this->addChild(emPlaneSprite);

		float count = ((rand() % ((int)(461 - (this->getContentSize().width)))) + this->getContentSize().width / 2 + 10);			//�������λ��
		this->setPosition(Vec2(count, 852 + this->getContentSize().height / 2));
	}	
	else if (this->emPlaneKind == BIG)					//��ʼ�����͵л�
	{
		this->emPlaneSprite = Sprite::createWithSpriteFrameName("enemy3_n1.png");
		this->emPlaneLife = 12;
		emPlaneSprite->setIgnoreAnchorPointForPosition(true);

		//���͵л�����
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		auto animate = Animate::create(animation);
		auto animate1 = RepeatForever::create(animate);
		animate1->setTag(100);
		this->emPlaneSprite->runAction(animate1);


		this->setContentSize(Size(emPlaneSprite->getContentSize().width, emPlaneSprite->getContentSize().height));
		this->addChild(emPlaneSprite);

		float count = ((rand() % ((int)(461 - (this->getContentSize().width)))) + this->getContentSize().width / 2 + 10);			//�������λ��
		this->setPosition(Vec2(count, 852 + this->getContentSize().height / 2));
	}


	return true;
}

void EmPlane::flyAction(Node* emPlaneLayer)
{
	this->emPlaneLayer = emPlaneLayer;
	auto action = MoveTo::create(this->emPlaneTime, Vec2(this->getPositionX(), 0 - this->getContentSize().height / 2));
	auto actionFinish = CallFuncN::create(this, callfuncN_selector(EmPlane::emPlaneDelete));						   	 //�л��Ƴ���Ļ��ɾ���л�������
	this->runAction(Sequence::create(action, actionFinish, NULL));
}

void EmPlane::emPlaneDelete(cocos2d::Node *bulletObject)
{
	if (bulletObject != nullptr)
	{
		EmPlane* emPlane = (EmPlane*)bulletObject;
		this->emPlaneMange->eraseObject(emPlane);				//�ӹ��������Ƴ��л�
		emPlane->emPlaneLayer->removeChild(emPlane);
	}
}

void EmPlane::emAnimate()
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);

	char buff[50] = {0};
	for (int i = 0; i < 4; ++i)
	{
		if (this->emPlaneKind == SMALL)
		{
			sprintf(buff,"enemy1_down%d.png",i + 1);
		}
		else if (this->emPlaneKind == MIDDLE)
		{
			sprintf(buff, "enemy2_down%d.png", i + 1);
		}
		else if (this->emPlaneKind == BIG)
		{
			sprintf(buff, "enemy3_down%d.png", i + 1);
		}
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
	}			
	if (this->emPlaneKind == BIG)																				//����Ǵ��ͷɻ����������֡����
	{
		sprintf(buff,"enemy3_down%d.png",5);
		sprintf(buff, "enemy3_down%d.png", 6);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
	}
	auto animate = Animate::create(animation);
	auto actionFinish = CallFuncN::create(this, callfuncN_selector(EmPlane::emPlaneDeleteToEmemAnimate));
	this->emPlaneSprite->runAction(Sequence::create(animate, actionFinish, NULL));
}

void EmPlane::hitAction()
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	if (this->emPlaneKind == MIDDLE)
	{		
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png"));
	}
	else if (this->emPlaneKind == BIG)
	{
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
	}
	auto animate = Animate::create(animation);
	this->emPlaneSprite->runAction(animate);
}

void EmPlane::emPlaneDeleteToEmemAnimate(cocos2d::Node *bulletObject)
{
	if (bulletObject != nullptr)
	{
		Sprite* emPlane = (Sprite*)bulletObject;
		this->emPlaneMange->eraseObject((EmPlane*)emPlane->getParent());				//�ӹ��������Ƴ��л�
		emPlane->removeFromParent();
	}
}