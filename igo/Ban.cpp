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
    
    ishi->setPosition(this->getPos(x, y));//TODO:(x, y)から計算しておく。
    return true;
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

Ban::Ban(){
}

Ban::~Ban(){
}