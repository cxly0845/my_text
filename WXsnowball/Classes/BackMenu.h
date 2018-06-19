#ifndef __BackMenu_H__
#define __BackMenu_H__

#include "cocos2d.h"

class BackMenu :public cocos2d::Layer
{
public:
	BackMenu();
	~BackMenu();
	static BackMenu* getInstance();
	void showBackMenu(cocos2d::Node *node);	
	void backToGame(cocos2d::Ref * o);
private:
	CC_SYNTHESIZE(bool, isShow, IsShow);
	cocos2d::Sprite * sprite;
	CREATE_FUNC(BackMenu);
	virtual bool init();
	void endGame(cocos2d::Ref  * o);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	
};

#endif 