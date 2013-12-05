//
//  Goishi.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#include "Goishi.h"

Goishi::Goishi(){
}

Goishi::~Goishi(){
}

Goishi* Goishi::create()
{
    Goishi *pobSprite = new Goishi();
    if (pobSprite && pobSprite->init())
    {
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
            this->hide();
            this->color = NONE;
            return;
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