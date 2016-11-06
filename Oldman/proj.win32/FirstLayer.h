#ifndef _FIRST_LAYER_H_
#define _FIRST_LAYER_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class PhysicsSprite : 
	public CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
	virtual CCAffineTransform nodeToParentTransform(void);
public:
    b2Body * m_pBody;
};



class FirstLayer :
	public CCLayer
{
	b2World * world;
	PhysicsSprite * pHaha;
	bool isGravityDown;
	unsigned int wavNum;
public:
	FirstLayer();
	~FirstLayer();
	void update(float dt);
	void setTitle(int count);
	//touch event
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch * touch,CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * touch,CCEvent * pEvent);
	virtual void ccTouchEnded(CCTouch * touch,CCEvent * pEvent);
	virtual void ccTouchCanceled(CCTouch * touch,CCEvent * pEvent);
};

class MyContactListener : 
	public b2ContactListener
{
public:
  void BeginContact(b2Contact* contact)
  { /* handle begin event */ }

  void EndContact(b2Contact* contact)
  { /* handle end event */ }

  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
  { /* handle pre-solve event */ }

  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
  { /* handle post-solve event */ }
};


#endif//_FIRST_LAYER_H_