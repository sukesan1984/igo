//
//  Te.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#ifndef __igo__Te__
#define __igo__Te__

#include <iostream>
#include "Const.h"
#include <cassert>
#include "cocos2d.h"
//手を管理するクラス
using namespace cocos2d;

class Te : public CCObject{
    int x;
    int y;
    GOISHI color;
    bool init();
    int removedNum;
public:
    int getX();
    int getY();
    GOISHI getColor();
    void setRemovedNum(int removedNum);
    int getRemovedNum();
    static Te* createWithPositionAndColor(int x, int y, GOISHI color);
    Te(int x, int y, GOISHI color);
    ~Te();
};

#endif /* defined(__igo__Te__) */
