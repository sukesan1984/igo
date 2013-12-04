//
//  Goban.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/03.
//
//

#include "Goban.h"

void Goban::setGoishi(int x, int y, GOISHI goishi){
    goban[x][y] = goishi;
}

bool Goban::hasGoishi(int x, int y){
    if(goban[x][y] == WHITE || goban[x][y] == BLACK){
        return true;
    }
    return false;
}

Goban::Goban(){
    for(int i = 0; i < BAN_SIZE; i++){
        for (int j = 0; j < BAN_SIZE; j++){
            goban[i][j] = NONE;
        }
    }
}

bool Goban::hasKokyuAround(int x, int y){
    //左(x - 1)
    //左端の時は、左には呼吸点無し。
    if(x != 0 && goban[x-1][y] == NONE){
        return true;
    }
    //右(x + 1)
    //右端の時は、右には呼吸点無し。
    if(x != (BAN_SIZE - 1) && goban[x+1][y] == NONE){
        return true;
    }
    //下(y - 1)
    //下端の時は、下には呼吸点無し。
    if(y != 0 && goban[x][y-1] == NONE){
        return true;
    }
    //上(y + 1)
    //上端の時は、上には呼吸点無し。
    if(y != (BAN_SIZE - 1) && goban[x][y+1] == NONE){
        return true;
    }
    return false;
}

Goban::~Goban(){
}