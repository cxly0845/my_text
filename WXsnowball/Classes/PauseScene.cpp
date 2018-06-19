#include "PauseScene.h"
#include "StartGame.h"

PauseScene::PauseScene()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->initWithColor(ccc4(98, 98, 98, 45));

	CCMenuItemImage* PauseItem = CCMenuItemImage::create("resume_btn.png", "resume_btn.png");
	PauseItem->setTarget(this, menu_selector(PauseScene::backToGame));
	PauseItem->setScale(0.5f);
	CCMenu* PauseMenu = CCMenu::create(PauseItem, NULL);
	PauseMenu->setTag(131);
	PauseMenu->setPosition(ccp(winSize.width / 2 + 180, winSize.height / 2 + 10));
	CCScaleTo* scaleToBig = CCScaleTo::create(2.0f, 0.6f);
	CCScaleTo * scaleToSmall = CCScaleTo::create(2.0f, 0.4f);
	CCSequence *seq = CCSequence::create(scaleToBig, scaleToSmall, NULL);
	PauseItem->runAction(CCRepeatForever::create(seq));
	this->addChild(PauseMenu, 30);


	//返回主界面按钮
	CCMenuItemImage* BackItem = CCMenuItemImage::create("home_btn.png", "home_btn.png");
	BackItem->setScale(0.55f);
	BackItem->setTarget(this, menu_selector(PauseScene::backMenu));
	CCMenu* BackMenu = CCMenu::create(BackItem, NULL);
	BackMenu->setTag(132);
	BackMenu->setPosition(ccp(winSize.width - 60, winSize.height / 2 - 90));
	this->addChild(BackMenu, 30);

}

void PauseScene::backToGame(CCObject* c)
{
	CCDirector::sharedDirector()->resume();
	this->removeFromParent();
}

void PauseScene::backMenu(CCObject* c)
{
	CCDirector::sharedDirector()->replaceScene(StartGame::create());
}

void PauseScene::onEnter()
{
	CCLayerColor::onEnter();
	//触摸监听器
}
void PauseScene::onExit()
{
	
}

bool PauseScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}
