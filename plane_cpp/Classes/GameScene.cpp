#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BackGroundLayer.h"
#include "PlaneLayer.h"
#include "Plane.h"

USING_NS_CC;
using namespace CocosDenshion;


bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	this->addChild(BackGroundLayer::create());             //��ӱ�����
	auto planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);							//��ӷɻ���

	return true;
}


void GameScene::onEnter()
{
	Scene::onEnter();

	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("AirplaneResource/sound/game_music.mp3", true);
}
