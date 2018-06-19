#include "Hero.h"
#define PTM_RATIO 32

Hero* Hero::createHero()
{
	Hero* hero = new Hero();
	if (hero)
	{
		return hero;
	}
	return NULL;
}


void Hero::initHero(CCPoint p, b2World* world)				//��ʼ������
{
	float x = p.x;
	float y = p.y;
	_myWorld = world;
	isFly = false;
	isEnd = false;
	_nextVel = 0;
	memset(_preVels, 0, NUM_PREV_VELS *sizeof(b2Vec2));
	this->initWithFile("hero.png");
	this->setPosition(Vec2(x, y));

	this->setScale(0.3f);
	this->setTag(HERO_ID);



	if (world != NULL)
	{
		CCLOG("create body");

		//�����Ǵ�������
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);
		ballBodyDef.userData = this;
		ballBodyDef.fixedRotation = true;	//�̶���ת
		ballBodyDef.bullet = true;
		b2Body* ballBody = world->CreateBody(&ballBodyDef);
		_myBody = ballBody;

		b2PolygonShape blockShape;
		blockShape.SetAsBox(30.0 / (PTM_RATIO * 2), 30.0 / (PTM_RATIO * 2));

		b2FixtureDef ballshapDef;
		ballshapDef.shape = &blockShape;
		ballshapDef.density = 36.0f;
		ballshapDef.friction = 0.1f;
		ballshapDef.restitution = 0.0f;
		ballshapDef.filter.groupIndex = 1;
		ballBody->CreateFixture(&ballshapDef);
	}

}
//���ٻ�ѩ
void Hero::skiSpeed()			
{
	if (isFly == false)
	{
		_myBody->ApplyLinearImpulse(b2Vec2(2.0f, 0.7f), _myBody->GetPosition(),true);		//������������

	}

}

void Hero::flySpeed()			//����
{
	_myBody->SetLinearVelocity(b2Vec2(_myBody->GetLinearVelocity().x, 7.5f));				//������������
	isFly = true;
}
//����վ��
void Hero::standSpeed()			
{
	_myBody->ApplyLinearImpulse(b2Vec2(8.0f, 5.0f), _myBody->GetPosition(),true);
}

void Hero::highSpeed()				//�����ƶ�
{
	_myBody->SetLinearVelocity(b2Vec2(20.0f, 0.0f));
}
void Hero::jump()					//��Ծ
{
	_myBody->ApplyLinearImpulse(b2Vec2(0.0f, 90.0f), _myBody->GetPosition(),true);

}

void Hero::update(float dt)			//���ݸ����������λ�ü��Ƕ�
{
	this->setPosition(ccp(_myBody->GetPosition().x * PTM_RATIO, _myBody->GetPosition().y * PTM_RATIO));
	b2Vec2 vel = _myBody->GetLinearVelocity();
	b2Vec2 weightedVel = vel;

	for (int i = 0; i < NUM_PREV_VELS; ++i)
	{
		weightedVel += _preVels[i];

	}
	weightedVel = b2Vec2(weightedVel.x / NUM_PREV_VELS, weightedVel.y / NUM_PREV_VELS);		//ƽ���ٶ�
	_preVels[_nextVel++] = vel;
	if (_nextVel >= NUM_PREV_VELS)
	{
		_nextVel = 0;
	}

	float angle = 0;
	if (weightedVel.x > 0.0000000001 && weightedVel.y > 0.0000000001)
	{
		angle = ccpToAngle(ccp(weightedVel.x, weightedVel.y));
		this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
	}

	if (isFly)
	{
		if (this->getPositionY()>400)
		{
			_myBody->ApplyForce(b2Vec2(0.0f, -500.0f), _myBody->GetPosition(),true);     //����������������
		}
	}

}
void Hero::limitVelocity()						//�����ٶ�

{
	const float minVelocityX = 20;
	const float minVelocityY = -40;
	b2Vec2 vel = _myBody->GetLinearVelocity();
	if (vel.x > minVelocityX)
	{
		vel.x = minVelocityX;
	}
	if (vel.y < minVelocityY)
	{
		vel.y = minVelocityY;
	}
	_myBody->SetLinearVelocity(vel);
}
