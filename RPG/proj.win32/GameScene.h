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
	bool showWord;//是否显示文字
	int wordNum;
	bool isStart;
	CCLayerColor * wordLayer;
//	float deltax,deltay;
	CCTMXTiledMap * map;
	CCTMXLayer * layerMap;
	void beforeMove();//移动前回调函数
	void afterMove();//移动后回调函数
//	int around[4];
	CCPoint getSRDMapPoint(kSRDMap ksrdmap);//得到人物四周的地图块坐标
	CCPoint getCRTMapPoint();//得到人物当前的地图块坐标

};

#endif