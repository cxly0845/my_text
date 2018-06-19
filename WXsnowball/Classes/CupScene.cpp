#include"CupScene.h"
#include"DataManager.h"
#include"BackMenu.h"
USING_NS_CC;

using namespace cocos2d;
CCScene* CupScene::scene()
{
	CCScene *scene = CCScene::create();
	CupScene *layer = CupScene::create();
	scene->addChild(layer);
	return scene;
}
bool CupScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}


	CCSprite* bgSprite = CCSprite::create("chengjiu_bg.png");
	bgSprite->setScale(1.2f);
	bgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bgSprite);

	DataManager::getInstance()->_rankScore[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("First");
	DataManager::getInstance()->_rankScore[1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("Second");
	DataManager::getInstance()->_rankScore[2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("Third");
	DataManager::getInstance()->_rankScore[3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("Fourth");
	DataManager::getInstance()->_rankScore[4] = CCUserDefault::sharedUserDefault()->getIntegerForKey("Fivth");
	DataManager::getInstance()->_rankScore[5] = CCUserDefault::sharedUserDefault()->getIntegerForKey("Sixth");
	DataManager::getInstance()->getHighestScore();

	CCUserDefault::sharedUserDefault()->setIntegerForKey("Seventh", DataManager::getInstance()->_rankScore[5]);
	for (int i = 0; i<5; i++)
	{


		CCSprite* labelBgSprite = CCSprite::create("chengjiu_labelbg.png");
		labelBgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 65 * i + 110));
		this->addChild(labelBgSprite);

		CCSize size = labelBgSprite->getContentSize();
		CCLabelTTF * label;
		if (DataManager::getInstance()->_rankScore[i] != 0)
		{
			char tmp[20];
			sprintf(tmp, "%d", DataManager::getInstance()->_rankScore[i]);
			label = CCLabelTTF::create(tmp, "", 40);

		}
		else
		{
			label = CCLabelTTF::create("", "", 40);
		}
		label->setPosition(ccp(size.width / 2, size.height / 2));
		labelBgSprite->addChild(label);

		if (DataManager::getInstance()->_rankScore[i] == DataManager::getInstance()->_currentScore&&DataManager::getInstance()->_rankScore[i] != 0 && DataManager::getInstance()->isBlink)
		{
			DataManager::getInstance()->isBlink = false;
			CCBlink * blink = CCBlink::create(1.5f, 1);
			labelBgSprite->runAction(CCRepeatForever::create(blink));

		}

	}

	//¼àÌýÆ÷£¬ÓÃÀ´ÍÌÊÉ¼àÌýÊÂ¼þ
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CupScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);

	return true;
}

bool CupScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

