#ifndef __SkiSafari_GameOver_H__
#define __SkiSafari_GameOver_H__
#include<iostream>
#include"cocos2d.h"
#include"BackMenu.h"
USING_NS_CC;
class GameOver :public CCLayer			//”Œœ∑Ω· ¯≥°æ∞
{
public:
	static  CCScene * scene();
	virtual bool init();
	CREATE_FUNC(GameOver);
	void onkeyBackClicked();
	void onkeyMenuClicked();
	void ToNext(CCObject* object);
private:
	CCSize winSize;
	bool isNext;
	CCSprite * ScoreSprite;
	CCLabelTTF* Scorelabel;
};

#endif