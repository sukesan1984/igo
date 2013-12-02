//
//  Goishi.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#ifndef __igo__Goishi__
#define __igo__Goishi__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Goishi : public CCSprite{
public:
    static Goishi* create(const char *pszFileName);
    Goishi();
    ~Goishi();
};

#endif /* defined(__igo__Goishi__) */