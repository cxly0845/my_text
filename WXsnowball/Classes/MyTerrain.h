#ifndef __Terrain_H__
#define __Terrain_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

using namespace cocos2d;

#define kMaxHillKeyPoints 30000				//山丘数组最大值
#define kHillSegmentWidth 5					//山丘部分宽度
#define kMaxHillVertices 4000				//山丘顶点
#define kMaxBorderVertices 800				//边界顶点

#define TERRAIN_ID 2

class Obstacle;

class MyTerrain : public Node				//地形绘制
{
public:

	MyTerrain(void);
	~MyTerrain(void);
	CREATE_FUNC(MyTerrain);

	static MyTerrain *createWithWorld(b2World *world);
	bool initWithWorld(b2World *world);
	void setOffsetX(float newOffsetX);
	void generateHills();
	void resetHillVertices();
	void resetBox2DBody();
	void snowBallRoll(Vec2 point);


	Array* boxArray;				//箱子数组
	Array* houseArray;			//房子数组
	Array* goldArray;				//黄金数组
	Array* guideboardArray;		//路牌数组
	Array* fireArray;				//火焰数组
	Array *snowBallArray;			//雪球数组
	Array * birdArray;			//鸟数组
	Array * penguinArray;			//企鹅数组
	Array * icepitonArray;		//冰块数组
	Array * xinArray;				//心心数组
	Array * diamondArray;			//钻石数组

	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _stripes, Stripes);					//设置条纹精灵
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode, BatchNode);		//一批精灵节点
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode2, BatchNode2);	
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode3, BatchNode3);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCParticleBatchNode*, _batchNode4, BatchNode4);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode5, BatchNode5);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode6, BatchNode6);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode8, BatchNode8);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode9, BatchNode9);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode10, BatchNode10);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode11, BatchNode11);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode12, BatchNode12);

private:
	float _offsetX;									//x偏移
	CCPoint _hillKeyPoints[kMaxHillKeyPoints];		//山丘点数组
	int _fromKeyPointI;									
	int _toKeyPointI;
	int _nHillVertices;								//山丘至高点
	CCPoint _hillVertices[kMaxHillVertices];		//山丘顶点数组
	CCPoint _hillTexCoords[kMaxHillVertices];		//山丘纹理坐标数组
	int _nBorderVertices;							//边界至高点
	CCPoint _borderVertices[kMaxBorderVertices];	//边界顶点数组
	b2World *_world;
	b2Body *_body;
	bool isAdd;

	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void onDraw();
	CustomCommand _cus;
};
#endif