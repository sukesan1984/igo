//
//  Ban.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#include "Ban.h"

Ban* Ban::create(const char *pszFileName, Goban* goban)
{
    Ban *pobSprite = new Ban(goban);
    if (pobSprite && pobSprite->initWithSpriteFrameName(pszFileName))
    {
        //最初に全てスプライトは作ってしまう。
        for (int i = 0; i < BAN_SIZE; i++){
            for (int j = 0; j < BAN_SIZE; j++){
                Goishi* ishi = Goishi::create();
                ishi->initWithSpriteFrameName("shiro.png");
                ishi->setPosition(pobSprite->getPos(i, j));
                ishi->setScale(0.546875);
                ishi->setVisible(false);
                ishi->show(NONE);
                pobSprite->addChild(ishi);
                pobSprite->sprites[i][j] = ishi;
            }
        }
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
    if(!this->goban->putGoishi(x, y, goishi)){
        return false;
    }
    this->update();
    
    return true;
}

bool Ban::makeGoishiDead(int x, int y){
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
    float width  = this->getContentSize().width - (OFFSET * 2);
    float height = this->getContentSize().height - (OFFSET * 2);
    
    float posX = ( width / (BAN_SIZE - 1) ) * x + OFFSET;
    float posY = ( height / (BAN_SIZE - 1) ) * y + OFFSET;
    return ccp(posX, posY);
}

void Ban::onTouchStart(cocos2d::CCTouch *touch){
    CCLOG("onTouchStart");
    switch(this->mode){
        case PLAY:
            this->onTouchOnPlayMode(touch);
            break;
        case CHECK_SHI:
            this->onTouchOnCheckShi(touch);
            break;
    }
}

void Ban::onTouchOnPlayMode(cocos2d::CCTouch *touch){
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    CCPoint tapPos = this->getTouchedPos(tap);
    //盤外なら何もしない。
    if(tapPos.x < 0 || tapPos.x > BAN_SIZE -1 || tapPos.y < 0 || tapPos.y > BAN_SIZE - 1){
        return;
    }
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

void Ban::onTouchOnCheckShi(cocos2d::CCTouch *touch){
    CCLOG("死んでる石をチェックする");
    CCPoint tap = CCDirector::sharedDirector()->convertToGL( touch->getLocationInView() );
    CCPoint tapPos = this->getTouchedPos(tap);
    //盤外なら何もしない。
    if(tapPos.x < 0 || tapPos.x > BAN_SIZE -1 || tapPos.y < 0 || tapPos.y > BAN_SIZE - 1){
        return;
    }
    this->sprites[(int) tapPos.x][(int) tapPos.y]->changeDead();
}

void Ban::onTouchMove(cocos2d::CCTouch *touch){
    CCLOG("onTouchMove");
}

void Ban::pass(){
    if(this->goban->getHistory()->getLast()->isPass()){
        mode = CHECK_SHI;
    }
    this->goban->pass();
    turn++;
}

CCPoint Ban::getTouchedPos(cocos2d::CCPoint touchedLocation){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float scale = this->getScale();
    float offSetX = (size.width - this->getContentSize().width * scale) / 2 + OFFSET;
    float offSetY = (size.height - this->getContentSize().height * scale) / 2 + OFFSET;
    
    float masuSize = (this->getContentSize().width - (OFFSET * 2)) * scale / (BAN_SIZE - 1);
    int X = round( (touchedLocation.x - offSetX) / masuSize );
    int Y = round( (touchedLocation.y - offSetY) / masuSize );
    return ccp(X, Y);
}

void Ban::update(){
   for (int i = 0; i < BAN_SIZE; i++){
        for (int j = 0; j < BAN_SIZE; j++){
            Goishi* ishi = this->sprites[i][j];
            GOISHI color = this->goban->getGoishi(i, j);
            ishi->show(color);
        }
   }
}

Ban::Ban(Goban* goban){
    this->turn = 0;
    this->goban = goban;
    mode = PLAY;
}

Ban::~Ban(){
}