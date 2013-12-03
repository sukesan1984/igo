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

Goban::~Goban(){
}