#include "FirstLayer.h"
#include "SimpleAudioEngine.h"
#include "DlgFrame.h"
#include "PopupLayer.h"
#include <WINDOWS.H>

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

void FirstLayer::setParticleSys()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
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
}


void FirstLayer::setGroundCeiling()
{
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(50/BOX_PIXEL,50/BOX_PIXEL);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
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
}
//void FirstLayer::popupLayer()
//{
//    // 定义一个弹出层，传入一张背景图片
//    PopupLayer* popup = PopupLayer::create("beingGod.png");
//    // ContentSize是可选的设置，可以不设置，如果设置则把它当做9图缩放
//    popup->setContentSize(CCSizeMake(250, 260));
//    popup->setTitle("Message");
//    popup->setContentText("Most people... ", 20, 50, 150);
//    // 设置回调函数，回调传回一个CCNode以获取tag判断点击的按钮
//    // 这只是作为一种封装实现，如果使用delegate那就能够更灵活的控制参数了
////    popup->setCallBackFunc(this, callfuncN_selector(FirstLayer::buttonCallback));
//    //添加按钮，设置图片、文字，tag信息
//    popup->addButton("CloseNormal.png", "CloseSelected.png", "Ok", 0);
//    popup->addButton("CloseNormal.png", "CloseSelected.png", "Cancel", 1);
//    this->addChild(popup);
//}
void FirstLayer::updateGame(float dt)
{
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//CCLabelTTF * addOneSecond = CCLabelTTF::create("-1s","Georgia", 30);
	//addOneSecond->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	//addOneSecond->setColor(ccc3(0xFF, 0x00, 0x00));
	//addOneSecond->setPosition(CCPointMake(s.width/2, s.height * 0.7));
	//addChild(addOneSecond, 5);
	if(pHaha->m_pBody->GetPosition().y > s.height * 0.9/ BOX_PIXEL
		|| pHaha->m_pBody->GetPosition().y < s.height * 0.1/ BOX_PIXEL)
	{
		timecount -= 5;
		CCLabelTTF * addOneSecond = CCLabelTTF::create("-5s","Georgia", 30);
		addOneSecond->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		addOneSecond->setColor(ccc3(0xFF, 0x00, 0x00));
		addOneSecond->setPosition(CCPointMake(s.width * 0.9, s.height * 0.87));
		addChild(addOneSecond, 5);
		CCActionInterval * fade = CCFadeOut::create(0.02f);
		addOneSecond->runAction(fade);
		setLife();
	}
	if(timecount <= 0)
	{
		stringstream strm_givecount;
		string str_givecount;
		strm_givecount << givecount;
		strm_givecount >> str_givecount;
		string lifelabel = "您用光了您的命:)总共为长者续了";
		string seclabel = "秒";
		str_givecount = lifelabel + str_givecount + seclabel;
		MessageBox(NULL,TEXT("您用光了您的命:)"),TEXT("Gameover"),MB_OK);
		CCDirector::sharedDirector()->end();
		exit(0);
	}
}

FirstLayer::FirstLayer()
{
	schedule(schedule_selector(FirstLayer::updateGame));

	//CCTime::gettimeofdayCocos2d(&t_begin, NULL);
	givecount = 0;
	timecount = 60;
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

	CCSprite * pWenxuan = CCSprite::create("wenxuan.png");
	CCMenuItemSprite * wenxuanitem = CCMenuItemSprite::create(pWenxuan, pWenxuan, pWenxuan,
		this, menu_selector(FirstLayer::learnCallback));
	//CCMenu * pmenu = CCMenu::create(wenxuanitem);
	//pmenu->alignItemsVertically();
	wenxuanitem->setPosition(CCPointMake(s.width * 0.1, s.height * 0.5));
	wenxuanitem->setScale(0.4f);
	addChild(wenxuanitem, 1);
	

	CCLabelTTF * learnlabel = CCLabelTTF::create("LEARN","Georgia", 25);
	learnlabel->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	learnlabel->setColor(ccc3(0xFF, 0xFF, 0xFF));
	learnlabel->setPosition(CCPointMake(s.width * 0.1, s.height * 0.7));
	addChild(learnlabel, 5);

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

	setGroundCeiling();
	setTitle(1);
	setParticleSys();

	CCLabelTTF * skilllabel = CCLabelTTF::create("SKILL\n click to give life","Georgia", 25);
	skilllabel->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	skilllabel->setColor(ccc3(0xFF, 0xFF, 0xFF));
	skilllabel->setPosition(CCPointMake(s.width * 0.1, s.height * 0.9));
	addChild(skilllabel, 5);
	//TODO
	setLife();
	scheduleUpdate();
}

FirstLayer::~FirstLayer()
{
	delete world;
    world = NULL;
}

void FirstLayer::learnCallback(CCObject * pSender)
{
	FirstLayer * mylayer = (FirstLayer *)pSender;
	//CCLabelTTF * skilllabel = CCLabelTTF::create("Mo Fa","Georgia", 25);
	//skilllabel->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	//skilllabel->setColor(ccc3(0xFF, 0xFF, 0xFF));
	//skilllabel->setPosition(CCPointMake(s.width * 0.1, s.height * 0.8));
	//mylayer->addChild(skilllabel, 5);
 // create a scene. it's an autorelease object
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
	//clock_t finish = clock();
	//double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	//if (duration > 10.0) 
	//{
	//	AfxMessageBox(L"您的生命值已用光:)");
	//	exit(0);
	//}
	//CCTime::gettimeofdayCocos2d(&t_now, NULL);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//CCLabelTTF * addOneSecond = CCLabelTTF::create("-1s","Georgia", 30);
	//addOneSecond->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	//addOneSecond->setColor(ccc3(0xFF, 0x00, 0x00));
	//addOneSecond->setPosition(CCPointMake(s.width/2, s.height * 0.7));
	//addChild(addOneSecond, 5);
	if(pHaha->getPosition().y > s.height * 0.8)
	{
		MessageBox(NULL,TEXT("您用光了您的命:)"),TEXT("Gameover"),MB_OK);
	}
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
void FirstLayer::setLife()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	stringstream strm_timecount;
    string str_timecount;
    strm_timecount << timecount;
    strm_timecount >> str_timecount;
	string lifelabel = "LIFE: ";
	string seclabel = " sec";
    str_timecount = lifelabel + str_timecount + seclabel;
	CCLabelTTF * labelcount = CCLabelTTF::create(str_timecount.data(),"Georgia", 30);
	labelcount->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	labelcount->setColor(ccc3(0xFF, 0xFF, 0xFF));
	labelcount->setPosition(CCPointMake(s.width * 0.9, s.height * 0.9));
	this->removeChildByTag(20, true);
	addChild(labelcount, 5, 20);
}
void FirstLayer::registerWithTouchDispatcher(void)
{
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool FirstLayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	givecount++;
	timecount--;
	setLife();
	//popupLayer();


	
	CCLabelTTF * addOneSecond = CCLabelTTF::create("-1s","Georgia", 30);
	addOneSecond->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	addOneSecond->setColor(ccc3(0xFF, 0x00, 0x00));
	addOneSecond->setPosition(CCPointMake(s.width * 0.9, s.height * 0.87));
	addChild(addOneSecond, 5);

	CCActionInterval * fade = CCFadeOut::create(0.5f);
	addOneSecond->runAction(fade);
	pHaha->m_pBody->ApplyLinearImpulse( b2Vec2(0,700), pHaha->m_pBody->GetWorldCenter() );
	if(isGravityDown)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(
		string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("gao.wav")).c_str(),false);
		//world->SetGravity(b2Vec2(0.0f,10.0f));
		isGravityDown = false;
		setTitle(2);
	}
	else 
	{
		SimpleAudioEngine::sharedEngine()->playEffect(
		string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("haoa.wav")).c_str(),false);
		//world->SetGravity(b2Vec2(0.0f,-10.0f));
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
