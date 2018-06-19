#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include"BackMenu.h"
class Hero;
class MyTerrain;
class Obstacle;

USING_NS_CC;

typedef enum
{
	Sprite_gold = 0,
	Sprite_diamond,
	Sprite_fire,
	Sprite_xin

}SpriteType;

class GameScene :public cocos2d::Layer
{
public:
	static CCScene* scene();
	CREATE_FUNC(GameScene);

private:
	GameScene();
	~GameScene(){};

	cocos2d::Size winSize;
	b2World* world;
	Hero* hero;
	cocos2d::Node *node;
	cocos2d::LabelTTF* _distance;		//距离得分
	MyTerrain*  _terrain;				//地形对象
	cocos2d::Array *HpArray;
	cocos2d::Sprite* bgSprite1;
	cocos2d::Sprite* bgSprite2;
	CC_SYNTHESIZE(bool, isPause, IsPause);
	CC_SYNTHESIZE(bool, isMove, IsMove);
	CC_SYNTHESIZE(bool, oldNum, OldNum);
	CC_SYNTHESIZE(bool, newNum, NewNum);
	CC_SYNTHESIZE(bool, isHighSpeed, IsHighSpeed);
	CC_SYNTHESIZE(bool, isContinue, IsContinue);
	CC_SYNTHESIZE(bool, istest, Istest);
	CC_SYNTHESIZE(int, count, Count);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, Hp_batchNode, Hp_BatchNode);
	Obstacle * _currentBird;
	Obstacle *_currentPenguin;

	virtual bool init();

	void createWorld();
	void update(float dt);
	void addHero();
	void createTrangle(float dt);
	void removeTrangle();
	void removePoint();
	void interval(float dt);
	void highSpeedSki(float dt);
	void genBackground();
	cocos2d::Sprite *Setthetexture1(cocos2d::Color4F c1, float textureWidth, float textureHeight);
	bool isCollision(cocos2d::Sprite * sp1, cocos2d::Sprite * sp2);
	void  ToPause(cocos2d::Ref* object);
	void ToResume(cocos2d::Ref* object);
	void ToHomeScene(cocos2d::Ref* object);
	void bgMove(float dt);
	void addSnowball(float dt);
	void reduceHp();
	void removeLabel();
	void addHp();

	void onEnter();
	void onExit();

	void onkeyBackClicked();
	void onkeyMenuClicked();

	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	void showResult(SpriteType type);
	void RemoveResult(cocos2d::Node * sender);
	
};


#endif
