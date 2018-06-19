#include "GameScene.h"
#include "GLES-Render.h"
#include "MyTerrain.h"
#include "MyContactListener.h"
#include "Obstacle.h"
#include "DataManager.h"
#include "Hero.h"
#include "StartGame.h"
#include "GameOver.h"
#define PTM_RATIO 32

USING_NS_CC;

int timer = 0;
int timer1 = 0;
int timeTrip = 0;
int total = 0;

CCScene* GameScene::scene()
{
	CCScene* scene = CCScene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
GameScene::GameScene() :
isHighSpeed(false),
count(0)
{

}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getWinSize();

	bgSprite1 = Sprite::create("background1.png");
	bgSprite1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bgSprite1->setScale(0.5);
	this->addChild(bgSprite1,-1);
	
	bgSprite2 = Sprite::create("background2.png");
	bgSprite2->setPosition(Vec2(winSize.width / 2 + winSize.width, winSize.height / 2));
	bgSprite2->setScale(0.5);
	this->addChild(bgSprite2,-1);

	this->createWorld();
	return true;
}

//设置地形纹理
void GameScene::genBackground()		
{

	auto stripes = this->Setthetexture1(ccc4FFromccc4B(Color4B(255, 255, 255, 100)), 512, 512);			//绘制地形精灵
    Texture2D::TexParams tp2 = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };//GL_CLAMP_TO_EDGE   GL_NEAREST  GL_LINEAR
	stripes->getTexture()->setTexParameters(&tp2);
	_terrain->setStripes(stripes);
}

//设置纹理颜色
Sprite * GameScene::Setthetexture1(cocos2d::Color4F c1, float textureWidth, float textureHeight)
{

	CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);


	rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);


	this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));		//kCCShader_PositionColor


	float gradientAlpha = 0.7f;
	CCPoint vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;

	vertices[nVertices] = CCPointMake(0, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	vertices[nVertices] = CCPointMake(textureWidth, 0);
	colors[nVertices++] = ccc4f(0, 0, 0, 0);
	vertices[nVertices] = CCPointMake(0, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
	vertices[nVertices] = CCPointMake(textureWidth, textureHeight);
	colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);

	rt->end();


	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

//创建世界
void GameScene::createWorld()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	MyContactListener* listener = new MyContactListener(world, this);
	world->SetContactListener(listener);

}


void GameScene::update(float dt)
{
	//碰撞黄金后更新数据
	CCArray * RMgoldArray = CCArray::create();
	for (int i = 0; i < int(_terrain->goldArray->count()); i++)
	{
		Obstacle *spr = (Obstacle*)_terrain->goldArray->objectAtIndex(i);
		if (isCollision(hero, spr))			
		{
			this->showResult(Sprite_gold);

			RMgoldArray->addObject(spr);
			spr->goldAnimation();
			total += 10;
			_terrain->getBatchNode5()->removeChild(spr, false);
		}

	}
	//从数组中移除碰撞黄金
	for (int i = 0; i < int(RMgoldArray->count()); i++)
	{
		Obstacle *spr = (Obstacle *)RMgoldArray->objectAtIndex(i);
		_terrain->goldArray->removeObject(spr);

	}
//	RMgoldArray->release();
	//限制黄金数量
	if (_terrain->goldArray->count()>20)
	{
		CCSprite * sp = (CCSprite *)_terrain->goldArray->objectAtIndex(0);
		_terrain->getBatchNode5()->removeChild(sp, false);
		_terrain->goldArray->removeObjectAtIndex(0);

	}

	//碰撞钻石后更新数据
	CCArray * RMdiamondArray = CCArray::create();
	for (int i = 0; i < int(_terrain->diamondArray->count()); i++)
	{
		Obstacle *spr = (Obstacle*)_terrain->diamondArray->objectAtIndex(i);
		if (isCollision(hero, spr))
		{
			this->showResult(Sprite_diamond);

			RMdiamondArray->addObject(spr);

			total += 50;
			_terrain->getBatchNode12()->removeChild(spr, false);
		}

	}
	for (int i = 0; i < int(RMdiamondArray->count()); i++)
	{
		Obstacle *spr = (Obstacle *)RMdiamondArray->objectAtIndex(i);
		_terrain->diamondArray->removeObject(spr);

	}
//	RMdiamondArray->release();

	if (_terrain->diamondArray->count()>20)
	{
		CCSprite * sp = (CCSprite *)_terrain->diamondArray->objectAtIndex(0);
		_terrain->getBatchNode12()->removeChild(sp, false);
		_terrain->diamondArray->removeObjectAtIndex(0);

	}


	//碰撞心心后更新数据
	CCArray * RMxinArray = CCArray::create();
	for (int i = 0; i < int(_terrain->xinArray->count()); i++)
	{
		Obstacle *spr = (Obstacle*)_terrain->xinArray->objectAtIndex(i);
		if (isCollision(hero, spr))
		{

			this->showResult(Sprite_xin);

			RMxinArray->addObject(spr);
			this->addHp();
			_terrain->getBatchNode11()->removeChild(spr, false);
		}

	}
	for (int i = 0; i < int(RMxinArray->count()); i++)
	{
		Obstacle *spr = (Obstacle *)RMxinArray->objectAtIndex(i);
		_terrain->xinArray->removeObject(spr);

	}
//	RMxinArray->release();

	if (_terrain->xinArray->count()>4)
	{
		CCSprite * sp = (CCSprite *)_terrain->xinArray->objectAtIndex(0);
		_terrain->getBatchNode11()->removeChild(sp, false);
		_terrain->xinArray->removeObjectAtIndex(0);

	}




	//碰撞冰块后更新数据
	CCArray * RMHpArray = CCArray::create();
	for (int i = 0; i < int(_terrain->icepitonArray->count()); i++)
	{
		Obstacle *spr = (Obstacle*)_terrain->icepitonArray->objectAtIndex(i);
		if (isCollision(hero, spr))
		{

			RMHpArray->addObject(spr);
			this->reduceHp();

			hero->jump();

			CCSprite * hp_spr = (CCSprite *)HpArray->objectAtIndex(HpArray->count() - 1);
			Hp_batchNode->removeChild(hp_spr, false);
			HpArray->removeObject(hp_spr);

			_terrain->getBatchNode10()->removeChild(spr, false);
		}

	}

	for (int i = 0; i < int(RMHpArray->count()); i++)
	{
		Obstacle *spr = (Obstacle *)RMHpArray->objectAtIndex(i);
		_terrain->icepitonArray->removeObject(spr);

	}
//	RMHpArray->release();


	if (_terrain->icepitonArray->count()>2)
	{
		CCSprite * sp = (CCSprite *)_terrain->icepitonArray->objectAtIndex(0);
		_terrain->getBatchNode10()->removeChild(sp, false);
		_terrain->icepitonArray->removeObjectAtIndex(0);

	}



	//碰撞火焰后更新数据
	CCArray* RMfireArray = CCArray::create();
	for (int i = 0; i <int(_terrain->fireArray->count()); i++)
	{
		Obstacle *spr = (Obstacle*)_terrain->fireArray->objectAtIndex(i);
		if (isCollision(hero, spr))
		{
			this->showResult(Sprite_fire);

			RMfireArray->addObject(spr);
			isHighSpeed = true;
			this->schedule(schedule_selector(GameScene::highSpeedSki), 0.2f);
			_terrain->removeChild(spr, false);

		}

	}

	for (int i = 0; i <int(RMfireArray->count()); i++)
	{
		Obstacle *spr = (Obstacle *)RMfireArray->objectAtIndex(i);
		_terrain->fireArray->removeObject(spr);

	}
//	RMfireArray->release();

	if (_terrain->fireArray->count()>2)
	{
		CCSprite * sp = (CCSprite *)_terrain->fireArray->objectAtIndex(0);
		_terrain->removeChild(sp, false);
		_terrain->fireArray->removeObjectAtIndex(0);

	}





	int velocityIterations = 8;
	int positionIterations = 1;

	hero->skiSpeed();			//主角每秒加速
	if (hero->_myBody->GetLinearVelocity().x>20 && !isHighSpeed)
	{

		hero->limitVelocity();		//限制主角最大速度
	}

	world->Step(dt, velocityIterations, positionIterations);			//更新物理世界
	b2Body* node = world->GetBodyList();
	while (node)				//同步刚体和精灵的位置
	{
		b2Body* body = node;
		node = node->GetNext();
		if (body->GetUserData() != NULL)
		{
			Sprite* sprite = (Sprite*)body->GetUserData();
			sprite->setPosition(Vec2(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));

			Sprite * sp = (Sprite*)body->GetUserData();
			if (sp->getTag() == 333)				//障碍物
			{
				Obstacle * obstacle_sp = (Obstacle*)sp;

				if (obstacle_sp->spType == obstacle_box)
				{
					if (obstacle_sp->isContact)				//连接了箱子
					{
						_terrain->getBatchNode6()->removeChild(obstacle_sp, false);
						world->DestroyBody(obstacle_sp->Obstacle_body);
						obstacle_sp->isContact = false;
						_terrain->boxArray->removeObject(obstacle_sp);
					}
					if (_terrain->boxArray->count()>3)				//限制箱子数量
					{
						Obstacle * ob = (Obstacle *)_terrain->boxArray->objectAtIndex(0);
						_terrain->getBatchNode6()->removeChild(ob, false);
						world->DestroyBody(ob->Obstacle_body);
						_terrain->boxArray->removeObjectAtIndex(0);
					}

				}

				else if (obstacle_sp->spType == obstacle_house)			//限制房子数量
				{
					if (_terrain->houseArray->count()>2)
					{
						Obstacle * ob = (Obstacle *)_terrain->houseArray->objectAtIndex(0);
						_terrain->getBatchNode8()->removeChild(ob, false);
						world->DestroyBody(ob->Obstacle_body);
						_terrain->houseArray->removeObjectAtIndex(0);
					}
				}


				else if (obstacle_sp->spType == obstacle_guideboard)	//限制路牌数量
				{
					if (_terrain->guideboardArray->count()>2)
					{
						Obstacle * ob = (Obstacle *)_terrain->guideboardArray->objectAtIndex(0);
						_terrain->removeChild(ob, false);
						world->DestroyBody(ob->Obstacle_body);
						_terrain->guideboardArray->removeObjectAtIndex(0);
					}
				}

				else if (obstacle_sp->spType == obstacle_snowball)	//限制雪球数量
				{
					obstacle_sp->ballRoll();
					if (_terrain->snowBallArray->count()>2)
					{
						Obstacle * sp = (Obstacle *)_terrain->snowBallArray->objectAtIndex(0);
						_terrain->removeChild(sp, false);
						world->DestroyBody(sp->Obstacle_body);
						_terrain->snowBallArray->removeObjectAtIndex(0);
					}
				}

				else if (obstacle_sp->spType == obstacle_bird)		//限制鸟数量
				{
					obstacle_sp->BirdFlay();

					if (_terrain->birdArray->count()>5)
					{
						Obstacle * sp = (Obstacle *)_terrain->birdArray->objectAtIndex(0);
						_terrain->removeChild(sp, false);
						world->DestroyBody(sp->Obstacle_body);
						_terrain->birdArray->removeObjectAtIndex(0);

					}

				}

				else if (obstacle_sp->spType == obstacle_penguin)
				{
					
					if (obstacle_sp->ispenguinContace == true)		//连接企鹅
					{
						obstacle_sp->_obstacleskiSpeed1();
						if (istest == true)		//可以连接状态
						{
							
							istest = false;
							obstacle_sp->createJoin(hero->_myBody, obstacle_sp->penguinBody);
							_currentPenguin = obstacle_sp;

						}

					}
					if (_terrain->penguinArray->count()>3)			//限制企鹅数量
					{

						Obstacle * ob = (Obstacle *)_terrain->penguinArray->objectAtIndex(0);

						if (ob == _currentPenguin)

						{

							Obstacle * op = (Obstacle *)_terrain->penguinArray->objectAtIndex(1);
							_terrain->getBatchNode9()->removeChild(op, false);
							world->DestroyBody(op->Obstacle_body);
							_terrain->penguinArray->removeObjectAtIndex(1);
						}
						else
						{

							_terrain->getBatchNode9()->removeChild(ob, false);
							world->DestroyBody(ob->Obstacle_body);
							_terrain->penguinArray->removeObjectAtIndex(0);
						}

					}

				}


			}

		}
		world->ClearForces();				//清除力量
	}

	count++;
	if (count % 600 == 0 && !istest)			//连接企鹅时间
	{
		count = 0;
		istest = true;
		_terrain->getBatchNode9()->removeChild(_currentPenguin, false);
		world->DestroyBody(_currentPenguin->Obstacle_body);

		_terrain->penguinArray->removeObject(_currentPenguin);

	}


	hero->update(dt);			//更新主角刚体及位置


	float offset = hero->getPosition().x;
	DataManager::getInstance()->_currentDistance = offset / 32;



	if (hero->_myBody->GetLinearVelocity().x<2)				//根据时间距离添加雪球
	{
		timeTrip++;
		float time;
		if (timeTrip > 10)
		{
			if (DataManager::getInstance()->_currentDistance>0 && DataManager::getInstance()->_currentDistance <= 1000)
			{
				time = 6;
			}
			else if (DataManager::getInstance()->_currentDistance>1000 && DataManager::getInstance()->_currentDistance <= 2000)
			{
				time = 5;
			}
			else if (DataManager::getInstance()->_currentDistance>2000)
			{
				time = 4;
			}
			//this->scheduleOnce(schedule_selector(GameScene::addSnowball), time);
			timeTrip = 0;
		}
	}

	DataManager::getInstance()->_currentScore = DataManager::getInstance()->_currentDistance + total;
	char temp[20];
	sprintf(temp, "%i", DataManager::getInstance()->_currentScore);
	_distance->setString(temp);
	_terrain->setOffsetX(offset);				//地形偏移，移动

	if (hero->isEnd || !HpArray->count())
	{
		int a = CCUserDefault::sharedUserDefault()->getIntegerForKey("Seventh");
		if (CCUserDefault::sharedUserDefault()->getIntegerForKey("First") <= a)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("First", DataManager::getInstance()->_currentScore);
		}
		else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Second") <= a)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("Second", DataManager::getInstance()->_currentScore);
		}
		else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Third") <= a)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("Third", DataManager::getInstance()->_currentScore);
		}
		else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Fourth") <= a)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("Fourth", DataManager::getInstance()->_currentScore);
		}
		else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Fivth") <= a)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("Fivth", DataManager::getInstance()->_currentScore);
		}
		else if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Sixth") <= a)
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("Sixth", DataManager::getInstance()->_currentScore);
		}
		total = 0;
		DataManager::getInstance()->isBlink = true;
		CCDirector::sharedDirector()->replaceScene(GameOver::scene());
	}

}

//添加雪球
void GameScene::addSnowball(float dt)
{
	_terrain->snowBallRoll(ccp(hero->getPositionX() - 140, hero->getPositionY() + 10));
	_terrain->snowBallRoll(ccp(hero->getPositionX() - 160, hero->getPositionY() + 10));
}
//背景移动
void GameScene::bgMove(float dt)
{
	newNum = hero->getPositionX();
	if (newNum > oldNum)
	{
		oldNum = newNum;
		newNum = 0;
		if (bgSprite1->getPositionX() == winSize.width / 2)
		{
			bgSprite2->setPosition(ccp(winSize.width / 2 + winSize.width, winSize.height / 2));
			CCMoveTo* moveTo1 = CCMoveTo::create(15, ccp(-winSize.width / 2, winSize.height / 2));
			CCMoveTo* moveTo2 = CCMoveTo::create(15, ccp(winSize.width / 2, winSize.height / 2));
			bgSprite1->runAction(moveTo1);
			bgSprite2->runAction(moveTo2);
		}
		if (bgSprite2->getPositionX() == winSize.width / 2)
		{
			bgSprite1->setPosition(ccp(winSize.width / 2 + winSize.width, winSize.height / 2));
			CCMoveTo* moveTo1 = CCMoveTo::create(15, ccp(-winSize.width / 2, winSize.height / 2));
			CCMoveTo* moveTo2 = CCMoveTo::create(15, ccp(winSize.width / 2, winSize.height / 2));
			bgSprite1->runAction(moveTo2);
			bgSprite2->runAction(moveTo1);
		}
	}
}
//减少HP
void GameScene::reduceHp()
{
	CCLabelTTF * label = CCLabelTTF::create("-1", "", 30);
	label->setPosition(hero->getPosition());
	label->setTag(116);
	label->setColor(ccc3(255, 0, 0));
	_terrain->addChild(label);
	CCJumpBy * jump = CCJumpBy::create(0.5, ccp(50, 0), 50, 1);
	CCCallFunc * fun = CCCallFunc::create(this, callfunc_selector(GameScene::removeLabel));
	CCSequence * seq = CCSequence::create(jump, CCDelayTime::create(1.0f), fun, NULL);
	label->runAction(seq);
}

//增加HP
void GameScene::addHp()
{
	if (HpArray->count()<3)
	{
		auto Hp_sprite = Sprite::create("xin.png");
		if (HpArray->count() == 1)
		{
			Hp_sprite->setPosition(Vec2(90 + 22, winSize.height - 40));
		}
		else
		{
			Hp_sprite->setPosition(Vec2(90 + 44, winSize.height - 40));
		}
		Hp_sprite->setScale(0.6f);
		Hp_batchNode->addChild(Hp_sprite);
		HpArray->addObject(Hp_sprite);
	}
}

//快速移动
void GameScene::highSpeedSki(float dt)
{

	hero->highSpeed();
	timer1++;
	if (timer1 == 12)
	{
		this->unschedule(schedule_selector(GameScene::highSpeedSki));
		timer1 = 0;
		isHighSpeed = false;
	}
}

//添加主角
void GameScene::addHero()
{

	hero = Hero::createHero();
	hero->initHero(Vec2(50, 180), world);
	_terrain->getBatchNode()->addChild(hero);
	this->scheduleUpdate();
}





//创建trangle
void GameScene::createTrangle(float dt)
{
	CCSprite* follow;
	CCCallFunc* fun;
	if (!(hero->isFly))
	{
		follow = CCSprite::create("trangle.png");
		_terrain->getBatchNode2()->addChild(follow);
		follow->setTag(123);
		fun = CCCallFunc::create(this, callfunc_selector(GameScene::removeTrangle));
	}
	else
	{
		follow = CCSprite::create("point.png");
		_terrain->getBatchNode3()->addChild(follow);
		follow->setTag(456);
		fun = CCCallFunc::create(this, callfunc_selector(GameScene::removePoint));
	}
	follow->setPosition(ccp(hero->getPositionX() - 5, hero->getPositionY() - 13));

	CCScaleBy* scaleBy = CCScaleBy::create(0.2f, 0.5f);
	CCSequence* seq = CCSequence::create(scaleBy, fun, NULL);
	follow->runAction(seq);

	if (isHighSpeed)
	{
		CCParticleSystemQuad* mSystem = CCParticleSystemQuad::create("myfire.plist");
		mSystem->setTextureWithRect(CCTextureCache::sharedTextureCache()->addImage("fire2.png"), CCRectMake(0, 0, 30, 20));
		mSystem->setBlendAdditive(true);
		mSystem->setPosition(ccp(hero->getPositionX(), hero->getPositionY() + 10));
		mSystem->setDuration(0.005f);
		_terrain->getBatchNode4()->addChild(mSystem);
		mSystem->setAutoRemoveOnFinish(true);

	}
}

void GameScene::removeTrangle()
{
	_terrain->getBatchNode2()->removeChildByTag(123);
}


void GameScene::removePoint()
{
	_terrain->getBatchNode3()->removeChildByTag(456);
}
void GameScene::removeLabel()
{
	_terrain->removeChildByTag(116);
}

//是否碰撞
bool GameScene::isCollision(Sprite * sp1, Sprite * sp2)
{
	CCRect rect1 = sp1->boundingBox();
	CCRect rect2 = sp2->boundingBox();
	return rect1.intersectsRect(rect2);
}

//暂停游戏
void  GameScene::ToPause(Ref* object)
{
	if (!isPause)
	{
		isPause = true;
		Director::getInstance()->pause();

		auto PauseItem = MenuItemImage::create("resume_btn.png", "resume_btn.png");
		PauseItem->setTarget(this, menu_selector(GameScene::ToResume));
		PauseItem->setScale(0.5f);
		auto PauseMenu = Menu::create(PauseItem, NULL);
		PauseMenu->setTag(131);
		PauseMenu->setPosition(Vec2(winSize.width / 2 + 180, winSize.height / 2 + 10));
		auto scaleToBig = ScaleTo::create(2.0f, 0.6f);
		auto scaleToSmall = ScaleTo::create(2.0f, 0.4f);
		auto seq = Sequence::create(scaleToBig, scaleToSmall, NULL);
		PauseItem->runAction(RepeatForever::create(seq));
		this->addChild(PauseMenu, 30);

		auto BackItem = MenuItemImage::create("home_btn.png", "home_btn.png");
		BackItem->setScale(0.55f);
		BackItem->setTarget(this, menu_selector(GameScene::ToHomeScene));
		auto BackMenu = Menu::create(BackItem, NULL);
		BackMenu->setTag(132);
		BackMenu->setPosition(Vec2(winSize.width - 60, winSize.height / 2 - 90));
		this->addChild(BackMenu, 30);
	}
}
//回复游戏
void GameScene::ToResume(CCObject* object)
{
	this->removeChildByTag(131);
	this->removeChildByTag(132);
	Director::getInstance()->resume();
	isPause = false;
}

//返回主界面
void GameScene::ToHomeScene(CCObject* object)
{
	CCDirector::sharedDirector()->replaceScene(StartGame::create());
}
//进入游戏场景后，
void GameScene::onEnter()
{
	Layer::onEnter();


	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	touch->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
	dispatcher->addEventListenerWithSceneGraphPriority(touch,this);

	auto disLab = LabelTTF::create("Score:", "Arial", 25);
	disLab->setColor(ccc3(255, 255, 0));
	disLab->setPosition(Vec2(winSize.width / 2 + 120, winSize.height - 40));
	this->addChild(disLab, 2);


	_distance = LabelTTF::create("0", "Arial", 25);
	_distance->setColor(ccc3(125, 255, 0));
	_distance->setPosition(Vec2(winSize.width - 50, winSize.height - 40));
	this->addChild(_distance, 2);

	auto HpLabel = LabelTTF::create("Hp:", "Arial", 25);
	HpLabel->setColor(ccc3(255, 255, 0));
	HpLabel->setPosition(Vec2(60, winSize.height - 40));
	this->addChild(HpLabel, 2);
	Hp_batchNode = CCSpriteBatchNode::create("xin.png");
	this->addChild(Hp_batchNode);

	HpArray = CCArray::create();
	HpArray->retain();
	for (int i = 0; i < 3; i++)
	{
		auto Hp_sprite = Sprite::create("xin.png");
		Hp_sprite->setPosition(Vec2(90 + 22 * i, winSize.height - 40));
		Hp_sprite->setScale(0.6f);
		Hp_batchNode->addChild(Hp_sprite);
		HpArray->addObject(Hp_sprite);

	}

	_terrain = MyTerrain::createWithWorld(world);
	node = CCNode::create();
	node->addChild(_terrain,1);
	node->setScale(0.8f);
	node->setRotation(15);
	this->addChild(node, 1);

	isPause = false;

	auto PauseSprite = MenuItemImage::create("pause_btn.png", "pause_btn.png");
	PauseSprite->setTarget(this, menu_selector(GameScene::ToPause));
	auto PauseMenu = Menu::create(PauseSprite, NULL);
	PauseMenu->setPosition(Vec2(winSize.width / 2 + 180, winSize.height - 80));
	this->addChild(PauseMenu);

	this->genBackground();

	auto PariticleSnow = ParticleSnow::create();
	PariticleSnow->setScale(1.2f);
	PariticleSnow->setPosition(ccp(winSize.width / 2 - 40, winSize.height));
	PariticleSnow->setSpeed(10);
	PariticleSnow->setBlendAdditive(true);
	this->addChild(PariticleSnow);
	PariticleSnow->setAutoRemoveOnFinish(true);

	oldNum = 0;
	newNum = 0;
	isContinue = true;
	istest = true;
	this->addHero();
	this->schedule(schedule_selector(GameScene::createTrangle), 0.05f);
	this->schedule(schedule_selector(GameScene::bgMove), 0.1f);


}
void GameScene::onExit()
{
//	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	this->unscheduleAllSelectors();
	Layer::onExit();
}

//主角站立
void GameScene::interval(float dt)
{
	timer++;
	if (timer>5)
	{
		hero->standSpeed();
	}
}
//触摸开始，长按主角站立
bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{

	this->schedule(schedule_selector(GameScene::interval), 0.1f);

	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{


}

//触摸结束，主角跳跃
void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	if (!hero->isFly && timer < 5)
	{
		hero->isFly = true;
		hero->flySpeed();
	}
	timer = 0;
	this->unschedule(schedule_selector(GameScene::interval));

}

void GameScene::onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{

}
//显示结果
void GameScene::showResult(SpriteType type)		
{
	Sprite * sp;
	LabelTTF * label;
	switch (type)
	{
	case Sprite_gold:
		sp = Sprite::create("xiutu.png");
		label = LabelTTF::create("X 10", "", 20);
		sp->setScale(0.7f);
		break;
	case Sprite_diamond:
		sp = Sprite::create("diamond.png");
		label = LabelTTF::create("X 50", "", 20);
		sp->setScale(0.7f);
		break;
	case Sprite_fire:
		sp = Sprite::create("fire.png");
		label = LabelTTF::create("X 1", "", 20);
		sp->setScale(0.7f);
		break;
	case Sprite_xin:
		sp = Sprite::create("xin.png");
		label = LabelTTF::create("X 1", "", 20);
		sp->setScale(0.6f);
		break;
	default:
		break;
	}
	sp->setPosition(Vec2(winSize.width / 2 - 20, winSize.height - 40));

	label->setPosition(Vec2(winSize.width / 2 + 20, winSize.height - 40));
	label->setColor(ccc3(255, 0, 0));
	this->addChild(sp);
	this->addChild(label);

	auto Spfun = CallFuncN::create(this, callfuncN_selector(GameScene::RemoveResult));
	auto SpSeq = Sequence::create(DelayTime::create(0.1f), Spfun, NULL);
	sp->runAction(SpSeq);

	auto Labelfun = CallFuncN::create(this, callfuncN_selector(GameScene::RemoveResult));
	auto * LabelSeq = Sequence::create(DelayTime::create(0.1f), Labelfun, NULL);
	label->runAction(LabelSeq);

}
//移除结果
void GameScene::RemoveResult(CCNode * sender)
{
	sender->removeFromParent();
}

//退出菜单
void GameScene::onkeyBackClicked()
{
	auto back = BackMenu::getInstance();
	if (back->getIsShow() == false)
	{
		back->showBackMenu(this);
	}
	else
	{
		back->backToGame(nullptr);
	}
}

void GameScene::onkeyMenuClicked()
{


}



