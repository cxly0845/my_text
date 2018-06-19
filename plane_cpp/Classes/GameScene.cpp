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
	
	this->addChild(BackGroundLayer::create());             //Ìí¼Ó±³¾°²ã
	auto planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);							//Ìí¼Ó·É»ú²ã

	return true;
}


void GameScene::onEnter()
{
	Scene::onEnter();

	//²¥·Å±³¾°ÒôÀÖ
	SimpleAudioEngine::getInstance()->playBackgroundMusic("AirplaneResource/sound/game_music.mp3", true);
}
