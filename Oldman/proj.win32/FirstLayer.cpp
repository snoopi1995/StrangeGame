#include "FirstLayer.h"
#include "SimpleAudioEngine.h"
#include "DlgFrame.h"

#define BOX_PIXEL 32
#define MAX_COUNT 10


using namespace CocosDenshion;

enum
{
	kTagWord = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body* body)
{
	m_pBody = body;
}

CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * BOX_PIXEL;
    float y = pos.y * BOX_PIXEL;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_tTransform;
}


FirstLayer::FirstLayer()
{
	//load background music file
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
		CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Schoen_Rosmarin.wav"));
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Schoen_Rosmarin.wav")).c_str(),true);

	//load words effect file
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("haoa.wav"));
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5f);


	setTouchEnabled(true);

	//define the world
	b2Vec2 gravity(0.0f, -10.0f);
	isGravityDown = true;
	world = new b2World(gravity);

//	world->SetAllowSleeping(true);
//	world->SetContinuousPhysics(true);

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	pHaha = new PhysicsSprite();
	pHaha->initWithFile("haha.png");
	pHaha->autorelease();
	addChild(pHaha,1);



	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(s.width/2/BOX_PIXEL, s.height/BOX_PIXEL/2);
	bodyDef.linearDamping = 0.1f;
	b2Body* body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(50/BOX_PIXEL,50/BOX_PIXEL);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 1.0f;

	body->CreateFixture(&fixtureDef);

	pHaha->setPhysicsBody(body);
	
	//set ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(s.width/2/BOX_PIXEL,0);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBodyBox;
	groundBodyBox.SetAsBox(s.width/BOX_PIXEL,0.5);
	b2FixtureDef gfixtureDef;
	gfixtureDef.shape = &dynamicBox;
	gfixtureDef.density = 5.0f;
	gfixtureDef.friction = 0.3f;
	groundBody->CreateFixture(&gfixtureDef);

	b2BodyDef groundBodyDef2;
	groundBodyDef2.type = b2_staticBody;
	groundBodyDef2.position.Set(s.width/2/BOX_PIXEL,s.height/BOX_PIXEL);
	b2Body* groundBody2 = world->CreateBody(&groundBodyDef2);
	b2PolygonShape groundBodyBox2;
	groundBodyBox2.SetAsBox(s.width/BOX_PIXEL,0.5);
	b2FixtureDef gfixtureDef2;
	gfixtureDef2.shape = &dynamicBox;
	gfixtureDef2.density = 5.0f;
	gfixtureDef2.friction = 0.3f;
	groundBody2->CreateFixture(&gfixtureDef2);

	setTitle(1);

	CCParticleSystemQuad * m_emitter = new CCParticleSystemQuad();
	m_emitter->initWithTotalParticles(50);
	addChild(m_emitter, 10);
	m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("haha.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(CCPointZero);
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setSpeed(160);
	m_emitter->setSpeedVar(20);
	m_emitter->setRadialAccel(-120);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	m_emitter->setPosition(CCPointMake(160, 240));
	m_emitter->setPosVar(CCPointZero);
	m_emitter->setLife(4);
	m_emitter->setLifeVar(1);
	m_emitter->setStartSpin(0);
	m_emitter->setStartSpinVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);

	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);
	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);
	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColor(endColor);
	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColorVar(endColorVar);

	m_emitter->setStartSize(80.0f);
	m_emitter->setStartSizeVar(40.0f);
	m_emitter->setEndSize(kParticleStartSizeEqualToEndSize);

	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());

	m_emitter->setBlendAdditive(true);

	if(m_emitter != NULL)
		m_emitter->setPosition(CCPointMake(s.width/2, s.height/8));

	this->scheduleUpdate();

}

FirstLayer::~FirstLayer()
{
	delete world;
    world = NULL;
}

void FirstLayer::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;

    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
}

void FirstLayer::setTitle(int count)
{
	if (this->getChildByTag(kTagWord) != NULL)
		this->removeChildByTag(kTagWord,true);
	std::stringstream stringcount; 
	stringcount << count;

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCDictionary * dictHa = CCDictionary::dictionaryWithContentsOfFile("dict/moHa.xml");
	const char * wordHa = ((CCString *)dictHa->objectForKey(stringcount.str()))->getCString();
	CCLabelTTF* words = CCLabelTTF::create(wordHa, "华文新魏", 20);
	words->setAnchorPoint(ccp(0.5f, 0.5f)); 
	words->setPosition( ccp(s.width/2, s.height-50));
//	words->setDimensions(CCSizeMake(160,90));
//	words->setHorizontalAlignment(kCCTextAlignmentLeft);
	addChild(words,1,kTagWord);
}
void FirstLayer::registerWithTouchDispatcher(void)
{
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool FirstLayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent)
{
	if(isGravityDown)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(
		string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("gao.wav")).c_str(),false);
		world->SetGravity(b2Vec2(0.0f,10.0f));
		isGravityDown = false;
		setTitle(2);
	}
	else 
	{
		SimpleAudioEngine::sharedEngine()->playEffect(
		string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("haoa.wav")).c_str(),false);
		world->SetGravity(b2Vec2(0.0f,-10.0f));
		isGravityDown = true;
		setTitle(3);
	}
	return true;
}

void FirstLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent)
{
}

void FirstLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent)
{
}

void FirstLayer::ccTouchCanceled(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent)
{
	
}
