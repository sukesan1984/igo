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

Goishi* Goishi::create(const char *pszFileName)
{
    Goishi *pobSprite = new Goishi();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}