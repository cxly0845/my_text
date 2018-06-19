#ifndef __StartGame_H__
#define __StartGame_H__
#include "cocos2d.h"


class StartGame : public cocos2d::Scene
{
public:
	CREATE_FUNC(StartGame);

private:
	StartGame();
	~StartGame(){};

	CC_SYNTHESIZE(bool, isBack, IsBack);		//是否开启菜单面板
	CC_SYNTHESIZE(bool, isSound, IsSound);		//是否开启声音
	CC_SYNTHESIZE(bool, isHelp, IsHelp);		//是否开启帮助
	CC_SYNTHESIZE(bool, isCup, IsCup);			//是否开启奖杯

	cocos2d::Node* nodeSprite;				//背景节点
	cocos2d::Node * nodeMenu;				//菜单节点

	virtual bool init();

	void onkeyBackClicked(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void RemoveLabel(cocos2d::Node * node);
	void createLabel(float dt);
	void ToAlert(cocos2d::Ref* object);
	void ControlMusic(cocos2d::Ref* object);
	void goNext(cocos2d::Ref* sender);
	void ToCup(cocos2d::Ref* object);
	void ToHelp(cocos2d::Ref* object);
	void addHeroAnimation();
	void UndoHelp(cocos2d::Ref* object);
	void UndoCup(cocos2d::Ref* object);

};
#endif