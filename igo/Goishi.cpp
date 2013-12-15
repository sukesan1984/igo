//
//  Goishi.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#include "Goishi.h"

Goishi::Goishi(){
    this->color = NONE;
    this->dead = false;
}

Goishi::~Goishi(){
}

Goishi* Goishi::create()
{
    Goishi *pobSprite = new Goishi();
    if (pobSprite && pobSprite->init())
    {
        CCSprite* batsu = CCSprite::createWithSpriteFrameName("batsu.png");
        batsu->setVisible(false);
        pobSprite->batsu = batsu;
        
        CCSprite* jinchi = CCSprite::createWithSpriteFrameName("jinchiShiro.png");
        jinchi->setVisible(false);
        pobSprite->jinchi = jinchi;
        
        pobSprite->addChild(jinchi);
        pobSprite->addChild(batsu);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void Goishi::show(GOISHI color){
    if(color != this->color){
        this->setVisible(true);
        this->setImage(color);
    }
}

void Goishi::setImage(GOISHI color){
    std::string pszFilename;
    switch(color){
        case BLACK:
            pszFilename = "kuro.png";
            this->color = BLACK;
            break;
        case WHITE:
            pszFilename = "shiro.png";
            this->color = WHITE;
            break;
        default:
            pszFilename = "null.png";
            this->color = NONE;
            break;
    }
    CCSpriteFrame* _frame;
    _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFilename.c_str());
    this->setTexture(_frame->getTexture());
    this->setTextureRect(_frame->getRect(), false, _frame->getOriginalSize());
    return;
}

void Goishi::hide(){
    this->setVisible(false);
}

void Goishi::showState(State::Value state){
    switch (state) {
        case State::NONE:
            this->dead = false;
            this->batsu->setVisible(this->dead);
            break;
        case State::REMOVE:
            this->dead = true;
            this->batsu->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
            this->batsu->setVisible(this->dead);
        default:
            break;
    }
}

void Goishi::showJinchi(Jinchi::Value jinchiState){
    std::string pszFilename;
    switch (jinchiState) {
        case Jinchi::WHITE:
            pszFilename = "jinchiShiro.png";
            this->jinchi->setVisible(true);
            break;
        case Jinchi::BLACK:
            pszFilename = "jinchiKuro.png";
            this->jinchi->setVisible(true);
            break;
        default:
            return;
    }
    CCSpriteFrame* _frame;
    _frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFilename.c_str());
    this->jinchi->setTexture(_frame->getTexture());
    this->jinchi->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    this->jinchi->setTextureRect(_frame->getRect(), false, _frame->getOriginalSize());
}