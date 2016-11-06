#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

enum kSRDMap{
	kLeftMap = 1,
	kRightMap,
	kUpMap,
	kDownMap};


class GameScene :
	public CCLayer
{
public:
	GameScene(void);
	~GameScene(void);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyArrowClicked(int arrow);
	virtual void keyEnterClicked();
	void characterMapCollision();
	void testMapWay();
	void desireCallback(CCObject * pSender);
	void desireNotCallback(CCObject * pSender);
private:
	CCSprite * m_pCharacter;
//	bool isControl;
	bool moveDisabled;
	bool leftAble;
	bool rightAble;
	bool upAble;
	bool downAble;
	bool showWord;//�Ƿ���ʾ����
	int wordNum;
	bool isStart;
	CCLayerColor * wordLayer;
//	float deltax,deltay;
	CCTMXTiledMap * map;
	CCTMXLayer * layerMap;
	void beforeMove();//�ƶ�ǰ�ص�����
	void afterMove();//�ƶ���ص�����
//	int around[4];
	CCPoint getSRDMapPoint(kSRDMap ksrdmap);//�õ��������ܵĵ�ͼ������
	CCPoint getCRTMapPoint();//�õ����ﵱǰ�ĵ�ͼ������

};

#endif