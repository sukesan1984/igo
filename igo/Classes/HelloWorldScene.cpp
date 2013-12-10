#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("goishi.plist");
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
          
    CCSprite* pass = CCSprite::createWithSpriteFrameName("pass.png");
    CCSprite* passOff = CCSprite::createWithSpriteFrameName("pass.png");
    passOff->setColor(ccc3(102,102,102));
    pPassButton =
        CCMenuItemSprite::create(pass, passOff, this, menu_selector(HelloWorld::pass));
    pPassButton->setScale(0.5);
    pPassButton->setPosition(ccp(size.width/2, 50));
    pPassButton->setVisible(true);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pPassButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    goban = new Goban();
    ban = Ban::create("ban.png", goban);
    // position the sprite on the center of the screen
    ban->setPosition( ccp(size.width/2, size.height/2) );
    //ban->setScale(0.55);
    
    kuroAgehama = CCLabelTTF::create(CCString::createWithFormat("黒: %d", goban->getAgehamaKuro() )->getCString(), "Thonburi", 20);
    kuroAgehama->setPosition(ccp(20, size.height - 80));
    kuroAgehama->setAnchorPoint(ccp(0,0));
    this->addChild(kuroAgehama);
    
       
    shiroAgehama = CCLabelTTF::create(CCString::createWithFormat("白: %d", goban->getAgehamaShiro())->getCString(), "Thonburi", 20);
    shiroAgehama->setPosition(ccp(size.width - 20, 50));
    shiroAgehama->setAnchorPoint(ccp(1,0));
    this->addChild(shiroAgehama);
    
    
   // add the sprite as a child to this layer
    this->addChild(ban);
    
    this->schedule(schedule_selector(HelloWorld::update));
    this->setTouchEnabled(true);
    
    return true;
}

void HelloWorld::update(){
    kuroAgehama->setString(CCString::createWithFormat("黒: %d", goban->getAgehamaKuro())->getCString());
    shiroAgehama->setString(CCString::createWithFormat("白: %d", goban->getAgehamaShiro())->getCString());
}


void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;
    
    CCPoint loc;
    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            ban->onTouchStart(touch);
        }
    }
}

void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    CCSetIterator i;
    CCTouch* touch;

    for( i = pTouches->begin(); i != pTouches->end(); i++ ){
        touch = (CCTouch*) (*i);
        if(touch) {
            ban->onTouchMove(touch);
        }
    }
}

void HelloWorld::pass(){
    ban->pass();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
