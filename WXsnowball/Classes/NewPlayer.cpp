#include "NewPlayer.h"
#include "StartGame.h"
#include "HelpScene.h"
#include "GameScene.h"

CCScene* NewPlayer::scene()
{
	CCScene* scene = CCScene::create();
	NewPlayer* layer = NewPlayer::create();
	scene->addChild(layer);
	return scene;
}

bool NewPlayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCUserDefault::sharedUserDefault()->setBoolForKey("first", true);

	isHelp = false;

	winSize = CCDirector::sharedDirector()->getWinSize();

	bgSprite1 = CCSprite::create("newBg1.png");
	bgSprite1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bgSprite1);
	bgSprite1->setOpacity(100);

	CCSprite* hand = CCSprite::create("shou_xia.png");
	hand->setScale(0.3f);
	hand->setTag(369);
	hand->setPosition(ccp(winSize.width / 2 - 180, winSize.height / 2 + 40));
	this->addChild(hand);

	CCMenuItemImage* snowMan = CCMenuItemImage::create("xueren.png", "xueren.png", this, menu_selector(NewPlayer::snowManClick));
	snowMan->setPosition(ccp(winSize.width / 2 - 180, winSize.height / 2 - 70));
	snowMan->setScale(0.6f);
	snowMenu = CCMenu::create(snowMan, NULL);
	snowMenu->setPosition(Vec2::ZERO);
	this->addChild(snowMenu);

	CCMoveTo* moveTo1 = CCMoveTo::create(1.0, ccp(winSize.width / 2 - 180, winSize.height / 2));
	hand->runAction(moveTo1);

	return true;
}

void NewPlayer::snowManClick(CCObject* ob)
{
	this->removeChildByTag(369);
	bgSprite1->removeFromParent();
	snowMenu->removeFromParent();
	bgSprite2 = CCSprite::create("newBg2.png");
	bgSprite2->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	bgSprite2->setOpacity(100);
	this->addChild(bgSprite2);

	CCSprite* hand = CCSprite::create("shou_xia.png");
	hand->setScale(0.3f);
	hand->setTag(123);
	hand->setPosition(ccp(50, 95));
	this->addChild(hand);

	CCMenuItemImage* helpItem = CCMenuItemImage::create("help.png", "help.png", this, menu_selector(NewPlayer::helpClick));
	helpItem->setPosition(ccp(50, 35));
	helpItem->setScale(0.6f);
	helpMenu = CCMenu::create(helpItem, NULL);
	helpMenu->setPosition(Vec2::ZERO);
	helpMenu->setTag(258);
	this->addChild(helpMenu);

	CCMoveTo* moveTo2 = CCMoveTo::create(1.0, ccp(50, 75));
	hand->runAction(moveTo2);
}


void NewPlayer::helpClick(CCObject* ob)
{
	this->removeChildByTag(123);
	this->removeChildByTag(258);

	HelpScene* layer = HelpScene::create();
	layer->setTag(147);
	this->addChild(layer, 30);


	CCMenuItemImage* item = CCMenuItemImage::create("close_btn.png", "close_btn.png");
	item->setScale(0.5f);
	item->setTarget(this, menu_selector(NewPlayer::closeClick));
	item->setPosition(ccp(winSize.width / 2 + 120, winSize.height / 2 + 90));
	CCMenu * menu = CCMenu::create(item, NULL);
	menu->setPosition(Vec2::ZERO);
	layer->addChild(menu);

	isHelp = true;

	CCSprite* hand = CCSprite::create("shou_right.png");
	hand->setScale(0.3f);
	hand->setTag(456);
	hand->setPosition(ccp(winSize.width / 2 - 200, winSize.height / 2));
	this->addChild(hand);

	CCMoveTo* moveTo = CCMoveTo::create(1.0f, ccp(winSize.width / 2 - 170, winSize.height / 2));
	hand->runAction(moveTo);

	CCCallFunc* fun = CCCallFunc::create(this, callfunc_selector(NewPlayer::scrollClick));
	CCSequence* seq = CCSequence::create(CCDelayTime::create(1.0f), fun, NULL);
	this->runAction(seq);
}


void NewPlayer::scrollClick()
{
	this->removeChildByTag(456);

	CCSprite* hand = CCSprite::create("shou_xia.png");
	hand->setScale(0.3f);
	hand->setTag(789);
	hand->setPosition(ccp(winSize.width / 2 + 130, winSize.height / 2 + 150));
	this->addChild(hand);

	CCMoveTo* moveTo = CCMoveTo::create(1.0f, ccp(winSize.width / 2 + 130, winSize.height / 2 + 130));
	hand->runAction(moveTo);
}

void NewPlayer::closeClick(CCObject* ob)
{
	isHelp = true;
	this->removeChildByTag(147);
	this->removeChildByTag(789);

	CCSprite* hand = CCSprite::create("shou_xia.png");
	hand->setScale(0.3f);
	hand->setPosition(ccp(winSize.width - 70, 140));
	this->addChild(hand);

	CCMenuItemImage* beginItem = CCMenuItemImage::create("play.png", "play.png");
	beginItem->setTarget(this, menu_selector(NewPlayer::playGame));
	beginItem->setPosition(ccp(winSize.width - 70, 50));
	CCMenu* menuBegin = CCMenu::create(beginItem, NULL);
	menuBegin->setPosition(Vec2::ZERO);
	this->addChild(menuBegin);
	beginItem->setRotationY(10);

	CCMoveTo* moveTo3 = CCMoveTo::create(1.0f, ccp(winSize.width - 70, 110));
	hand->runAction(moveTo3);
}

void NewPlayer::playGame(CCObject* ob)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}
#pragma mark ·µ»Ø°´Å¥£¬home°´Å¥

void NewPlayer::onkeyBackClicked()
{
	/*BackMenu * back = new BackMenu();
	back->keyBackClickeds();
	this->addChild(back, 100);
	*/
}

void NewPlayer::onkeyMenuClicked()
{

}