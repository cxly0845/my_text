#ifndef _SKISAFARI_NEWPLAYER_
#define _SKISAFARI_NEWPLAYER_

#include <iostream>
#include "cocos2d.h"
#include"BackMenu.h"
USING_NS_CC;

class NewPlayer :public CCLayer
{
public:

	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(NewPlayer);
	void onkeyBackClicked();
	void onkeyMenuClicked();

	void snowManClick(CCObject* ob);
	void helpClick(CCObject* ob);
	void scrollClick();
	void closeClick(CCObject* ob);
	void playGame(CCObject* ob);

	CCSize winSize;
	CCSprite* bgSprite1;
	CCSprite* bgSprite2;
	CCMenu* snowMenu;
	CCMenu* helpMenu;
	bool isHelp;
};


#endif