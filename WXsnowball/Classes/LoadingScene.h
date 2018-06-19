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
	void Fade();				//���볡��
	void addTitle();			//��ӱ���

};

#endif