#include "DlgFrame.h"


void DlgFrame::setName(int nameNum)
{
	if (getChildByTag(kTagName) != NULL)
		removeChildByTag(kTagName,true);
	std::stringstream stringcount; 
	stringcount << 0;

	CCDictionary * dictName = CCDictionary::dictionaryWithContentsOfFile("dict/characterName.xml");
	const char * wordName = ((CCString *)dictName->objectForKey("0"))->getCString();
	CCLabelTTF* words = CCLabelTTF::create(wordName, "华文新魏", 20);
	words->setAnchorPoint(ccp(0.0f, 0.0f));
	words->setColor(ccc3(0, 0, 0));
	words->setPosition(ccp(30.0f, 30.0f));
	addChild(words, 5, kTagName);
}

void DlgFrame::setHeadImage(const char * filename)
{
	if (getChildByTag(kTagHead) != NULL)
		removeChildByTag(kTagHead,true);
    CCSprite * pHead = CCSprite::create(filename);
	pHead->setPosition(ccp(70.0f, 120.0f));
	addChild(pHead, 5, kTagHead);
}
void DlgFrame::setWords(const char * XMLfilename, int wordNum)
{
	if (getChildByTag(kTagTalk) != NULL)
		removeChildByTag(kTagTalk,true);
	std::stringstream stringcount; 
	stringcount << wordNum;

	CCDictionary * dictName = CCDictionary::dictionaryWithContentsOfFile(XMLfilename);
	const char * wordName = ((CCString *)dictName->objectForKey(stringcount.str()))->getCString();
	CCLabelTTF* words = CCLabelTTF::create(wordName, "华文新魏", 25);
	words->setAnchorPoint(ccp(0.0f, 1.0f));
	words->setColor(ccc3(0, 0, 0));
	words->setPosition(ccp(150.0f, 160.0f));
	words->setDimensions(CCSizeMake(470,350));
	words->setHorizontalAlignment(kCCTextAlignmentLeft);
	addChild(words, 5, kTagTalk);
}