#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"

USING_NS_CC;

class Character :
	public CCSprite
{
private:
	bool moveDisabled;
	bool leftAble;
	bool rightAble;
	bool upAble;
	bool downAble;
public:
	Character();
	~Character();
};

#endif//_CHARACTER_H_
