#ifndef __SkiSafari_PauseScene_H__
#define __SkiSafari_PauseScene_H__

#include<iostream>
#include "cocos2d.h"

USING_NS_CC;

class PauseScene :public CCLayerColor
{
public:

	PauseScene();
	void backToGame(CCObject* c);
	void backMenu(CCObject* c);

	virtual void onEnter();
	virtual void onExit();

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
//	void onTouchMoved(Touch *pTouch, Event *pEvent);
//	void onTouchEnded(Touch *pTouch, Event *pEvent);
//	void onTouchCancelled(Touch *pTouch, Event *pEvent);
private:


};


#endif