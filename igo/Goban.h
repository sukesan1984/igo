//
//  Goban.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/03.
//
//

#ifndef __igo__Goban__
#define __igo__Goban__

#include <iostream>
#include "Const.h"

class Goban{
public:
    GOISHI goban[BAN_SIZE][BAN_SIZE]; //何も無い時はundef, WHITE, BLACKが入る。
    // goban上にflagを立てる。
    void setGoishi(int x, int y, GOISHI goishi);
    
    // すでに、石が置かれているかどうかを判定する。
    bool hasGoishi(int x, int y);
    Goban();
    ~Goban();
};

#endif /* defined(__igo__Goban__) */
