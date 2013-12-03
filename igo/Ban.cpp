//
//  Ban.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#include "Ban.h"

Ban* Ban::create(const char *pszFileName)
{
    Ban *pobSprite = new Ban();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool Ban::putGoishi(int x, int y, GOISHI goishi){
    CCAssert(x >= 0 && x <= BAN_SIZE - 1, "x must be defined");
    CCAssert(y >= 0 && y <= BAN_SIZE - 1, "y must be defined");
    CCAssert(goishi, "WHITE or BLACK must be defined");
    Goishi* ishi;
    if (this->hasGoishi(x, y)){
        return false;
    }
    switch(goishi){
        case WHITE:
            ishi = Goishi::create("shiro.png");
            break;
        case BLACK:
            ishi = Goishi::create("kuro.png");
            break;
        default:
            return false;
    }
    this->addChild(ishi);
    this->setScale(this->getScale());
    this->setGoishi(x, y);
    
    ishi->setPosition(this->getPos(x, y));
    
    return true;
}

void Ban::setGoishi(int x, int y){
    goban[x][y] = 1;
}

bool Ban::hasGoishi(int x, int y){
    if(goban[x][y] == 1){
        return true;
    }
    return false;
}

bool Ban::showCandidate(int x, int y){
    CCAssert(x >= 0 && x <= BAN_SIZE - 1, "x must be defined");
    CCAssert(y >= 0 && y <= BAN_SIZE - 1, "y must be defined");
    Candidate* candidate = Candidate::create("candidate.png");
    
    this->addChild(candidate);
    this->setScale(this->getScale());
    candidate->setPosition(this->getPos(x, y));
    return true;
}

CCPoint Ban::getPos(int x, int y){
    CCAssert(x >= 0 && x <= BAN_SIZE - 1, "x must be defined");
    CCAssert(y >= 0 && y <= BAN_SIZE - 1, "y must be defined");
    float width  = this->getContentSize().width;
    float height = this->getContentSize().height;
    
    float posX = ( width / (BAN_SIZE - 1) ) * x;
    float posY = ( height / (BAN_SIZE - 1) ) * y;
    return ccp(posX, posY);
}

void Ban::onTouchStart(cocos2d::CCTouch *touch){
    CCLOG("onTouchStart");
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    CCPoint tapPos = this->getTouchedPos(tap);
    GOISHI type;
    if(turn % 2){
        type = WHITE;
    } else {
        type = BLACK;
    }
    if( this->putGoishi(tapPos.x, tapPos.y, type) ){
        turn++;
    }
}

void Ban::onTouchMove(cocos2d::CCTouch *touch){
    CCLOG("onTouchMove");
}

CCPoint Ban::getTouchedPos(cocos2d::CCPoint touchedLocation){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float scale = this->getScale();
    float offSetX = (size.width - this->getContentSize().width * scale) / 2;
    float offSetY = (size.height - this->getContentSize().height * scale) / 2;
    
    float masuSize = this->getContentSize().width * scale / (BAN_SIZE - 1);
    int X = round( (touchedLocation.x - offSetX) / masuSize );
    int Y = round( (touchedLocation.y - offSetY) / masuSize );
    return ccp(X, Y);
}

Ban::Ban(){
    turn = 0;
}

Ban::~Ban(){
}