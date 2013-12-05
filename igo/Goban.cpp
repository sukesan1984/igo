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
            checkBoard[i][j] = false;
        }
    }
}

void Goban::tryToRemoveAround(int x, int y, GOISHI color){
    //置かれた石と色が違うときだけ
    //左
    if(x != 0 && color != this->goban[x-1][y] ){
        //呼吸点を持たないときは、消す処理
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x-1, y, this->goban[x-1][y])){
            this->clearCheckBoard();
            this->removeGoishi(x-1, y, this->goban[x-1][y]);
        }
    }
    
    //右
    if( x != BAN_SIZE - 1 && color != this->goban[x+1][y]){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x+1, y, this->goban[x+1][y])){
            this->clearCheckBoard();
            this->removeGoishi(x+1, y, this->goban[x+1][y]);
        }
    }
    
    //下
    if( y != 0 && color != this->goban[x][y-1]){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x, y-1, this->goban[x][y-1])){
            this->clearCheckBoard();
            this->removeGoishi(x, y-1 , this->goban[x][y-1]);
        }
    }
    
    //上
    if( y != BAN_SIZE - 1 && color != this->goban[x][y+1]){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x, y+1, this->goban[x][y+1])){
            this->clearCheckBoard();
            this->removeGoishi(x, y+1, this->goban[x][y+1]);
        }
    }
}

void Goban::removeGoishi(int x, int y, GOISHI color){
    //既にチェック済みなら何もしない。
    if(this->checkBoard[x][y]){
        return;
    }
    this->checkBoard[x][y] = true;
    if(this->goban[x][y] == color){
        this->goban[x][y] = NONE;
    }
    
    //左
    if(x != 0 && this->goban[x-1][y] == color ){
        this->removeGoishi(x-1, y, color);
    }
    
    //右
    if(x != BAN_SIZE -1 && this->goban[x+1][y] == color){
        this->removeGoishi(x+1, y, color);
    }
    
    //下
    if(y != 0 && this->goban[x][y-1] == color){
        this->removeGoishi(x, y-1, color);
    }
    
    if(y != BAN_SIZE - 1 && this->goban[x][y+1] == color){
        this->removeGoishi(x, y+1, color);
    }
}

//x, yが呼吸点を回りに持つならば、true
bool Goban::hasKokyuAround(int x, int y, GOISHI color){
    //既にチェック済みならば、false
    if(this->checkBoard[x][y]){
        return false;
    }
    //チェックする。
    this->checkBoard[x][y] = true;
    //同じ色じゃない。
    if(this->goban[x][y] != color){
        return false;
    }
    
    //同じ色のとき。
    //右が呼吸点ならば、
    if(x != (BAN_SIZE - 1) && this->goban[x+1][y] == NONE){
        return true;
    }
    //右をチェック
    bool right = this->hasKokyuAround(x + 1, y, color);
    //右の石が呼吸点を持っていたら、呼吸点あり。
    if(right){
        return true;
    }
    
    //上をチェック
    if(y != (BAN_SIZE - 1) && this->goban[x][y+1] == NONE){
        return true;
    }
    bool upper = this->hasKokyuAround(x, y + 1, color);
    if(upper){
        return true;
    }
    
    //左をチェック
    if(x != 0 && this->goban[x-1][y] == NONE){
        return true;
    }
    bool left = this->hasKokyuAround(x-1, y, color);
    if(left){
        return true;
    }
    
    //下をチェック
    if(y != 0 && this->goban[x][y-1] == NONE){
        return true;
    }
    bool lower = this->hasKokyuAround(x, y-1, color);
    if(lower){
        return true;
    }
    
    return false;
}



void Goban::clearCheckBoard(){
    for(int i = 0; i < BAN_SIZE; i++){
        for (int j = 0; j < BAN_SIZE; j++){
            checkBoard[i][j] = false;
        }
    }
}

Goban::~Goban(){
}