#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__
#include "cocos2d.h"

//±≥æ∞Õº≤„¿‡
class BackGroundLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BackGroundLayer);
	
private:
	cocos2d::Sprite* backGround1;
	cocos2d::Sprite* backGround2;

	virtual bool init() override;
	virtual void update(float time) override;
};




#endif