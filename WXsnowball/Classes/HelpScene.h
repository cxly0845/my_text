#ifndef __HelpScene_H__
#define __HelpScene_H__

#include "cocos2d.h"
#include "ui\UIScrollView.h"



class HelpScene :public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(HelpScene);
	virtual void onEnter();
	virtual void onExit();

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	
	cocos2d::ui::ScrollView* scrollView;		//�����Ӵ�
	cocos2d::Size winSize;
	cocos2d::Layer* layer;

	bool flag;		//����������־

	void leftOrRight(cocos2d::Ref* items);		

	void setFlag();

};
#endif