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
#include "History.h"
#include "Te.h"
#include "Agehama.h"

using namespace std;

class Goban{
    History* history;
    //コウのときは抜かれた位置をを保存しておく。
    int koX;
    int koY;
    Agehama* agehamaKuro;
    Agehama* agehamaShiro;
public:
    GOISHI goban[BAN_SIZE][BAN_SIZE]; //何も無い時はundef, WHITE, BLACKが入る。
    Jinchi::Value jinchi[BAN_SIZE][BAN_SIZE];
    State::Value state[BAN_SIZE][BAN_SIZE];
    
    History* getHistory();
    int getAgehamaKuro();
    int getAgehamaShiro();
    
    bool checkBoard[BAN_SIZE][BAN_SIZE];
    
    // goban上にflagを立てる。
    void setGoishi(int x, int y, GOISHI goishi);
    
    // 実際に置く。置けなかったらfalse
    bool putGoishi(int x, int y, GOISHI color);
    
    // changeState
    bool changeGoishiState(int x, int y);
    
    // stateを取得する。
    State::Value getState(int x, int y);
    
    // jinchiを計算して、jinchiに格納する。
    void calcJinchi(int x, int y);
    
    Jinchi::Value getJinchi(int x, int y);
    
    void setJinchi(int x, int y, Jinchi::Value jinchi);
    
    Jinchi::Value changeJinchiState(Jinchi::Value before, Jinchi::Value after);
    
    //仮置き
    void setGoishiKari(int x, int y, GOISHI goishi);
    
    void unsetGoishi(int x, int y);
    
    // すでに、石が置かれているかどうかを判定する。
    bool hasGoishi(int x, int y);
    
    // 置かれた碁石の周りにとれる石があるかを返す。
    bool hasCanGetGoishiAround(int x, int y);
    
    //　置かれた碁石の周りをチェックして消すときは消す。
    int tryToRemoveAround(int x, int y, GOISHI color);
    
    // ある位置の碁石の周りに呼吸点があるかどうかを返す。
    bool hasKokyuAround(int x, int y, GOISHI color);
    
    //碁石を取り除いて、取り除いた数を返す。
    int removeGoishi(int x, int y, GOISHI color);
    
    void clearCheckBoard();
    
    //着手禁止点かどうかを判定する。
    bool canPutGoishi(int x, int y, GOISHI color);
    
    GOISHI getGoishi(int x, int y);
    
    // passする。
    void pass();
    
    // ×がついているところを取り除く。
    void confirm();
    
    Goban();
    ~Goban();
};

#endif /* defined(__igo__Goban__) */
