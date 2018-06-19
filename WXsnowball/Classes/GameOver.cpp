#include"GameOver.h"
#include"DataManager.h"
#include"CupScene.h"
#include"StartGame.h"
CCScene * GameOver::scene()
{
	CCScene * scene = CCScene::create();
	GameOver * layer = GameOver::create();
	scene->addChild(layer);
	return scene;

}
bool GameOver::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	isNext = true;

	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite * bgSprite = CCSprite::create("end_bg.png");
	bgSprite->setScale(0.5f);
	bgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bgSprite);





	CCSprite * overSprite = CCSprite::create("gameover.png");
	overSprite->setPosition(ccp(winSize.width / 2, winSize.height - 50));
	this->addChild(overSprite);

	CCScaleTo * toBig = CCScaleTo::create(2.0f, 1.2f);
	CCScaleTo * toSmall = CCScaleTo::create(2.0f, 0.8f);
	CCSequence * seq = CCSequence::create(toBig, toSmall, NULL);
	overSprite->runAction(CCRepeatForever::create(seq));


	ScoreSprite = CCSprite::create("score.png");
	ScoreSprite->setScale(0.5f);
	ScoreSprite->setPosition(ccp(winSize.width / 2 - 20, winSize.height / 2));
	this->addChild(ScoreSprite);


	char tmp[10];
	sprintf(tmp, "%i", DataManager::getInstance()->_currentScore);
	Scorelabel = CCLabelTTF::create(tmp, "", 35);
	Scorelabel->setPosition(ccp(winSize.width / 2 + 50, winSize.height / 2));
	Scorelabel->setColor(ccc3(255, 0, 255));
	this->addChild(Scorelabel);



	CCMenuItemImage *nextItem = CCMenuItemImage::create("next_btn.png", "next_btn.png");
	nextItem->setTarget(this, menu_selector(GameOver::ToNext));
	nextItem->setPosition(ccp(winSize.width - 60, 50));
	nextItem->setScale(0.9f);
	nextItem->setRotationY(10);
	CCMenu* endMenu = CCMenu::create(nextItem, NULL);
	endMenu->setPosition(Vec2::ZERO);
	this->addChild(endMenu);

	CCParticleSnow* PariticleSnow = CCParticleSnow::create();
	PariticleSnow->setScale(1.2f);
	PariticleSnow->setPosition(ccp(winSize.width / 2 - 40, winSize.height));
	PariticleSnow->setSpeed(10);

	PariticleSnow->setBlendAdditive(true);
	this->addChild(PariticleSnow);

	PariticleSnow->setAutoRemoveOnFinish(true);

	return true;

}
void  GameOver::ToNext(CCObject* object)
{

	if (isNext)
	{
		isNext = false;
		ScoreSprite->removeFromParent();
		Scorelabel->removeFromParent();
		CupScene* layer = CupScene::create();
		layer->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 30));
		layer->setAnchorPoint(Vec2::ZERO);
		layer->setScale(0.5f);
		this->addChild(layer);
		
		CCDirector::sharedDirector()->replaceScene(StartGame::create());
	}
	else
	{
		isNext = true;
		CCDirector::sharedDirector()->replaceScene(StartGame::create());

	}

}

void GameOver::onkeyBackClicked()
{
	/*BackMenu * back = new BackMenu();
	back->keyBackClickeds();
	this->addChild(back, 100);*/
}

void GameOver::onkeyMenuClicked()
{


}