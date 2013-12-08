//
//  Goban.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/03.
//
//

#include "Goban.h"

History* Goban::getHistory(){
    return this->history;
}

int Goban::getAgehamaKuro(){
    return agehamaKuro->get();
}

int Goban::getAgehamaShiro(){
    return agehamaShiro->get();
}

void Goban::setGoishi(int x, int y, GOISHI goishi){
    this->setGoishiKari(x, y, goishi);
    this->history->pushTe(Te::createWithPositionAndColor(x, y, goishi));
}

//実際において、取り除いたりもする。
bool Goban::putGoishi(int x, int y, GOISHI color){
    if (!this->canPutGoishi(x, y, color)){
        return false;
    }
    
    this->setGoishi(x, y, color);
    int removedNum = this->tryToRemoveAround(x, y, this->getGoishi(x, y));
    ((Te*)this->history->getLast())->setRemovedNum(removedNum);
    switch (color) {
        case WHITE:
            agehamaShiro->increase(removedNum);
            break;
        case BLACK:
            agehamaKuro->increase(removedNum);
            break;
        default:
            break;
    }
    
    return true;
}

void Goban::setGoishiKari(int x, int y, GOISHI goishi){
    assert(goishi == WHITE || goishi == BLACK || goishi == NONE);
    assert(x >= 0 && x < BAN_SIZE );
    assert(y >= 0 && y < BAN_SIZE );
    goban[x][y] = goishi;
}

void Goban::unsetGoishi(int x, int y){
    assert(x >= 0 && x < BAN_SIZE );
    assert(y >= 0 && y < BAN_SIZE );
    this->setGoishiKari(x, y, NONE);
}


bool Goban::hasGoishi(int x, int y){
    GOISHI color = this->getGoishi(x, y);
    if(color == WHITE || color == BLACK){
        return true;
    }
    return false;
}

GOISHI Goban::getGoishi(int x, int y){
    assert(x >= 0 && x < BAN_SIZE );
    assert(y >= 0 && y < BAN_SIZE );
    
    return this->goban[x][y];
}

Goban::Goban(){
    history = History::create();
    history->retain();
    koX = -1;
    koY = -1;
    agehamaKuro  = new Agehama();
    agehamaShiro = new Agehama();
    
    for(int i = 0; i < BAN_SIZE; i++){
        for (int j = 0; j < BAN_SIZE; j++){
            goban[i][j] = NONE;
            checkBoard[i][j] = false;
        }
    }
}

int Goban::tryToRemoveAround(int x, int y, GOISHI color){
    //置かれた石と色が違うときだけ
    int removedNum = 0;
    //左
    if(x != 0 && color != this->getGoishi(x-1, y) ){
        //呼吸点を持たないときは、消す処理
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x-1, y, this->getGoishi(x-1, y))){
            this->clearCheckBoard();
            removedNum += this->removeGoishi(x-1, y, this->getGoishi(x-1, y));
        }
    }
    
    //右
    if( x != BAN_SIZE - 1 && color != this->getGoishi(x+1, y)){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x+1, y, this->getGoishi(x+1, y))){
            this->clearCheckBoard();
            removedNum += this->removeGoishi(x+1, y, this->getGoishi(x+1, y));
        }
    }
    
    //下
    if( y != 0 && color != this->getGoishi(x, y-1)){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x, y-1, this->getGoishi(x, y-1))){
            this->clearCheckBoard();
            removedNum += this->removeGoishi(x, y-1 , this->getGoishi(x, y-1));
        }
    }
    
    //上
    if( y != BAN_SIZE - 1 && color != this->getGoishi(x, y+1)){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x, y+1, this->getGoishi(x, y+1))){
            this->clearCheckBoard();
            removedNum += this->removeGoishi(x, y+1, this->getGoishi(x, y+1));
        }
    }
    return removedNum;
}

int Goban::removeGoishi(int x, int y, GOISHI color){
    //既にチェック済みなら何もしない。
    int removedNum = 0;
    if(this->checkBoard[x][y]){
        return removedNum;
    }
    this->checkBoard[x][y] = true;
    if(this->getGoishi(x, y) == color){
        this->setGoishiKari(x, y, NONE);
        removedNum++;
        if(removedNum == 1){
            koX = x;
            koY = y;
        }
    }
    
    //左
    if(x > 0 && this->getGoishi(x-1, y) == color ){
        removedNum += this->removeGoishi(x-1, y, color);
    }
    
    //右
    if(x < (BAN_SIZE-1) && this->getGoishi(x+1, y) == color){
        removedNum += this->removeGoishi(x+1, y, color);
    }
    
    //下
    if(y > 0 && this->getGoishi(x, y-1) == color){
        removedNum += this->removeGoishi(x, y-1, color);
    }
    
    if(y < (BAN_SIZE - 1) && this->getGoishi(x, y+1) == color){
        removedNum += this->removeGoishi(x, y+1, color);
    }
    
    if(removedNum > 1){
        koX = -1;
        koY = -1;
    }
    
    return removedNum;
}

//x, yが呼吸点を回りに持つならば、true
bool Goban::hasKokyuAround(int x, int y, GOISHI color){
    if(color == NONE){
        return true;
    }
    //既にチェック済みならば、false
    if(this->checkBoard[x][y]){
        return false;
    }
    //チェックする。
    this->checkBoard[x][y] = true;
    //同じ色じゃない。
    if(this->getGoishi(x, y) != color){
        return false;
    }
    
    //同じ色のとき。
    //右が呼吸点ならば、
    if(x < (BAN_SIZE - 1)){
        if(this->getGoishi(x + 1, y) == NONE){
            return true;
        } else {
            //右をチェック
            bool right = this->hasKokyuAround(x + 1, y, color);
            //右の石が呼吸点を持っていたら、呼吸点あり。
            if(right){
                return true;
            }
        }
    }
    
    //上をチェック
    if(y < (BAN_SIZE - 1)){
        if(this->getGoishi(x, y + 1) == NONE){
            return true;
        } else {
            bool upper = this->hasKokyuAround(x, y + 1, color);
            if(upper){
                return true;
            }
        }
    }
    
    //左をチェック
    if(x > 0){
        if(this->getGoishi(x-1, y) == NONE){
            return true;
        } else {
            bool left = this->hasKokyuAround(x-1, y, color);
            if(left){
                return true;
            }
        }
    }
    
    //下をチェック
    if(y > 0){
        if(this->getGoishi(x, y-1) == NONE){
            return true;
        } else {
            bool lower = this->hasKokyuAround(x, y-1, color);
            if(lower){
                return true;
            }
        }
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

bool Goban::canPutGoishi(int x, int y, GOISHI color){
    //既に碁石があるところには置けない。
    if(this->hasGoishi(x, y)){
        return false;
    }
    //前の手で取った数が1の時に、前の前の手と同じ場所には置けない。
    Te* lastTe = this->history->getLast();
    if(lastTe && lastTe->getRemovedNum() == 1){
        if(koX ==x && koY == y ){
            return false;
        }
    }
    
    //試しに置く。
    this->setGoishiKari(x, y, color);

    // 置いた先に呼吸点があれば、置ける。
    this->clearCheckBoard();
    if( this->hasKokyuAround(x, y, this->getGoishi(x, y))){
        this->clearCheckBoard();
        //仮置きしたものをとってから、置けるよと返す。
        this->unsetGoishi(x, y);
        return true;
    } else {
    //置いた先に呼吸点が無くても、周りにとれる石があれば、置ける。
        if(this->hasCanGetGoishiAround(x, y)){
            this->unsetGoishi(x, y);
            return true;
        }
    }
    this->clearCheckBoard();
    this->unsetGoishi(x, y);
    return false;
}

bool Goban::hasCanGetGoishiAround(int x, int y){
    GOISHI color = this->getGoishi(x, y);
    //色が違うところだけ見る。
    //左をチェック
    if(x > 0 && color != this->getGoishi(x - 1, y)){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x - 1, y, this->getGoishi(x - 1, y))){
            return true;
        }
    }
    if(x < BAN_SIZE - 1 && color != this->getGoishi(x + 1, y)){
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x + 1, y, this->getGoishi(x + 1, y))){
            return true;
        }
    }
    
    if(y > 0 && color != this->getGoishi(x, y - 1)) {
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x, y - 1, this->getGoishi(x, y - 1))){
            return true;
        }
    }
    
    if(y < BAN_SIZE - 1 && color != this->getGoishi(x, y + 1)) {
        this->clearCheckBoard();
        if(!this->hasKokyuAround(x, y + 1, this->getGoishi(x, y + 1))){
            return true;
        }
    }
    
    return false;
}

Goban::~Goban(){
}