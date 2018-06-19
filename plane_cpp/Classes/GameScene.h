#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

//游戏总场景类
class GameScene : public cocos2d::Scene
{
public:
	virtual bool init() override;
	virtual void onEnter() override;


	CREATE_FUNC(GameScene);

};

#endif