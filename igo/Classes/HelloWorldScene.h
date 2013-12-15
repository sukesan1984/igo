#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Ban.h"
#include "Const.h"

class HelloWorld : public cocos2d::CCLayer
{
    Goban* goban;
    Ban* ban;
    CCLabelTTF* kuroAgehama;
    CCLabelTTF* shiroAgehama;
    CCMenuItemSprite* pPassButton;
    CCMenuItemSprite* pOkButton;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);

    void pass();
    void ok();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    void update();
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
