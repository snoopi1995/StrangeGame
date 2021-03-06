#include "cocos2d.h"

USING_NS_CC;

#define CREATE_FUNC(__TYPE__)\
	static __TYPE__* create()\
{\
	__TYPE__ * pRet = new __TYPE__();\
	if(pRet && pRet->init())\
{\
	pRet->autorelease();\
	return pRet;\
}\
	else\
{\
	delete pRet;\
	pRet = NULL;\
	return NULL;\
}\
}


class PopupLayer : public CCLayer{
public:
    PopupLayer();
    ~PopupLayer();
    virtual bool init();

    virtual void registerWithTouchDispatcher();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

    static PopupLayer* create(const char* backgroundImage);

    void setTitle(const char* title, int fontsize = 20);
 
    void setContentText(const char* text, int fontsize=20, int padding=50, int paddingTop=100);

    void setCallBackFunc(CCObject* target, SEL_CallFuncN callfun);


    bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag=0);

    virtual void onEnter();
    virtual void onExit();

    CREATE_FUNC(PopupLayer);

private:
    void buttonCallBack(CCObject* pSender);

    //文字内容两边的空白区域
    int m_contentPadding;
    int m_contentPaddingTop;
    CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;

    //定义了CCMenu*类型变量m_pMenu, 并且直接定义默认的set/get方法
    CC_SYNTHESIZE_RETAIN(CCMenu*, m_pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_sfBackGround, SpriteBackGround);
//    CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m_s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_ltContentText, LabelContentText);
};