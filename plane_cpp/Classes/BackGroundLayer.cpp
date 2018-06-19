#include "BackGroundLayer.h"

USING_NS_CC;

bool BackGroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//Ìí¼Ó±³¾°Í¼Æ¬
	backGround1 = Sprite::createWithSpriteFrameName("background.png");
	backGround1->setPosition(Vec2(0, 0));
	backGround1->setContentSize(Size(480, 852));
	backGround1->setAnchorPoint(Point::ZERO);
	this->addChild(backGround1);

	backGround2 = Sprite::createWithSpriteFrameName("background.png");
	backGround2->setContentSize(Size(480, 852));
	backGround2->setAnchorPoint(Point::ZERO);
	backGround2->setPosition(Vec2(0,850));
	this->addChild(backGround2);

	scheduleUpdate();

	return true;
}

void BackGroundLayer::update(float time)
{
	//±³¾°¹ö¶¯
	 
	backGround1->setPositionY(backGround1->getPositionY() - 2);
	backGround2->setPositionY(backGround1->getContentSize().height + backGround1->getPositionY() -2 );

	if (backGround2->getPositionY() <= 0)
	{
		backGround1->setPositionY(0);
	}

}

