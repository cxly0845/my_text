#include "MyTerrain.h"
#include "Obstacle.h"
#include "DataManager.h"
#define PTM_RATIO 32
using namespace cocos2d;



MyTerrain::MyTerrain(void)
{

	_stripes = NULL;
	_offsetX = 0;
	_fromKeyPointI = 0;
	_toKeyPointI = 0;
	_world = NULL;
	_body = NULL;

	boxArray = CCArray::create();
	boxArray->retain();

	houseArray = CCArray::create();
	houseArray->retain();

	goldArray = CCArray::create();
	goldArray->retain();

	guideboardArray = CCArray::create();
	guideboardArray->retain();

	fireArray = CCArray::create();
	fireArray->retain();

	snowBallArray = CCArray::create();
	snowBallArray->retain();

	birdArray = CCArray::create();
	birdArray->retain();

	penguinArray = CCArray::create();
	penguinArray->retain();

	icepitonArray = CCArray::create();
	icepitonArray->retain();

	xinArray = CCArray::create();
	xinArray->retain();

	diamondArray = CCArray::create();
	diamondArray->retain();

	this->setTag(111);

}

MyTerrain::~MyTerrain(void)
{
	CC_SAFE_RELEASE_NULL(_stripes);
}

//形成山丘数组
void MyTerrain::generateHills()				
{

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float minDX = 160;
	float minDY = 60;


	float x = -minDX;
	float y = winSize.height / 2;

	float dy, ny;
	float sign = 1;
	float paddingTop = 20;				//顶部填充
	float paddingBottom = 20;			//底部填充

	for (int i = 0; i<kMaxHillKeyPoints; i++)
	{
		if (i<kMaxHillKeyPoints)
		{

			int rangeDY = 200;
			_hillKeyPoints[i] = Vec2(x, y);
			if (i == 0)
			{
				x = 0;
				y = winSize.height / 2;
			}
			else
			{

				x += 800;
				while (true)
				{
					dy = rand() % rangeDY + minDY;

					ny = y + dy * sign;

					if (ny < 320 && ny > 90)
					{
						break;
					}

				}
				y = ny;
			}
			sign *= -1;

		}

	}

}

//绘制地形
void MyTerrain::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)			
{
	_cus.init(1);
	_cus.func = CC_CALLBACK_0(MyTerrain::onDraw, this);
	renderer->addCommand(&_cus);
}

void MyTerrain::onDraw()
{
	CC_NODE_DRAW_SETUP();

	ccGLBindTexture2D(_stripes->getTexture()->getName());
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);

	ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);

	////刚体绘图调试
	//ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	//kmGLPushMatrix();
	//_world->DrawDebugData();
	//kmGLPopMatrix();
}

//设置地形偏移(地形滚动)
void MyTerrain::setOffsetX(float newOffsetX)				
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	_offsetX = newOffsetX;

	this->setPosition(Vec2(winSize.width / 8 - _offsetX * this->getScale(), 0));
	this->resetHillVertices();
}

//重置山丘顶点
void MyTerrain::resetHillVertices()				
{

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	static int prevFromKeyPointI = -1;
	static int prevToKeyPointI = -1;


	while (_hillKeyPoints[_fromKeyPointI + 1].x < _offsetX - winSize.width * 3 / 8 / this->getScale())
	{
		_fromKeyPointI++;			//从数组中统计x坐标小于主角位置-的点的个数
	}


	while (_hillKeyPoints[_toKeyPointI].x <  _offsetX + winSize.width * 9 / 8 / this->getScale())

	{
		_toKeyPointI++;				//x坐标大于主角位置的点个数
	}

	if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI)
	{

		_nHillVertices = 0;
		_nBorderVertices = 0;
		CCPoint p0, p1, pt0, pt1;
		p0 = _hillKeyPoints[_fromKeyPointI];
		for (int i = _fromKeyPointI + 1; i < _toKeyPointI + 1; ++i)
		{
			p1 = _hillKeyPoints[i];


			int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
			float dx = (p1.x - p0.x) / hSegments;
			float da = M_PI / hSegments;
			float ymid = (p0.y + p1.y) / 2;
			float ampl = (p0.y - p1.y) / 2;
			pt0 = p0;


			_borderVertices[_nBorderVertices++] = pt0;
			for (int j = 1; j < hSegments + 1; ++j)
			{

				pt1.x = p0.x + j * dx;
				pt1.y = ymid + ampl*cosf(da * j);


				_borderVertices[_nBorderVertices++] = pt1;

				_hillVertices[_nHillVertices] = ccp(pt0.x, 0);
				_hillTexCoords[_nHillVertices++] = ccp(pt0.x / 512, 1.0f);
				_hillVertices[_nHillVertices] = ccp(pt1.x, 0);
				_hillTexCoords[_nHillVertices++] = ccp(pt1.x / 512, 1.0f);

				_hillVertices[_nHillVertices] = ccp(pt0.x, pt0.y);
				_hillTexCoords[_nHillVertices++] = ccp(pt0.x / 512, 0);
				_hillVertices[_nHillVertices] = ccp(pt1.x + 10, pt1.y);
				_hillTexCoords[_nHillVertices++] = ccp(pt1.x / 512, 0);

				pt0 = pt1;

			}

			p0 = p1;
		}

		prevFromKeyPointI = _fromKeyPointI;
		prevToKeyPointI = _toKeyPointI;

		this->resetBox2DBody();
	}
}

MyTerrain * MyTerrain::createWithWorld(b2World *world)
{
	MyTerrain *pRet = new MyTerrain();

	if (pRet && pRet->initWithWorld(world))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

//通过世界初始化地形
bool MyTerrain::initWithWorld(b2World *world)		
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCNode::init());

		_world = world;

		this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE));  //kCCShader_PositionTexture
		this->generateHills();
		this->resetHillVertices();
		_batchNode = CCSpriteBatchNode::create("hero.png");
		this->addChild(_batchNode);
		_batchNode2 = CCSpriteBatchNode::create("trangle.png");
		this->addChild(_batchNode2);
		_batchNode3 = CCSpriteBatchNode::create("point.png");
		this->addChild(_batchNode3);

		_batchNode4 = CCParticleBatchNode::create("fire2.png");
		this->addChild(_batchNode4);

		_batchNode5 = CCSpriteBatchNode::create("xiutu.png");
		this->addChild(_batchNode5);
		_batchNode6 = CCSpriteBatchNode::create("box.png");
		this->addChild(_batchNode6);
		_batchNode8 = CCSpriteBatchNode::create("house.png");
		this->addChild(_batchNode8);
		_batchNode9 = CCSpriteBatchNode::create("qie.png");
		this->addChild(_batchNode9);

		_batchNode10 = CCSpriteBatchNode::create("ice.png");
		this->addChild(_batchNode10);

		_batchNode11 = CCSpriteBatchNode::create("xin.png");
		this->addChild(_batchNode11);

		_batchNode12 = CCSpriteBatchNode::create("diamond.png");
		this->addChild(_batchNode12);

		bRet = true;

	} while (0);

	//调试绘图
//	GLESDebugDraw  *m_debugDraw;
//	m_debugDraw = new GLESDebugDraw(PTM_RATIO);
//	world->SetDebugDraw(m_debugDraw);
//	uint32 flages = 0;
//	flages += b2Draw::e_shapeBit;
//	flages += b2Draw::e_jointBit;
////	flages += b2Draw::e_pairBit;
//	m_debugDraw->SetFlags(flages);

	return bRet;
}

//重置地形刚体
void MyTerrain::resetBox2DBody()		
{
	isAdd = true;
	if (_body)
	{
		_world->DestroyBody(_body);

	}
	b2BodyDef bd;
	bd.position.Set(0, 0);
	bd.userData = this;
	_body = _world->CreateBody(&bd);
	b2EdgeShape shape;
	b2Vec2 p1, p2;

	for (int i = 0; i < _nBorderVertices - 1; ++i)
	{
		p1 = b2Vec2(_borderVertices[i].x / PTM_RATIO, _borderVertices[i].y / PTM_RATIO);
		p2 = b2Vec2(_borderVertices[i + 1].x / PTM_RATIO, _borderVertices[i + 1].y / PTM_RATIO);
		shape.Set(p1, p2);


		if (i >= 1 && i % 195 == 0)
		{
			if (_borderVertices[i - 1].y > _borderVertices[i].y)
			{
				Obstacle* obstacle_sprite = new Obstacle(obstacle_guideboard, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y + 55));
				this->addChild(obstacle_sprite);				//每过195添加路牌
				guideboardArray->addObject(obstacle_sprite);
			}
		}




		if (i>1 && i % 150 == 0)
		{
			if (_borderVertices[i - 1].y > _borderVertices[i].y)
			{
				Obstacle* obstacle_sprite = new Obstacle(obstacle_bird, _world, (CCLayer*)this, ccp(_borderVertices[i].x - 500, _borderVertices[i].y + 220));
				this->addChild(obstacle_sprite);				//每过150添加鸟
				birdArray->addObject(obstacle_sprite);
			}
		}


		int mmm = rand() % 3;
		switch (mmm)
		{
		case 1:
		{
				  if (i >= 10 && i % 265 == 0)
				  {
					  if (_borderVertices[i - 1].y > _borderVertices[i].y)
					  {
						  int mmm1 = rand() % 2 + 3;
						  for (int j = 0; j<mmm1; j++)
						  {
							  Obstacle* obstacle_sprite = new Obstacle(obstacle_diamond, _world, (CCLayer*)this, ccp(_borderVertices[i].x + (j % 265 * 30), _borderVertices[i].y + 130));
							  _batchNode12->addChild(obstacle_sprite);	//添加钻石
							  diamondArray->addObject(obstacle_sprite);

							  Obstacle* obstacle_sprite1 = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i].x + (j % 265 * 30), _borderVertices[i].y + 105));
							  _batchNode5->addChild(obstacle_sprite1);		//添加黄金
							  goldArray->addObject(obstacle_sprite1);

							  Obstacle* obstacle_sprite2 = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i].x + (j % 265 * 30), _borderVertices[i].y + 80));
							  _batchNode5->addChild(obstacle_sprite2);		//添加黄金
							  goldArray->addObject(obstacle_sprite2);

						  }

					  }
				  }
		}
			break;

		default:
			break;
		}




		if (DataManager::getInstance()->_currentDistance % 500 >= 0 && DataManager::getInstance()->_currentDistance % 500 <= 10)
		{
			if (i >= 1 && i % 275 == 0)
			{

				Obstacle* obstacle_sprite = new Obstacle(obstacle_xin, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y + 80));
				_batchNode11->addChild(obstacle_sprite);  //添加心心
				xinArray->addObject(obstacle_sprite);

			}
		}


		if (DataManager::getInstance()->_currentDistance % 100 >= 0 && DataManager::getInstance()->_currentDistance % 100 <= 10)
		{
			if (i>1 && i % 230 == 0)
			{

				Obstacle* obstacle_sprite = new Obstacle(obstacle_icepiton, _world, (CCLayer*)this, ccp(_borderVertices[i].x, _borderVertices[i].y + 8));
				_batchNode10->addChild(obstacle_sprite);			//添加冰块
				icepitonArray->addObject(obstacle_sprite);


			}
		}


		int mm = rand() % 4 + 1;
		switch (mm)
		{
		case 1:
		{


				  int xx = rand() % 4 + 1;

				  switch (xx)
				  {
				  case 1:
				  {
							if (i >= 1 && i % 200 == 0)
							{

								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);		//添加黄金
								goldArray->addObject(obstacle_sprite);

							}

				  }
					  break;

				  case 2:
				  {
							if (i >= 1 && i % 200 == 0)
							{
								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
							else if (i >= 1 && i % 205 == 0)
							{

								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
				  }
					  break;
				  case 3:
				  {
							if (i >= 1 && i % 200 == 0)
							{
								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
							else if (i >= 1 && i % 205 == 0)
							{
								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
							else if (i >= 1 && i % 210 == 0)
							{

								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
				  }
					  break;

				  case 4:
				  {
							if (i >= 1 && i % 200 == 0)
							{

								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
							else if (i >= 1 && i % 205 == 0)
							{
								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
							else if (i >= 1 && i % 210 == 0)
							{

								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}
							else if (i >= 1 && i % 215 == 0)
							{
								Obstacle* obstacle_sprite = new Obstacle(obstacle_gold, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y));
								_batchNode5->addChild(obstacle_sprite);
								goldArray->addObject(obstacle_sprite);

							}

				  }
					  break;

				  default:

					  break;
				  }
		}
			break;


		case 2:
		{

				  if (i >= 1 && i % 250 == 0)
				  {
					  if (isAdd)
					  {
						  isAdd = false;
						  Obstacle *obstacle_sprite = new Obstacle(obstacle_box, _world, (CCLayer *)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y + 10));
						  _batchNode6->addChild(obstacle_sprite);		//添加箱子
						  boxArray->addObject(obstacle_sprite);
					  }
				  }

		}
			break;

		case 3:
		{

				  if (i >= 1 && i % 300 == 0)
				  {

					  if (_borderVertices[i - 1].y > _borderVertices[i].y)

					  {
						  Obstacle* obstacle_sprite = new Obstacle(obstacle_house, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x, _borderVertices[i - 1].y + 33));
						  _batchNode8->addChild(obstacle_sprite);		//添加箱子
						  houseArray->addObject(obstacle_sprite);
					  }

				  }

				  if (i >= 1 && i % 300 == 0)
				  {
					  if (_borderVertices[i - 1].y > _borderVertices[i].y)
					  {
						  Obstacle* obstacle_sprite = new Obstacle(obstacle_fire, _world, (CCLayer*)this, ccp(_borderVertices[i - 1].x + 90, _borderVertices[i - 1].y));
						  this->addChild(obstacle_sprite);				//添加鸟
						  fireArray->addObject(obstacle_sprite);
					  }

				  }

		}
			break;

		case 4:
		{

				  if (i >= 1 && i % 250 == 0)
				  {

					 Obstacle* obstacle_sprite = new Obstacle(obstacle_penguin, _world, (CCLayer*)this, ccp(_borderVertices[i].x, _borderVertices[i].y + 40));
					 _batchNode9->addChild(obstacle_sprite);			//添加企鹅
					 penguinArray->addObject(obstacle_sprite);

				  }

		}
			break;


		default:
			break;
		}

		_body->CreateFixture(&shape, 0);
	}


}

void MyTerrain::snowBallRoll(CCPoint point)		//添加雪球
{
	Obstacle* snowball = new Obstacle(obstacle_snowball, _world, (CCLayer*)this, point);
	this->addChild(snowball);
	snowBallArray->addObject(snowball);


}


