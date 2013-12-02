//
//  Candidate.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#ifndef __igo__Candidate__
#define __igo__Candidate__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Candidate : public CCSprite {
public:
    static Candidate* create(const char *pszFileName);
    Candidate();
    ~Candidate();
};
#endif /* defined(__igo__Candidate__) */
