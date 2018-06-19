#ifndef __Terrain_H__
#define __Terrain_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

using namespace cocos2d;

#define kMaxHillKeyPoints 30000				//ɽ���������ֵ
#define kHillSegmentWidth 5					//ɽ�𲿷ֿ��
#define kMaxHillVertices 4000				//ɽ�𶥵�
#define kMaxBorderVertices 800				//�߽綥��

#define TERRAIN_ID 2

class Obstacle;

class MyTerrain : public Node				//���λ���
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


	Array* boxArray;				//��������
	Array* houseArray;			//��������
	Array* goldArray;				//�ƽ�����
	Array* guideboardArray;		//·������
	Array* fireArray;				//��������
	Array *snowBallArray;			//ѩ������
	Array * birdArray;			//������
	Array * penguinArray;			//�������
	Array * icepitonArray;		//��������
	Array * xinArray;				//��������
	Array * diamondArray;			//��ʯ����

	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _stripes, Stripes);					//�������ƾ���
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode, BatchNode);		//һ������ڵ�
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
	float _offsetX;									//xƫ��
	CCPoint _hillKeyPoints[kMaxHillKeyPoints];		//ɽ�������
	int _fromKeyPointI;									
	int _toKeyPointI;
	int _nHillVertices;								//ɽ�����ߵ�
	CCPoint _hillVertices[kMaxHillVertices];		//ɽ�𶥵�����
	CCPoint _hillTexCoords[kMaxHillVertices];		//ɽ��������������
	int _nBorderVertices;							//�߽����ߵ�
	CCPoint _borderVertices[kMaxBorderVertices];	//�߽綥������
	b2World *_world;
	b2Body *_body;
	bool isAdd;

	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void onDraw();
	CustomCommand _cus;
};
#endif