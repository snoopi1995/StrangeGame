#ifndef _MENU_CONTROLLER_H_
#define _MENU_CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class MenuController :
	public CCLayer
{
public:
	MenuController(void);
	~MenuController(void);

private:
	CCPoint m_tBeginPos;
	CCMenu* m_pItemMenu;
public:
	void menuCallback(CCObject * pSender);
	void closeCallback(CCObject * pSender);
};

#endif