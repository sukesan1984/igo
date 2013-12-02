//
//  Candidate.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#include "Candidate.h"


Candidate::Candidate(){
}

Candidate::~Candidate(){
}

Candidate* Candidate::create(const char *pszFileName)
{
    Candidate *pobSprite = new Candidate();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}