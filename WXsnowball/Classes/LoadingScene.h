#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(LoadingScene);

private:
	LoadingScene(){};
	~LoadingScene(){};
	virtual bool init();
	void Fade();				//进入场景
	void addTitle();			//添加标题

};

#endif