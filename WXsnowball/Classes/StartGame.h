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

	CC_SYNTHESIZE(bool, isBack, IsBack);		//�Ƿ����˵����
	CC_SYNTHESIZE(bool, isSound, IsSound);		//�Ƿ�������
	CC_SYNTHESIZE(bool, isHelp, IsHelp);		//�Ƿ�������
	CC_SYNTHESIZE(bool, isCup, IsCup);			//�Ƿ�������

	cocos2d::Node* nodeSprite;				//�����ڵ�
	cocos2d::Node * nodeMenu;				//�˵��ڵ�

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