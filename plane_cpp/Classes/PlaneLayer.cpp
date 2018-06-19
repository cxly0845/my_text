#include "PlaneLayer.h"
#include "Plane.h"

USING_NS_CC;

bool PlaneLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	myPlane = MyPlane::create();
	myPlane->setTag(1000);
	this->addChild(myPlane);				   //添加我方飞机
	myPlane->shoot(0.1,this);				   //发射子弹

	//添加触摸监听器
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlaneLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PlaneLayer::onTouchMoved, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	schedule(schedule_selector(PlaneLayer::addEmPlane, this), this->addEmPlaneTime, kRepeatForever, 0);			//根据时间添加敌机
	scheduleUpdate();																							//开启碰撞检测

	char buff[50] = { 0 };
	sprintf(buff, "COUNT:%010d", myPlane->count);
	label = LabelBMFont::create(buff, "AirplaneResource/font/font.fnt");
	label->setPosition(Vec2(350, 840));
	this->addChild(label,200);
	return true;
}

//触摸开始执行方法,判断飞机存活并且触摸点在飞机上
bool PlaneLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	Vec2 touchPoint = touch->getLocation();
	Rect planeRect = myPlane->getBoundingBox();

	if (myPlane->planeLife && planeRect.containsPoint(touchPoint))
	{
		//CCLOG("%s","yes");
		return true;
	}
	else
	{
		//CCLOG("%s", "no");
		return false;
	}

}
//触摸移动执行方法，并检测边界
void PlaneLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Vec2 touchPoint = touch->getLocation();

	myPlane->setPosition(touchPoint.x, touchPoint.y);
	if ((myPlane->getPositionX() < (0 + myPlane->getContentSize().width / 2)))
	{
		myPlane->setPositionX(myPlane->getContentSize().width / 2);
	}
	if ((myPlane->getPositionX() > (480 - myPlane->getContentSize().width / 2)))
	{
		myPlane->setPositionX(480 - myPlane->getContentSize().width / 2);
	}
	if ((myPlane->getPositionY() < (0 + myPlane->getContentSize().height / 2)))
	{
		myPlane->setPositionY(myPlane->getContentSize().height / 2);
	}
	if (myPlane->getPositionY() > (852 - myPlane->getContentSize().height / 2))
	{
		myPlane->setPositionY(852 - myPlane->getContentSize().height / 2);
	}
}

void PlaneLayer::addEmPlane(float time)
{
	auto emPlane = EmPlane::create(SMALL);
	this->addChild(emPlane);
	this->addEmPlaneZ(emPlane);

	auto emPlane1 = EmPlane::create(MIDDLE);
	this->addChild(emPlane1);
	this->addEmPlaneZ(emPlane1);

	auto emPlane2 = EmPlane::create(BIG);
	this->addChild(emPlane2);
	this->addEmPlaneZ(emPlane2);
}
/*
void PlaneLayer::update(float time)					//碰撞检测
{
	auto bulletManage = this->myPlane->bulletManage;
	auto emPlaneManage = this->emPlaneManage;
	for (auto bulletIt = bulletManage.begin(); bulletIt != bulletManage.end(); bulletIt++)   //遍历子弹和敌机
	{
		Sprite *bullet = *bulletIt;
		for (auto emPlaneManageIt = emPlaneManage.begin(); emPlaneManageIt != emPlaneManage.end(); emPlaneManageIt++)
		{
			EmPlane* emPlane = *emPlaneManageIt;
			if (emPlane->emPlaneLife != 0 && bullet->getBoundingBox().intersectsRect(emPlane->getBoundingBox()))
			{
				bulletTemp.pushBack(bullet);					//临时保存碰撞子弹
				emPlane->emPlaneLife--;							//敌机生命-1
				switch (emPlane->emPlaneKind)
				{
				case SMALL:
					if (emPlane->emPlaneLife == 0)
					{
						emPlaneTemp.pushBack(emPlane);
						myPlane->count++;
					}
					break;
				case MIDDLE:
					if (emPlane->emPlaneLife == 0)
					{
						emPlaneTemp.pushBack(emPlane);
						myPlane->count = myPlane->count + 5;
					}
					else
					{
						emPlane->hitAction();					//播放敌机被击中动画
					}
					break;
				case BIG:
					if (emPlane->emPlaneLife == 0)
					{
						emPlaneTemp.pushBack(emPlane);
						myPlane->count = myPlane->count + 10;
						emPlane->emPlaneSprite->stopActionByTag(100);
					}
					else
					{
						emPlane->hitAction();					//播放敌机被击中动画
					}
					break;

				}
			}
		}
	}

	for (auto it = bulletTemp.begin(); it != bulletTemp.end(); ++it)		//删除产生碰撞子弹
	{
		Sprite* bullet = *it;
		myPlane->deleteBullet(bullet);
	}
	bulletTemp.clear();					//清空碰撞子弹缓存

	for (auto it = emPlaneTemp.begin(); it != emPlaneTemp.end(); ++it)
	{
		EmPlane* emPlane = *it;
		if (emPlane->emPlaneKind == SMALL)
		{
			emPlane->emPlaneDelete(emPlane);
		}
		else
		{
			emPlane->emAnimate();
		}
		
	}
	emPlaneTemp.clear();				//清空碰撞敌机缓存
	
	char buff[50] = { 0 };
	sprintf(buff, "COUNT:%010d", myPlane->count);
	label->setString(buff);
}
*/

void PlaneLayer::addEmPlaneZ(EmPlane* emPlane)
{
	emPlaneManage.pushBack(emPlane);				//将敌机加入管理器
	emPlane->emPlaneLayer = this;					//设置敌机所在图层
	emPlane->emPlaneMange = &emPlaneManage;			//给敌机设置管理器代理
	emPlane->flyAction(this);
}

void PlaneLayer::update(float time)					//碰撞检测
{
	auto bulletManage = this->myPlane->bulletManage;
	auto emPlaneManage = this->emPlaneManage;
	for (auto bulletIt = bulletManage.begin(); bulletIt != bulletManage.end(); bulletIt++)   //遍历子弹和敌机
	{
		Sprite *bullet = *bulletIt;
		for (auto emPlaneManageIt = emPlaneManage.begin(); emPlaneManageIt != emPlaneManage.end(); emPlaneManageIt++)
		{
			EmPlane* emPlane = *emPlaneManageIt;
			if (emPlane->emPlaneLife != 0 && bullet->getBoundingBox().intersectsRect(emPlane->getBoundingBox()))
			{
				myPlane->deleteBullet(bullet);
				emPlane->emPlaneLife--;							//敌机生命-1
				switch (emPlane->emPlaneKind)
				{
				case SMALL:
					if (emPlane->emPlaneLife == 0)
					{
						emPlane->emPlaneDelete(emPlane);
						myPlane->count++;
					}
					break;
				case MIDDLE:
					if (emPlane->emPlaneLife == 0)
					{
						emPlane->emAnimate();
						myPlane->count = myPlane->count + 5;
					}
					else
					{
						emPlane->hitAction();					//播放敌机被击中动画
					}
					break;
				case BIG:
					if (emPlane->emPlaneLife == 0)
					{
						emPlane->emAnimate();
						myPlane->count = myPlane->count + 10;
						emPlane->emPlaneSprite->stopActionByTag(100);
					}
					else
					{
						emPlane->hitAction();					//播放敌机被击中动画
					}
					break;

				}
			}
		}
	}

	char buff[50] = { 0 };
	sprintf(buff, "COUNT:%010d", myPlane->count);
	label->setString(buff);
}
     
	