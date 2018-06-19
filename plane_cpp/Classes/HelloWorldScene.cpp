#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include  "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//预加载音乐音效
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("AirplaneResource/sound/game_music.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("AirplaneResource/sound/get_bomb.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("AirplaneResource/sound/button.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("AirplaneResource/sound/bullet.mp3");

	//加载资源图片
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("AirplaneResource/ui/shoot_background.plist");
	cache->addSpriteFramesWithFile("AirplaneResource/ui/shoot.plist");

	//背景
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Vec2::ZERO);
	background->setContentSize(Size(480,852));
	this->addChild(background);

	//飞机大战图片
	auto copyright = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	copyright->setPosition(Vec2(origin.x + visibleSize.width / 2,
							origin.y + visibleSize.height / 2 + 200 ));
	this->addChild(copyright);

	//小飞机动画
	auto game_loading = Sprite::createWithSpriteFrameName("game_loading1.png");
	game_loading->setPosition(Vec2(origin.x + visibleSize.width / 2,
							origin.y + visibleSize.height / 2));
	this->addChild(game_loading);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.25f);

	char buff[50] = { 0 };
	for (int i = 0; i < 4; i++)
	{	
		sprintf(buff,"game_loading%d.png",i+1);
		animation->addSpriteFrame(cache->getSpriteFrameByName(buff));
	}
	auto animate = Animate::create(animation);
	game_loading->runAction(RepeatForever::create(animate));

	//开始游戏按钮
    auto startItem = MenuItemImage::create(
                                           "AirplaneResource/game_start.png",
										   "AirplaneResource/game_start.png",
										   CC_CALLBACK_1(HelloWorld::startCloseCallback, this));
    
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/2-200));
	auto menu = Menu::create(startItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


    
    return true;
}


void HelloWorld::startCloseCallback(Ref* pSender)
{
	auto gameScene = GameScene::create();
	Director::getInstance()->replaceScene(gameScene);
}

    


