#include "MenuController.h"
#include "GameScene.h"
#define LINE_SPACE 30

MenuController::MenuController(void)
:m_tBeginPos(CCPointZero)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	


	CCSprite * image = CCSprite::create("HelloWorld.png");
	image->setPosition(ccp(s.width/2,s.height/2));
	addChild(image,0);


	CCDictionary * chnStrings = CCDictionary::dictionaryWithContentsOfFile("CHN_Strings.xml");
	const char * sStart = ((CCString *)chnStrings->objectForKey("sStart"))->getCString();
	const char * sExit = ((CCString *)chnStrings->objectForKey("sExit"))->getCString();


	CCLabelBMFont * magicword = CCLabelBMFont::create("HelloWorld","bitmapFontTest.fnt");
	magicword->setAnchorPoint(ccp(0.5,0.5));
	magicword->setPosition(s.width/2,s.height/2);
	addChild(magicword,1);
	CCActionInterval * fade = CCFadeOut::create(1.0f);
	CCActionInterval * fadeIn = fade->reverse();
	CCFiniteTimeAction * seq = CCSequence::create(fade,fadeIn,NULL);
	CCAction * repeat = CCRepeatForever::create((CCActionInterval *)seq);
	magicword->runAction(repeat);
	m_pItemMenu = CCMenu::create();

	CCLabelTTF* label1 = CCLabelTTF::create(sStart, "Arial", 25);
	CCLabelTTF* label2 = CCLabelTTF::create(sExit, "Arial", 25);
	CCMenuItemLabel * item1 = CCMenuItemLabel::create(label1,this,menu_selector(MenuController::menuCallback));
	item1->setPosition( ccp(80, 30));
	item1->setColor(ccc3(8,25,45));
	CCMenuItemLabel * item2 = CCMenuItemLabel::create(label2,this,menu_selector(MenuController::closeCallback));
	item2->setPosition( ccp( s.width-80, 30));
	item2->setColor(ccc3(8,25,45));
	
	m_pItemMenu->addChild(item1,1);
	m_pItemMenu->addChild(item2,1);

	m_pItemMenu->setContentSize(CCSizeMake(s.width, s.height));
    m_pItemMenu->setPosition(ccp(0,0));
    addChild(m_pItemMenu,1);

    setTouchEnabled(true);


}

MenuController::~MenuController(void)
{
}

void MenuController::menuCallback(CCObject * pSender)
{
	CCDirector::sharedDirector()->purgeCachedData();

	CCScene * pScene = CCScene::create();
	GameScene * pLayer = new GameScene();
	pLayer->autorelease();
	pScene->addChild(pLayer,0);
	CCDirector::sharedDirector()->replaceScene(pScene);

}

void MenuController::closeCallback(CCObject * pSender)
{
	CCDirector::sharedDirector()->end();
}
