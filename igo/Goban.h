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
#include <cassert>
#include "Const.h"

using namespace std;

class Goban{
public:
    GOISHI goban[BAN_SIZE][BAN_SIZE]; //何も無い時はundef, WHITE, BLACKが入る。
    bool checkBoard[BAN_SIZE][BAN_SIZE];
    // goban上にflagを立てる。
    void setGoishi(int x, int y, GOISHI goishi);
    
    void unsetGoishi(int x, int y);
    
    // すでに、石が置かれているかどうかを判定する。
    bool hasGoishi(int x, int y);
    
    // 置かれた碁石の周りにとれる石があるかを返す。
    bool hasCanGetGoishiAround(int x, int y);
    
    //　置かれた碁石の周りをチェックして消すときは消す。
    void tryToRemoveAround(int x, int y, GOISHI color);
    
    // ある位置の碁石の周りに呼吸点があるかどうかを返す。
    bool hasKokyuAround(int x, int y, GOISHI color);
    
    void removeGoishi(int x, int y, GOISHI color);
    
    void clearCheckBoard();
    
    //着手禁止点かどうかを判定する。
    bool canPutGoishi(int x, int y, GOISHI color);
    
    GOISHI getGoishi(int x, int y);
    
    Goban();
    ~Goban();
};

#endif /* defined(__igo__Goban__) */
