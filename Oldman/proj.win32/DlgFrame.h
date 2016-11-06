#ifndef _DLG_FRAME_H_
#define _DLG_FRAME_H_

#include "cocos2d.h"

USING_NS_CC;

enum
{
	kTagName = 1,
	kTagHead,
	kTagTalk,
};

class DlgFrame :
	public CCLayer
{
public:

	//data
	void setName(int nameNum);//nameNum is given by XML file
	void setHeadImage(const char * filename);
	void setWords(const char * XMLfilename, int wordNum);

};

#endif//_DLG_FRAME_H_
