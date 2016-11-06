#include<iostream> 
#include<string> 
#include<sstream> 
#include "GameScene.h"
#define SQ(a) ((a)*(a))

 

GameScene::GameScene(void)
{
	
	setTouchEnabled(true);
	setKeypadEnabled(true);
	moveDisabled = true;
	upAble = true;
	downAble = true;
	leftAble = true;
	rightAble = true;
	showWord = true;
	isStart = true;
	wordNum = 0;
	CCSize s = CCDirector::sharedDirector()->getWinSize();

/* 	m_pRedBall = CCSprite::create("RedBall.png");
	m_pRedBall->setPosition(ccp(s.width/2,s.height/2));
	m_pRedBall->setScale(0.2f);
	m_pRedBall->getTexture()->setAntiAliasTexParameters();
	addChild(m_pRedBall,1);
	CCActionInterval * actionBlink = CCBlink::create(5,10);
	m_pRedBall->runAction(CCRepeatForever::create(actionBlink));
	isControl = false;
*/
	map = CCTMXTiledMap::create("mapSeeSide.tmx");
	addChild(map, 1);
	map->setAnchorPoint(ccp(0.0f,0.0f));
	map->setPosition(0,0);
	/*CCSize mapSize = map->getContentSize();
	CCArray * pChildrenArray = map->getChildren();
	CCSpriteBatchNode * child = NULL;
	CCObject * pObject = NULL;
	CCARRAY_FOREACH(pChildrenArray,pObject)
	{
		child = (CCSpriteBatchNode *)pObject;
		if(!child)
			break;
		child->getTexture()->setAntiAliasTexParameters();
	}
*/	
	CCSpriteFrameCache * pCharacterC = CCSpriteFrameCache::sharedSpriteFrameCache();
	pCharacterC->addSpriteFramesWithFile("character.plist","character.png");
	CCArray * animFrames = CCArray::create(3);
	CCSpriteFrame * frame1 = pCharacterC->spriteFrameByName("111.png");
	animFrames->addObject(frame1);
	CCSpriteFrame * frame2 = pCharacterC->spriteFrameByName("112.png");
	animFrames->addObject(frame2);
	CCAnimation * animation = CCAnimation::create(animFrames,0.2f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation,"walk");
	animFrames->removeAllObjects();
	CCAnimation * walk = CCAnimationCache::sharedAnimationCache()->animationByName("walk");
	walk->setRestoreOriginalFrame(true);
	CCAnimate * animW = CCAnimate::create(walk);
	m_pCharacter = CCSprite::create();
	m_pCharacter->setDisplayFrame(pCharacterC->spriteFrameByName("111.png"));
	CCSize sizeCrt = m_pCharacter->getContentSize();
	m_pCharacter->setAnchorPoint(ccp(0.5f,0.5f));

	int startIndexx = 10;
	int startIndexy = 15;
	CCPoint startpoint = ccp(32*startIndexx+map->getTileSize().width/2,(20-startIndexy)*32-map->getTileSize().height/2);
	m_pCharacter->setPosition(startpoint);
	addChild(m_pCharacter,2);
	m_pCharacter->setScale(0.4f);
	m_pCharacter->runAction(CCRepeatForever::create(animW));
	layerMap = map->layerNamed("Layer1");
//	CCSprite * s1 = layerMap->tileAt(ccp(10,19));
//	s1->removeFromParentAndCleanup(false);
//	layerMap->removeTileAt(ccp(10,13));
//	CCPoint positionCrt = m_pCharacter->getPosition();
//	sizeCrt.width = sizeCrt.width/2;
//	sizeCrt.height = sizeCrt.height/2;
//	int indexx = (positionCrt.x-sizeCrt.width/2)/map->getTileSize().width;
//	int	indexy = map->getMapSize().height-(positionCrt.y-sizeCrt.height/2)/map->getTileSize().height;

//	int up = layerMap->tileGIDAt(getSRDMapPoint(kUpMap));
//	layerMap->removeTileAt(getSRDMapPoint(kUpMap));
//	layerMap->removeTileAt(getSRDMapPoint(kLeftMap));
//	layerMap->removeTileAt(getSRDMapPoint(kRightMap));
//	layerMap->removeTileAt(getSRDMapPoint(kDownMap));

//	int left = layerMap->tileGIDAt(getSRDMapPoint(kLeftMap));
//	layerMap->setTileGID(left,getSRDMapPoint(kLeftMap));
//	layerMap->setTileGID(up,getSRDMapPoint(kUpMap));
	
//	CCSprite * s2 = layerMap->tileAt(ccp(indexx+1,indexy));
//	s1->removeFromParentAndCleanup(false);
//	CCSprite * s3 = layerMap->tileAt(ccp(indexx,indexy-1));
//	s1->removeFromParentAndCleanup(false);
//	CCSprite * s4 = layerMap->tileAt(ccp(indexx,indexy+1));
//	s1->removeFromParentAndCleanup(false);
//	testMapWay();
//	CCDirector::sharedDirector()->setDepthTest(false);
//	CCTileGrid3D * gridS1 = layerMap->;
//	CCWaves3D * actionWave = CCWaves3D::create(5,5.0f,gridS1->getGridSize(),3);
//	gridS1->runAction(actionWave);
//	if(s1->numberOfRunningActions()==0&&s1->getGrid()!=NULL)
//		s1->setGrid(NULL);
//	CCDirector::sharedDirector()->setDepthTest(false);
//	ccGridSize sss = {32,24};
//	CCActionInterval* shaky3D = CCShaky3D::create(15,false, sss, 4);
//	CCActionInterval* shakyTiles3D = CCShakyTiles3D::create(15,false, sss, 4);
//  layerMap->runAction(shakyTiles3D);
//	CCActionInterval* shaky3DBack=shaky3D->reverse();
//	layerMap->runAction(shaky3D);
//	shaky3D->startWithTarget(layerMap);
//	CCActionInterval* shaky3DBack=shaky3D->reverse();
//	shaky3DBack->startWithTarget(layerMap);
//	layerMap->runAction(CCSequence::create(shaky3D,shaky3DBack, NULL)); 
//检测父节点是否还有动作，如果没有并且网格不为空  
 if(layerMap->numberOfRunningActions() == 0 && layerMap->getGrid() != NULL)  
 {  
    //调用setGrid函数并传入空参数（NULL）便可清空网格，使用schedule一直检测调用这段代码就可以实现清空无动作的节点网  
     layerMap->setGrid( NULL );    
}
}

GameScene::~GameScene(void)
{
}
void GameScene::registerWithTouchDispatcher()
{
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	CCLayer::registerWithTouchDispatcher();
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	/*CCPoint ballPos = m_pRedBall->getPosition();
	CCPoint location = pTouch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	if((SQ(location.x-ballPos.x)+SQ(location.y-ballPos.y)) < SQ(128))
	{
		isControl = true;
		deltax = location.x-ballPos.x;
		deltay = location.y-ballPos.y;
	}

*/
/*	CCSprite * m_pRedBall = CCSprite::create("RedBall.png");
	m_pRedBall->setPosition(location);
	m_pRedBall->setScale(0.2f);
	addChild(m_pRedBall,1);
	CCActionInterval * actionBlink = CCBlink::create(5,10);
	m_pRedBall->runAction(CCRepeatForever::create(actionBlink));
	m_pRedBall->getTexture()->setAntiAliasTexParameters();
*/
	return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
/*	if(isControl)
	{
		CCPoint location = pTouch->locationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);
		float x = location.x-deltax;
		float y = location.y-deltay;
		m_pRedBall->setPosition(ccp(x,y));
	}*/
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//	isControl = false;
}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
//	isControl = false;

}



void GameScene::keyArrowClicked(int arrow)
{
	CCTMXLayer * layerMap = map->layerNamed("Layer1");

	CCFiniteTimeAction * walkLeft = CCSequence::create(
		CCCallFunc::create(this,callfunc_selector(GameScene::beforeMove)),
		CCMoveBy::create(0.15f,ccp(-32,0)),
		CCCallFunc::create(this,callfunc_selector(GameScene::afterMove)),
		NULL);
	CCFiniteTimeAction * walkRight = CCSequence::create(
		CCCallFunc::create(this,callfunc_selector(GameScene::beforeMove)),
		CCMoveBy::create(0.15f,ccp(32,0)),
		CCCallFunc::create(this,callfunc_selector(GameScene::afterMove)),
		NULL);
	CCFiniteTimeAction * walkUp = CCSequence::create(
		CCCallFunc::create(this,callfunc_selector(GameScene::beforeMove)),
		CCMoveBy::create(0.15f,ccp(0,32)),
		CCCallFunc::create(this,callfunc_selector(GameScene::afterMove)),
		NULL);
	CCFiniteTimeAction * walkDown = CCSequence::create(
		CCCallFunc::create(this,callfunc_selector(GameScene::beforeMove)),
		CCMoveBy::create(0.15f,ccp(0,-32)),
		CCCallFunc::create(this,callfunc_selector(GameScene::afterMove)),
		NULL);
	if(getCRTMapPoint().x==0)
		leftAble = false;
	if(getCRTMapPoint().x==map->getMapSize().width-1)
		rightAble = false;
	if(getCRTMapPoint().y==map->getMapSize().height-1)
		downAble = false;
	if(getCRTMapPoint().y==0)
		upAble = false;
	characterMapCollision();
	switch(arrow)
	{
	case kTypeLeftArrowClicked:
//		if(characterMapCollision()!=1)
//		{
		if(moveDisabled&&leftAble)
		{
			m_pCharacter->runAction(walkLeft);
		}
//		}
		break;
	case kTypeRightArrowClicked:
		if(moveDisabled&&rightAble)
		{
			m_pCharacter->runAction(walkRight);
		}
		break;
	case kTypeUpArrowClicked:
		if(moveDisabled&&upAble)
		{
			m_pCharacter->runAction(walkUp);
		}
		break;
	case kTypeDownArrowClicked:
		
		if(moveDisabled&&downAble)
		{
			m_pCharacter->runAction(walkDown);
		}
		break;
	}
//	CCSprite * s1 = getSRDMap(kUpMap);
//	s1->removeFromParentAndCleanup(false);
	this->runAction(CCFollow::create(m_pCharacter,CCRectMake(0,0,1600,640)));
//	wordLayer->runAction(CCFollow::create(m_pCharacter,CCRectMake(0,0,1600,640)));
//	layerMap->removeTileAt(getSRDMapPoint(kUpMap));
//	layerMap->removeTileAt(getSRDMapPoint(kLeftMap));
//	layerMap->removeTileAt(getSRDMapPoint(kRightMap));
//	layerMap->removeTileAt(getSRDMapPoint(kDownMap));

}




//主角地图碰撞检测
void GameScene::characterMapCollision()
{
	int thisGID = layerMap->tileGIDAt(getSRDMapPoint(kUpMap))-1;
	if(!(thisGID==132||thisGID==158||thisGID==159||thisGID==176||thisGID==177||
		thisGID==178||thisGID==196||thisGID==179||thisGID==162||thisGID==145||
		thisGID==144||thisGID==127||thisGID==110||thisGID==75||thisGID==61||
		thisGID==62||thisGID==133||thisGID==116||thisGID==117||thisGID==118||
		thisGID==152||thisGID==128||thisGID==146||thisGID==147||thisGID==131||
		thisGID==114||thisGID==59))
			upAble = false;
	thisGID = layerMap->tileGIDAt(getSRDMapPoint(kRightMap))-1;
	if(!(thisGID==132||thisGID==158||thisGID==159||thisGID==176||thisGID==177||
		thisGID==178||thisGID==196||thisGID==179||thisGID==162||thisGID==145||
		thisGID==144||thisGID==127||thisGID==110||thisGID==75||thisGID==61||
		thisGID==62||thisGID==133||thisGID==116||thisGID==117||thisGID==118||
		thisGID==152||thisGID==128||thisGID==146||thisGID==147||thisGID==131||
		thisGID==114||thisGID==59))
			rightAble = false;
	thisGID = layerMap->tileGIDAt(getSRDMapPoint(kLeftMap))-1;
	if(!(thisGID==132||thisGID==158||thisGID==159||thisGID==176||thisGID==177||
		thisGID==178||thisGID==196||thisGID==179||thisGID==162||thisGID==145||
		thisGID==144||thisGID==127||thisGID==110||thisGID==75||thisGID==61||
		thisGID==62||thisGID==133||thisGID==116||thisGID==117||thisGID==118||
		thisGID==152||thisGID==128||thisGID==146||thisGID==147||thisGID==131||
		thisGID==114||thisGID==59))
			leftAble = false;
	thisGID = layerMap->tileGIDAt(getSRDMapPoint(kDownMap))-1;
	if(!(thisGID==132||thisGID==158||thisGID==159||thisGID==176||thisGID==177||
		thisGID==178||thisGID==196||thisGID==179||thisGID==162||thisGID==145||
		thisGID==144||thisGID==127||thisGID==110||thisGID==75||thisGID==61||
		thisGID==62||thisGID==133||thisGID==116||thisGID==117||thisGID==118||
		thisGID==152||thisGID==128||thisGID==146||thisGID==147||thisGID==131||
		thisGID==114||thisGID==59))
			downAble = false;
//	int choice=0;
//	CCPoint positionCrt = m_pCharacter->getPosition();
//	positionCrt.x +=320;
//	positionCrt.y +=128;
//	CCSize sizeCrt = m_pCharacter->getContentSize();
//	sizeCrt.width = sizeCrt.width/2;
//	sizeCrt.height = sizeCrt.height/2;
//	int indexx,indexy;
//	CCTMXLayer * layerMap = map->layerNamed("Layer1");
	//待完成，遍历图素块，注意锚点位置
//	for(int charactery = positionCrt.y - sizeCrt.height/2;charactery <= (positionCrt.y+sizeCrt.height/2);charactery++)
//	{
		//人物左侧发生碰撞

//		indexx = (positionCrt.x-sizeCrt.width/2)/map->getTileSize().width;
//		indexy = map->getMapSize().height-(charactery)/map->getTileSize().height;
//		CCPoint characterIndex = ccp(indexx,indexy);
//		int recID = layerMap->tileGIDAt(characterIndex);
		//阻挡元素编号
//		if(!(recID==61||recID==75||((recID>=90)&&(recID<=93))||recID==97||
//			recID==102||recID==110||((recID>=114)&&(recID<=118))||
//			recID==127||recID==131||recID==144||recID==145||recID==159||
//			recID==161||recID==162||recID==176||recID==177||recID==178||
//			recID==179||recID==196))
//		{
//			CCDictionary * tiledic = map->propertiesForGID(recID);
//				choice=1;

//		}
//	}
//	return choice;

}

void GameScene::afterMove()
{
	moveDisabled = true;
	leftAble = true;
	rightAble = true;
	upAble = true;
	downAble = true;
//	layerMap->setTileGID(around[0],getSRDMapPoint(kLeftMap));
//	layerMap->setTileGID(around[1],getSRDMapPoint(kLeftMap));
//	layerMap->setTileGID(around[2],getSRDMapPoint(kLeftMap));
//	layerMap->setTileGID(around[3],getSRDMapPoint(kLeftMap));
}

CCPoint GameScene::getSRDMapPoint(kSRDMap ksrdmap)
{
	CCPoint positionCrt = m_pCharacter->getPosition();
//	CCSize sizeCrt = m_pCharacter->getContentSize();
//	sizeCrt.width = sizeCrt.width/2;
//	sizeCrt.height = sizeCrt.height/2;
	int indexx = (positionCrt.x-map->getTileSize().width/2)/map->getTileSize().width;
	int	indexy = map->getMapSize().height-(positionCrt.y+map->getTileSize().height/2)/map->getTileSize().height;
	switch(ksrdmap)
	{
	case kLeftMap:
		if((indexx > 0)&&(indexx <layerMap->getLayerSize().width-1))
		{
			return ccp(indexx-1,indexy);
		}
		else
			return ccp(indexx,indexy);
		break;
	case kRightMap:
		if((indexx > 0)&&(indexx <layerMap->getLayerSize().width-1))
		{
			return ccp(indexx+1,indexy);
		}
		else
			return ccp(indexx,indexy);
		break;
	case kUpMap:
		if((indexy > 0)&&(indexy <layerMap->getLayerSize().height-1))
		{
			return ccp(indexx,indexy-1);
		}
		else
			return ccp(indexx,indexy);
		break;
	case kDownMap:
		if((indexy > 0)&&(indexy <layerMap->getLayerSize().height-1))
		{
			return ccp(indexx,indexy+1);
		}
		else
			return ccp(indexx,indexy);
		break;
	default:
		return ccp(-1,-1);
	}
}


void GameScene::beforeMove()
{
//	around[0] = layerMap->tileGIDAt(getSRDMapPoint(kLeftMap));
//	layerMap->setTileGID(left,getSRDMapPoint(kLeftMap));
//	around[1] = layerMap->tileGIDAt(getSRDMapPoint(kUpMap));
//	layerMap->setTileGID(up,getSRDMapPoint(kUpMap));
//	around[2] = layerMap->tileGIDAt(getSRDMapPoint(kDownMap));
//	layerMap->setTileGID(down,getSRDMapPoint(kDownMap));
//	around[3] = layerMap->tileGIDAt(getSRDMapPoint(kRightMap));
//	layerMap->setTileGID(right,getSRDMapPoint(kRightMap));
	moveDisabled = false;
}


CCPoint GameScene::getCRTMapPoint()
{
	CCPoint positionCrt = m_pCharacter->getPosition();
	int indexx = (positionCrt.x-map->getTileSize().width/2)/map->getTileSize().width;
	int	indexy = map->getMapSize().height-(positionCrt.y+map->getTileSize().height/2)/map->getTileSize().height;
	return ccp(indexx,indexy);
}


void GameScene::testMapWay()
{
	for(int indexx = 0;indexx<50;indexx++)
		for(int indexy = 0;indexy<20;indexy++)
		{
		int upGID = layerMap->tileGIDAt(ccp(indexx,indexy));
	if(upGID==133)//在这里修改路的GID值，注意这里GID从1开始
	{
			layerMap->removeTileAt(ccp(indexx,indexy));
	}
		}
}
void GameScene::keyEnterClicked()
{
	if(showWord)
	{
		
	//	CCPoint nowPoint = getCRTMapPoint();
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		wordLayer = CCLayerColor::create(ccc4(175,95,60,200),200,100);
		wordLayer->ignoreAnchorPointForPosition(false);
		wordLayer->setAnchorPoint(ccp(1.0f,0.0f));
//		if(isStart){
			wordLayer->setPosition(ccp(m_pCharacter->getPosition().x+100,m_pCharacter->getPosition().y-50));
//			isStart = false;
//		}
//		else{
//		if(m_pCharacter->getPosition().x<=1360||(640-m_pCharacter->getPosition().y)<160)
//			wordLayer->setPosition(ccp(m_pCharacter->getPosition().x+100,m_pCharacter->getPosition().y+60));//正上方
//		else if(m_pCharacter->getPosition().x>1360||m_pCharacter->getPosition().y>=160)
//			wordLayer->setPosition(ccp(m_pCharacter->getPosition().x-40,m_pCharacter->getPosition().y-50));//正左方
//		else if(m_pCharacter->getPosition().x>1360||m_pCharacter->getPosition().y<160)
//			wordLayer->setPosition(ccp(m_pCharacter->getPosition().x-40,m_pCharacter->getPosition().y+60));//左上方
//		else
//			wordLayer->setPosition(ccp(m_pCharacter->getPosition().x+240,m_pCharacter->getPosition().y-160));//右下方
//		}
		addChild(wordLayer,3);
		CCDictionary * moHa = CCDictionary::dictionaryWithContentsOfFile("mo_Ha.xml");
		std::stringstream ssss; 
		if((getCRTMapPoint().x==10||getCRTMapPoint().x==11)&&(getCRTMapPoint().y==9))
		{
			ssss << 9;
			CCLabelTTF* disire = CCLabelTTF::create(((CCString *)moHa->objectForKey("10"))->getCString(), "华文新魏", 17);
			CCLabelTTF* disireNot = CCLabelTTF::create(((CCString *)moHa->objectForKey("11"))->getCString(), "华文新魏", 17);
			CCMenuItemLabel * itemD = CCMenuItemLabel::create(disire,this,menu_selector(GameScene::desireCallback));
			itemD->setPosition(ccp(100,60));
			itemD->setColor(ccc3(203,27,69));
			CCMenuItemLabel * itemDN = CCMenuItemLabel::create(disireNot,this,menu_selector(GameScene::desireNotCallback));
			itemDN->setPosition(ccp(100,30));
			itemDN->setColor(ccc3(203,27,69));
			wordLayer->addChild(itemD,1);
			wordLayer->addChild(itemDN,1);

		}
		else
		{
			ssss << wordNum;
			wordNum =(wordNum+1)%9;
		}
		const char * words = ((CCString *)moHa->objectForKey(ssss.str()))->getCString();
		CCLabelTTF* wordS = CCLabelTTF::create(words,"华文新魏",15);
		wordS->setAnchorPoint(ccp(0.0f,1.0f)); 
		wordS->setPosition( ccp(10, 90));
		wordS->setDimensions(CCSizeMake(180,90));
		wordS->setHorizontalAlignment(kCCTextAlignmentLeft);
		wordLayer->addChild(wordS,1);

		showWord = false;
		moveDisabled = false;
		
		
	}
	else
	{
		wordLayer->removeFromParentAndCleanup(false);
		showWord = true;
		moveDisabled = true;
	}
}

void GameScene::desireCallback(cocos2d::CCObject *pSender)
{
}

void GameScene::desireNotCallback(cocos2d::CCObject *pSender)
{
}