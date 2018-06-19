#include"StartGame.h"
#include"SimpleAudioEngine.h"
#include "GameScene.h"
#include "BackMenu.h"
#include"HelpScene.h"
#include"CupScene.h"

USING_NS_CC;
using namespace CocosDenshion;

StartGame::StartGame():
isSound(true),
isHelp(true),
isBack(true),
isCup(true),
nodeSprite(nullptr),
nodeMenu(nullptr)
{

}

bool StartGame::init()
{

	if (!Scene::init())
	{
		return false;
	}

	if (Director::getInstance()->isPaused())
	{
		CCDirector::getInstance()->resume();
	}

	SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);
	auto winSize = Director::getInstance()->getWinSize();

	//�����ڵ�
	nodeSprite = Node::create();
	this->addChild(nodeSprite, 0);

	//�˵��ڵ�
	nodeMenu = Node::create();
	this->addChild(nodeMenu, 0);

	//���ñ���1
	auto bgSprite1 = Sprite::create("beijing1.png");
	bgSprite1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bgSprite1->setScale(0.5);
	nodeSprite->addChild(bgSprite1);

	//���ñ���
	auto titleSprite = Sprite::create("title.png");
	titleSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 70));
	titleSprite->setScale(0.8f);
	nodeSprite->addChild(titleSprite);

	//������ǲ�ִ�ж���
	this->addHeroAnimation();

	//���÷���
	auto houseSprite = Sprite::create("house.png");
	houseSprite->setScale(0.5);
	houseSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 50));
	nodeSprite->addChild(houseSprite);

	//˯��z Z ����
	this->schedule(schedule_selector(StartGame::createLabel), 1.0f);				

	//ѩ�˲˵���
	auto snowRightItem = MenuItemImage::create("xueren1.png", "xueren.png");
	auto snowLeftItem =  MenuItemImage::create("xueren.png", "xueren1.png");
	auto toggleSnow =   MenuItemToggle::createWithTarget(this, menu_selector(StartGame::ToAlert), snowRightItem, snowLeftItem, NULL);	//����˵��飬�����õ���¼�
//	toggleSnow->setTarget(this, menu_selector(StartGame::ToAlert));
	toggleSnow->setPosition(Vec2(winSize.width / 2 - 180, winSize.height / 2 - 70));
	toggleSnow->setScale(0.6f);

	//�������ز˵���
	auto selectMusicOnItem = MenuItemImage::create("xitu4.png", "xitu3.png");
	auto selectMusicOffItem = MenuItemImage::create("xitu3.png", "xitu4.png");
	auto toggleMusic = MenuItemToggle::createWithTarget(this, menu_selector(StartGame::ControlMusic), selectMusicOnItem, selectMusicOffItem, NULL);
	toggleMusic->setPosition(Vec2(-20, 35));
	toggleMusic->setScale(0.6f);

	//�����˵���
	auto selectCupItem = MenuItemImage::create("jiangbei.png", "jiangbei.png");
	selectCupItem->setTarget(this, menu_selector(StartGame::ToCup));
	selectCupItem->setPosition(Vec2(-75, 35));
	selectCupItem->setScale(0.5);

	//�����˵���
	auto selectHelpItem = MenuItemImage::create("help.png", "help.png");
	selectHelpItem->setTarget(this, menu_selector(StartGame::ToHelp));
	selectHelpItem->setPosition(Vec2(-50, 35));
	selectHelpItem->setScale(0.6f);

	//�ܲ˵�
	auto menu = CCMenu::create(toggleSnow, toggleMusic, selectCupItem, selectHelpItem, NULL);
	menu->setPosition(Vec2::ZERO);
	nodeMenu->addChild(menu);

	//�����������������˵����
	auto selectSprite = Sprite::create("anniuk.png");
	selectSprite->setScale(1.1f);
	selectSprite->setPosition(Vec2(-48, 50));
	nodeMenu->addChild(selectSprite);
	selectSprite->setZOrder(-1);

	//go��ʼ�˵�
	auto beginItem = MenuItemImage::create("play.png", "play.png");
	beginItem->setTarget(this, menu_selector(StartGame::goNext));
	beginItem->setPosition(Vec2(winSize.width - 70, 50));
	auto menuBegin = Menu::create(beginItem, NULL);
	menuBegin->setPosition(Vec2::ZERO);
	nodeSprite->addChild(menuBegin);
	beginItem->setRotationY(10);

	//ѩ������Ч��
	auto PariticleSnow = ParticleSnow::create();
	PariticleSnow->setScale(1.2f);
	PariticleSnow->setPosition(Vec2(winSize.width / 2 - 40, winSize.height));
	PariticleSnow->setSpeed(10);
	PariticleSnow->setBlendAdditive(true);
	PariticleSnow->setAutoRemoveOnFinish(true);
	nodeSprite->addChild(PariticleSnow);
	
	//�����¼�
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(StartGame::onkeyBackClicked,this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);

	return true;
}

void StartGame::goNext(Ref* sender)			//go��ť�ص�����ʼ��Ϸ
{
	auto fade = TransitionFade::create(3.0f, GameScene::scene());
	Director::getInstance()->replaceScene(fade);
}

void StartGame::RemoveLabel(Node * node)   
{
	node->removeFromParent();
}

void StartGame::createLabel(float dt)					//˯�� z Z ����
{
	auto winSize = Director::getInstance()->getWinSize();
	auto zzLabel = LabelTTF::create("z...   Z...", "Arial", 15);
	zzLabel->setPosition(Vec2(winSize.width / 2 - 10, winSize.height / 2 - 50));
	nodeSprite->addChild(zzLabel);
	auto zzMmoveTo = MoveTo::create(3.0f, Vec2(winSize.width / 2 + 100, winSize.height / 2));
	auto zzScaleTo = ScaleTo::create(3.0f, 1.8f);
	auto zzSpawn = Spawn::create(zzMmoveTo, zzScaleTo, NULL);
	auto fun = CallFuncN::create(this, callfuncN_selector(StartGame::RemoveLabel));
	auto seq = Sequence::create(zzSpawn, fun, NULL);
	zzLabel->runAction(seq);

}
void StartGame::ToAlert(Ref* object)						//С�˵��������ն���
{

	if (isBack)
	{
		isBack = false;
		auto moveto = MoveTo::create(0.5, Vec2(100, 0));
		nodeMenu->runAction(moveto);
	}
	else
	{
		isBack = true;
		auto moveto = MoveTo::create(0.5, Vec2(0, 0));
		nodeMenu->runAction(moveto);

	}
}			
void StartGame::ControlMusic(Ref* object)			//��������ͣ����
{
	if (isSound)
	{
		isSound = false;
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	}
	else
	{
		isSound = true;
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}

}
void StartGame::ToCup(Ref* object)
{
	if (isCup)
	{
		auto winSize = Director::getInstance()->getWinSize();
		isCup = false;
		CupScene* layerCup = CupScene::create();

		layerCup->setTag(20);
		layerCup->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		layerCup->setAnchorPoint(Vec2::ZERO);
		layerCup->setScale(0.7f);
		this->addChild(layerCup);

		CCMenuItemImage* item = CCMenuItemImage::create("close_btn.png", "close_btn.png");
		item->setScale(0.9f);
		item->setTarget(this, menu_selector(StartGame::UndoCup));
		item->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 + 10));
		CCMenu * menu = CCMenu::create(item, NULL);
		menu->setPosition(Vec2::ZERO);
		layerCup->addChild(menu);


		isHelp = true;
		this->removeChildByTag(123);
	}


	else
	{
		isCup = true;
		this->removeChildByTag(20);
	}



}

void StartGame::UndoCup(Ref* object)
{
	if (!isCup)
	{
		isCup = true;
		this->removeChildByTag(20);
	}
}

void StartGame::ToHelp(Ref* object)
{
	if (isHelp)
	{
		auto winSize = Director::getInstance()->getWinSize();
		isHelp = false;
		auto layerHelp = HelpScene::create();			//�ǵø�Ϊ����ģʽ
		layerHelp->setTag(123);
		this->addChild(layerHelp, 30);
		layerHelp->setPosition(Vec2(0, winSize.height / 2));
		auto moveTo = MoveTo::create(2.0f, Vec2(winSize.width / 2 - 220, winSize.height / 2 - 200));
		layerHelp->runAction(moveTo);

		auto item = MenuItemImage::create("close_btn.png", "close_btn.png");
		item->setScale(0.7f);
		item->setTarget(this, menu_selector(StartGame::UndoHelp));
		item->setPosition(Vec2(winSize.width / 2 + 120, winSize.height / 2 + 90));
		auto menu = Menu::create(item, NULL);
		menu->setPosition(Vec2::ZERO);
		layerHelp->addChild(menu);

		isCup = true;
//		this->removeChildByTag(20);
	}
	else
	{
		isHelp = true;
		this->removeChildByTag(123);
	}
}

void StartGame::UndoHelp(Ref* object)
{
	if (!isHelp)
	{
		isHelp = true;
		this->removeChildByTag(123);
	}
}


void StartGame::addHeroAnimation()				//������Ƕ���
{
	auto winSize = Director::getInstance()->getWinSize();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero1.plist");

	//��������֡�ֵ�
	auto dic = Dictionary::createWithContentsOfFile("hero1.plist");
	auto frameDic = (Dictionary *)dic->objectForKey("frames");
	int num = frameDic->allKeys()->count();

	auto allFrames = Vector<SpriteFrame *>();
	for (int i = 0; i<num; i++)
	{
		char frame[15];
		sprintf(frame, "%i.png", i + 11);
		auto frameName = SpriteFrameCache::getInstance()->spriteFrameByName(frame);
		allFrames.pushBack(frameName);
	}
	auto animation = Animation::createWithSpriteFrames(allFrames, 0.5f);
	auto animate = Animate::create(animation);

	auto heroSprite = Sprite::createWithSpriteFrameName("11.png");
	heroSprite->setPosition(Vec2(winSize.width / 2 + 50, winSize.height / 2 - 58));
	heroSprite->setScale(0.2f);
	heroSprite->setScaleY(0.15f);
	nodeSprite->addChild(heroSprite);
	heroSprite->runAction(RepeatForever::create(animate));
}


void StartGame::onkeyBackClicked(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		auto back = BackMenu::getInstance();
		if (back->getIsShow() == false)
		{		
			back->showBackMenu(this);
		}
		else
		{
			back->backToGame(nullptr);
		}	
	}
}


