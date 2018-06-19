#include"Obstacle.h"
#include "DataManager.h"
#define PTM_RATIO 32

Obstacle::Obstacle(ObstacleType spriteType, b2World * _world, CCLayer *_layer, CCPoint p)
{
	world = _world;
	point = p;
	layer = _layer;
	spType = spriteType;

	isContact = false;
	isFllow = false;
	this->setTag(333);
	switch (spriteType)
	{
	case obstacle_house:
		this->init_obstacle_house();
		break;

	case obstacle_bird:
		this->init_obstacle_bird();
		break;

	case obstacle_penguin:
		this->init_obstacle_penguin();
		break;

	case obstacle_guideboard:
		this->init_obstacle_guideboard();
		break;

	case obstacle_box:
		this->init_obstacle_box();
		break;

	case obstacle_gold:
		this->init_obstacle_gold();
		break;

	case obstacle_fire:
		this->init_obstacle_fire();
		break;
	case obstacle_snowball:
		this->init_obstacle_snowball();
		break;
	case obstacle_icepiton:
		this->init_obstacle_icepiton();
		break;

	case obstacle_xin:
		this->init_obstacle_xin();
		break;

	case obstacle_diamond:
		this->init_obstacle_diamond();
		break;


	default:
		break;
	}
}
//初始化心心
void Obstacle::init_obstacle_xin()				
{
	this->initWithFile("xin.png");

	this->setPosition(point);

	this->setScale(0.6f);
}
//初始化钻石
void Obstacle::init_obstacle_diamond()			
{
	this->initWithFile("diamond.png");

	this->setPosition(point);

	this->setScale(0.8f);
}

//初始化房子
void Obstacle::init_obstacle_house()			
{
	this->initWithFile("house.png");
	this->setScale(0.5f);
	this->setPosition(point);


	b2BodyDef houseBodyDef;
	houseBodyDef.type = b2_staticBody;
	houseBodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	houseBodyDef.userData = this;
	b2Body * houseBody = world->CreateBody(&houseBodyDef);
	Obstacle_body = houseBody;
	b2EdgeShape houseBox;

	houseBox.Set(b2Vec2(-51.0f / PTM_RATIO, 18.0f / PTM_RATIO), b2Vec2(0, 35.0f / PTM_RATIO));


	b2FixtureDef houseShape;
	houseShape.shape = &houseBox;
	houseShape.filter.groupIndex = -1;
	houseBody->CreateFixture(&houseShape);


}
//初始化冰块
void Obstacle::init_obstacle_icepiton()				
{
	this->initWithFile("ice.png");

	this->setPosition(point);

	this->setScale(0.35f);
}
//初始化鸟
void Obstacle::init_obstacle_bird()					
{


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bird.plist");
	CCDictionary * dic = CCDictionary::createWithContentsOfFile("bird.plist");
	CCDictionary * frameDic = (CCDictionary *)dic->objectForKey("frames");
	int num = frameDic->allKeys()->count();
	auto allFrames = Vector<SpriteFrame *>();
	for (int i = 0; i<num; i++)
	{
		char frame[15];
		sprintf(frame, "%i.png", i + 1);
		CCSpriteFrame * frameName = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame);
		allFrames.pushBack(frameName);
	}
	CCAnimation * animation = CCAnimation::createWithSpriteFrames(allFrames, 0.1f);
	CCAnimate * animate = CCAnimate::create(animation);
	this->initWithSpriteFrameName("1.png");
	this->setPosition(point);
	this->setScale(0.2f);
	this->runAction(CCRepeatForever::create(animate));


	b2BodyDef birdBodydef;
	birdBodydef.type = b2_dynamicBody;
	birdBodydef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	birdBodydef.userData = this;
	birdBodydef.fixedRotation = true;

	birdBody = world->CreateBody(&birdBodydef);
	Obstacle_body = birdBody;
	b2PolygonShape birdShape;
	b2Vec2 vertices[] =
	{
		b2Vec2(0, -5.0 / PTM_RATIO),
		b2Vec2(20.0 / PTM_RATIO, -7.0 / PTM_RATIO),
		b2Vec2(20.0 / PTM_RATIO, 5.0 / PTM_RATIO),
		b2Vec2(-20.0 / PTM_RATIO, 5.0 / PTM_RATIO)
	};

	birdShape.Set(vertices, 4);
	b2FixtureDef birdShapeDef;
	birdShapeDef.shape = &birdShape;
	birdShapeDef.density = 40.0f;
	birdShapeDef.friction = 1.0f;
	birdShapeDef.restitution = 0.2f;
	birdShapeDef.filter.groupIndex = -1;
	birdBody->CreateFixture(&birdShapeDef);

}

//初始化企鹅
void Obstacle::init_obstacle_penguin()			
{
	this->initWithFile("qie.png");

	this->setPosition(point);

	this->setScale(0.4f);


	b2BodyDef penguinBodydef;
	penguinBodydef.type = b2_dynamicBody;
	penguinBodydef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	penguinBodydef.userData = this;

	penguinBodydef.fixedRotation = true;
	penguinBodydef.bullet = true;
	penguinBody = world->CreateBody(&penguinBodydef);

	Obstacle_body = penguinBody;

	b2PolygonShape penguinShape;

	b2Vec2 vertices[] =

	{

		b2Vec2(0.0 / PTM_RATIO, -9.0 / PTM_RATIO),
		b2Vec2(0.0 / PTM_RATIO, 1.0 / PTM_RATIO),
		b2Vec2(3.0 / PTM_RATIO, -9.0 / PTM_RATIO),
		b2Vec2(3.0 / PTM_RATIO, 1.0 / PTM_RATIO)

	};

	penguinShape.Set(vertices, 4);

	b2FixtureDef penguinShapeDef;

	penguinShapeDef.filter.groupIndex = -1;

	penguinShapeDef.shape = &penguinShape;
	penguinShapeDef.density = 50.0f;
	penguinShapeDef.friction = 0.15f;
	penguinShapeDef.restitution = 0.0f;
	penguinBody->CreateFixture(&penguinShapeDef);


}

//初始化路牌
void Obstacle::init_obstacle_guideboard()			
{
	this->initWithFile("lubiao.png");
	this->setPosition(point);
	this->setScale(0.4f);
	CCPoint p = this->getContentSize();

	char tep[20];
	sprintf(tep, "%im", DataManager::getInstance()->_currentDistance);
	CCLabelTTF * label = CCLabelTTF::create(tep, "", 60);
	label->setPosition(ccp(p.x / 2, p.y / 2 + 80));
	label->setColor(ccc3(0, 0, 0));
	this->addChild(label);

	b2BodyDef guideboardBodyDef;
	guideboardBodyDef.type = b2_kinematicBody;
	guideboardBodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	guideboardBodyDef.userData = this;
	b2Body * guideboardBody = world->CreateBody(&guideboardBodyDef);
	Obstacle_body = guideboardBody;
	b2EdgeShape guideboardBox;
	guideboardBox.Set(b2Vec2(-40.0f / PTM_RATIO, 40.0f / PTM_RATIO), b2Vec2(40.0f / PTM_RATIO, 40.0f / PTM_RATIO));

	b2FixtureDef guideboardShape;
	guideboardShape.shape = &guideboardBox;
	guideboardShape.filter.groupIndex = -1;
	guideboardBody->CreateFixture(&guideboardShape);

}
//初始化箱子
void Obstacle::init_obstacle_box()				
{
	this->initWithFile("box.png");
	this->setPosition(point);

	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_staticBody;
	boxBodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	boxBodyDef.userData = this;
	b2Body * boxBody = world->CreateBody(&boxBodyDef);
	Obstacle_body = boxBody;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(28.0f / (PTM_RATIO * 2), 28.0f / (PTM_RATIO * 2));


	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &boxShape;
	boxShapeDef.density = 3.0f;
	boxShapeDef.friction = 1.0f;
	boxShapeDef.restitution = 0.0f;
	boxShapeDef.filter.groupIndex = -1;
	boxBody->CreateFixture(&boxShapeDef);

}

//初始化黄金
void Obstacle::init_obstacle_gold()				
{
	this->initWithFile("xiutu.png");
	this->setScale(0.8f);
	this->setPosition(point);

}
//初始化雪球
void Obstacle::init_obstacle_snowball()			
{
	this->initWithFile("snowball.png");
	this->setScale(0.5f);
	this->setPosition(point);

	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	ballBodyDef.userData = this;
	ballBodyDef.fixedRotation = false;
	ballBody = world->CreateBody(&ballBodyDef);
	Obstacle_body = ballBody;

	b2CircleShape ballShap;
	ballShap.m_radius = 38.0f / PTM_RATIO;

	b2FixtureDef snowballShapeDef;
	snowballShapeDef.shape = &ballShap;
	snowballShapeDef.density = 100.0f;
	snowballShapeDef.friction = 0.1f;
	snowballShapeDef.restitution = 0.0f;
	snowballShapeDef.filter.groupIndex = -1;
	ballBody->CreateFixture(&snowballShapeDef);


}
//初始化火
void Obstacle::init_obstacle_fire()			
{
	this->initWithFile("fire.png");
	this->setScale(0.7f);
	this->setPosition(point);
}
//雪球滚动
void Obstacle::ballRoll()					
{
	ballBody->ApplyLinearImpulse(b2Vec2(50.0f, -5.0f), ballBody->GetPosition(),false);

}
//黄金动画
void Obstacle::goldAnimation()				
{

	CCSprite * sprite = CCSprite::create("xitu.png");
	sprite->setScale(0.8f);
	sprite->setPosition(point);
	layer->addChild(sprite);

	CCScaleTo * scaleTo = CCScaleTo::create(0.1f, 1.2f);
	CCScaleTo * toScale = CCScaleTo::create(0.2f, 0.5f);
	CCCallFuncN * funcN = CCCallFuncN::create(this, callfuncN_selector(Obstacle::RemoveAnimation));
	CCSequence * seq = CCSequence::create(scaleTo, toScale, funcN, NULL);
	sprite->runAction(seq);
}


//移除精灵
void Obstacle::RemoveAnimation(CCNode * sender)			
{
	CCSprite * sp = (CCSprite *)sender;
	sp->removeFromParent();
}
//箱子动画
void Obstacle::boxAnimation()						
{

	for (int i = 0; i<5; i++)
	{
		int random = rand() % 5 + 1;
		int range = 15;

		char t[30];
		sprintf(t, "box%d.png", random);
		CCSprite *temp = CCSprite::create(t);

		temp->setScale((float)(rand() % 5 / 10.1 + 0.5f));

		temp->setPosition(CCPointMake(this->getPosition().x + rand() % 10 * range - 20, this->getPosition().y + rand() % 10 * range - 10));
		CCMoveTo *actionMove = CCMoveTo::create(1.0f, CCPointMake(this->getPosition().x + rand() % 10 * range - 20, this->getPosition().y + rand() % 10 * range - 10));

		CCFadeOut *actionAlpha = CCFadeOut::create(1.0f);
		CCCallFuncN *actionMoveEnd = CCCallFuncN::create(this, callfuncN_selector(Obstacle::RemoveAnimation));
		CCRotateTo *actionRotate = CCRotateTo::create(1.0f, rand() % 180);
		CCSpawn *mut = CCSpawn::create(actionMove, actionAlpha, actionRotate, NULL);
		CCSequence *seq = CCSequence::create(mut, actionMoveEnd, NULL);
		temp->runAction(seq);

		layer->addChild(temp);
	}


}
//小鸟飞行
void Obstacle::BirdFlay()						
{

	birdBody->SetLinearVelocity(b2Vec2(13, 0.5));

}
//企鹅滑雪速度
void Obstacle::_obstacleskiSpeed1()				

{
	penguinBody->ApplyLinearImpulse(b2Vec2(0.035f, -0.05f), penguinBody->GetPosition(),false);
}
//创建关节
void Obstacle::createJoin(b2Body * body1, b2Body * body2)			
{
	b2DistanceJointDef jointDef;
	jointDef.Initialize(body1, body2, body1->GetWorldCenter(), body2->GetWorldCenter());
	jointDef.collideConnected = true;
	world->CreateJoint(&jointDef);

}