#include "HelpScene.h"
#include"cocos2d.h"
#include "BackMenu.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	flag = 0;

	winSize = Director::getInstance()->getWinSize();

	//添加视窗背景面板
	auto bgSprite = Sprite::create("help_bg.png");
	bgSprite->setPosition(Size(winSize.width / 2, winSize.height / 2));
	bgSprite->setScale(0.5);
	this->addChild(bgSprite);

	//创建滚动视窗
	scrollView = ScrollView::create();
	scrollView->setIgnoreAnchorPointForPosition(true);
	scrollView->setPosition(Vec2(winSize.width / 2 - 100 , winSize.height / 2 - 80));
	scrollView->setContentSize(Size(200,160));
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);

	scrollView->setInnerContainerSize(Size(200 * 7, 160));
	//scrollView->setScrollBarEnabled(true);
	//scrollView->setScrollBarColor(Color3B(25,128,49));
	//scrollView->setBounceEnabled(true);

	this->addChild(scrollView);

	//视窗内图层
	layer = Layer::create();
	layer->setContentSize(Size(200 * 8, winSize.height / 2));
	layer->setPosition(Vec2(0,0));

	//视窗内图层上显示内容（菜单形式显示）
	auto layerMenu = Menu::create();
	layerMenu->setPosition(Vec2::ZERO);
	char temp[50];
	for (int i = 0; i<8; i++)
	{
		sprintf(temp, "scroll%i.png", i + 1);
		auto items = MenuItemImage::create(temp, temp);

		items->setPosition(Vec2(i * 200, 0));
		items->setAnchorPoint(Vec2(0,0));
		layerMenu->addChild(items);
	}
	layer->addChild(layerMenu);
	
	scrollView->addChild(layer);
	
	//左侧按钮
	auto left = MenuItemImage::create("left_btn.png", "left_btn.png");
	left->setTarget(this, menu_selector(HelpScene::leftOrRight));
	left->setTag(111);
	left->setScale(0.7f);
	left->setPosition(Vec2(-115, 0));

	//右侧按钮
	auto right = MenuItemImage::create("right_btn.png", "right_btn.png");
	right->setTarget(this, menu_selector(HelpScene::leftOrRight));
	right->setTag(112);
	right->setScale(0.7f);
	right->setPosition(Vec2(116, 0));
	auto menu = Menu::create(left, right, NULL);
	addChild(menu);

	//监听器，用来吞噬监听事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelpScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);

	return true;
}
void HelpScene::onEnter()
{
	flag = false;				//视窗图层没有滚动		
	Layer::onEnter();
}
void HelpScene::onExit()
{
	Layer::onExit();
}

void HelpScene::leftOrRight(Ref* items)   //按钮后 滚动图层
{
	int tag = ((MenuItemImage*)items)->getTag();
	Vec2 p = layer->getPosition();
	CCLOG("layer = %lf",p.x);
	CCLOG("scrollview = %lf", scrollView->getPositionX());
	if (tag == 112 && flag == false && (p.x + 7*200) > scrollView->getPositionX())
	{
		flag = true;					//图层正在滚动状态
		auto move = MoveBy::create(1.0f,Vec2(-200,p.y));
		auto fun = CallFunc::create(this, callfunc_selector(HelpScene::setFlag));
		layer->runAction(Sequence::create(move,fun,nullptr));
	}
	else if (tag == 111 && flag == false && ((p.x + 200 ) < scrollView->getPositionX()))
	{
		flag = true;
		auto move = MoveBy::create(1.0f, Vec2(200, p.y));
		auto fun = CallFunc::create(this, callfunc_selector(HelpScene::setFlag));
		layer->runAction(Sequence::create(move, fun, nullptr));
	}
}

bool HelpScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void HelpScene::setFlag()
{
	flag = false;
}

