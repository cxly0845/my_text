#ifndef __SkiSafari_CupScene_H__
#define __SkiSafari_CupScene_H__
#include "cocos2d.h"
USING_NS_CC;

class CupScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(CupScene);
	CCSize winSize;
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
};
#endif