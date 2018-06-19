#include "BackMenu.h"

USING_NS_CC;
static BackMenu * backMenu = nullptr;

BackMenu::BackMenu():
isShow(false)
{
}

BackMenu::~BackMenu()
{
	backMenu = nullptr;
}

BackMenu* BackMenu::getInstance()
{
	if (backMenu == nullptr)
	{
		backMenu = BackMenu::create();
	}
	
	return backMenu;
}

bool BackMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->pause();			//ÔÝÍ£ÓÎÏ·
	auto Vsize = Director::getInstance()->getVisibleSize();

	//½áÊøÃæ°å±³¾°
	sprite = Sprite::create("endOrno_bg.png");
	sprite->setPosition(Vec2(Vsize.width / 2, Vsize.height / 2));
	sprite->setScale(0.7);

	//ÊÇ °´Å¥
	auto image = MenuItemImage::create("g_yes_hl.png", "g_yes.png");
	image->setTarget(this, menu_selector(BackMenu::endGame));
	image->setScale(0.4);
	image->setPosition(Vec2(185, 140));

	//·ñ °´Å¥
	auto image1 = MenuItemImage::create("g_no_hl.png", "g_no.png", this, menu_selector(BackMenu::backToGame));
	image1->setScale(0.4);
	image1->setPosition(Vec2(300, 140));

	auto menu = Menu::create(image, image1, NULL);
	menu->setPosition(Vec2(0,0));

	//¼àÌýÆ÷£¬ÓÃÀ´ÍÌÊÉ¼àÌýÊÂ¼þ
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BackMenu::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	listener->setSwallowTouches(true);

	this->addChild(sprite);
	this->addChild(menu);

	return true;
}


void BackMenu::endGame(Ref *o)		//½áÊøÓÎÏ·
{
	Director::getInstance()->end();
}
	
void BackMenu::backToGame(Ref *o)	//»Ö¸´ÓÎÏ·
{	
	Director::getInstance()->resume();
	isShow = false;
	this->removeFromParent();
}

void BackMenu::showBackMenu(cocos2d::Node *node)	//ÏÔÊ¾ÍË³öÃæ°å
{
	if (isShow == false)
	{
		node->addChild(this,1000);
		isShow = true;
	}
}

bool BackMenu::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

