#include "Plane.h"
#include "SimpleAudioEngine.h"
#include "stdio.h"


using namespace CocosDenshion;

USING_NS_CC;

//************我方飞机****************

bool MyPlane::init()
{
	if (!Node::init())
	{
		return false;
	}

	//将飞机精灵加入到MyPlane节点
	planeSprite = Sprite::createWithSpriteFrameName("hero1.png");
	planeSprite->setIgnoreAnchorPointForPosition(true);
	this->setContentSize(Size(planeSprite->getContentSize().width, planeSprite->getContentSize().height));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Point(240, 50));
	this->addChild(planeSprite);

	//飞机动画
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
	//SimpleAudioEngine::getInstance()->playEffect("AirplaneResource/sound/bullet.mp3");							 //播放子弹声音

	auto bullet = Sprite::createWithSpriteFrameName("bullet2.png");
	bulletLayer->addChild(bullet);
	this->bulletManage.pushBack(bullet);																			 //将子弹加入管理器
	bullet->setPosition(Vec2(this->getPositionX(), this->getPositionY() + this->getContentSize().height / 2 + 2));

	float bulletTime = (852 - bullet->getPositionY()) / this->bulletSpeed;											 //子弹飞行时间
	auto action = MoveTo::create(bulletTime,Vec2(bullet->getPositionX(),852));										 //子弹移动动作
	auto actionFinish = CallFuncN::create(this,callfuncN_selector(MyPlane::deleteBullet));						   	 //子弹移出屏幕后删除子弹动作。
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





//***********敌方飞机*****************

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

	this->setAnchorPoint(Vec2(0.5, 0.5));				//开启敌机节点的锚点

	if (this->emPlaneKind == SMALL)						//初始化小型敌机
	{
		this->emPlaneSprite = Sprite::createWithSpriteFrameName("enemy1.png");
		this->emPlaneLife = 1;
		emPlaneSprite->setIgnoreAnchorPointForPosition(true);
		this->setContentSize(Size(emPlaneSprite->getContentSize().width, emPlaneSprite->getContentSize().height));
		this->addChild(emPlaneSprite);

		float count = ((rand() % ((int)(461 - (this->getContentSize().width)))) + this->getContentSize().width / 2 + 10);			//生产随机位置
		this->setPosition(Vec2(count, 852 + this->getContentSize().height / 2));

	}
	else if (this->emPlaneKind == MIDDLE)				//初始化中型敌机
	{
		this->emPlaneSprite = Sprite::createWithSpriteFrameName("enemy2.png");
		this->emPlaneLife = 6;
		emPlaneSprite->setIgnoreAnchorPointForPosition(true);
		this->setContentSize(Size(emPlaneSprite->getContentSize().width, emPlaneSprite->getContentSize().height));
		this->addChild(emPlaneSprite);

		float count = ((rand() % ((int)(461 - (this->getContentSize().width)))) + this->getContentSize().width / 2 + 10);			//生产随机位置
		this->setPosition(Vec2(count, 852 + this->getContentSize().height / 2));
	}	
	else if (this->emPlaneKind == BIG)					//初始化大型敌机
	{
		this->emPlaneSprite = Sprite::createWithSpriteFrameName("enemy3_n1.png");
		this->emPlaneLife = 12;
		emPlaneSprite->setIgnoreAnchorPointForPosition(true);

		//大型敌机动画
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

		float count = ((rand() % ((int)(461 - (this->getContentSize().width)))) + this->getContentSize().width / 2 + 10);			//生产随机位置
		this->setPosition(Vec2(count, 852 + this->getContentSize().height / 2));
	}


	return true;
}

void EmPlane::flyAction(Node* emPlaneLayer)
{
	this->emPlaneLayer = emPlaneLayer;
	auto action = MoveTo::create(this->emPlaneTime, Vec2(this->getPositionX(), 0 - this->getContentSize().height / 2));
	auto actionFinish = CallFuncN::create(this, callfuncN_selector(EmPlane::emPlaneDelete));						   	 //敌机移出屏幕后删除敌机动作。
	this->runAction(Sequence::create(action, actionFinish, NULL));
}

void EmPlane::emPlaneDelete(cocos2d::Node *bulletObject)
{
	if (bulletObject != nullptr)
	{
		EmPlane* emPlane = (EmPlane*)bulletObject;
		this->emPlaneMange->eraseObject(emPlane);				//从管理器中移出敌机
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
	if (this->emPlaneKind == BIG)																				//如果是大型飞机，再添加两帧动画
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
		this->emPlaneMange->eraseObject((EmPlane*)emPlane->getParent());				//从管理器中移出敌机
		emPlane->removeFromParent();
	}
}