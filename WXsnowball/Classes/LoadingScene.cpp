#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "StartGame.h"
#include "NewPlayer.h"

USING_NS_CC;

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto winSize = CCDirector::getInstance()->getWinSize();

	auto bgSprite = Sprite::create("loading_bg.png");
	bgSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bgSprite);

	//进度条
	auto timer = ProgressTimer::create(Sprite::create("word.png"));
	auto progressTo = ProgressTo::create(3.5f, 100);
	timer->setType(kCCProgressTimerTypeBar);
	timer->setBarChangeRate(Vec2(1, 0));
	timer->setMidpoint(Vec2(0, 0.5));
	timer->setPosition(Vec2(winSize.width / 2 + 80, winSize.height / 2 - 80));
	this->addChild(timer);
	timer->runAction(progressTo);

	//背景放大并添加标题后，进入游戏场景
	auto scaleBy = ScaleBy::create(3.5f, 2.2f);
	auto fun = CallFunc::create(this, callfunc_selector(LoadingScene::Fade));
	auto add = CallFunc::create(this, callfunc_selector(LoadingScene::addTitle));
	auto seq = Sequence::create(scaleBy, add, DelayTime::create(1.0f), fun, NULL);
	bgSprite->runAction(seq);

	//粒子效果
	auto particle = ParticleGalaxy::create();
	particle->setScale(1.2f);
	particle->setPosition(Vec2(winSize.width / 2 - 80, winSize.height - 50));
	particle->setSpeed(10);
	particle->setBlendAdditive(true);
	particle->setAutoRemoveOnFinish(true);
	this->addChild(particle);


	return true;
}

void LoadingScene::Fade()			//切换游戏场景
{
	if (UserDefault::getInstance()->getBoolForKey("first"))
	{
		Director::getInstance()->replaceScene(StartGame::create());
	}
	else
	{
		Director::getInstance()->replaceScene(NewPlayer::scene());
	}
}

void LoadingScene::addTitle()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto titleSprite = Sprite::create("title.png");
	titleSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 70));
	titleSprite->setScale(0.7f);
	this->addChild(titleSprite);
}


