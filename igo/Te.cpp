//
//  Te.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#include "Te.h"

Te::Te(int x, int y, GOISHI color){
    assert(x >= 0 && x < BAN_SIZE);
    assert(y >= 0 && y < BAN_SIZE);
    this->x = x;
    this->y = y;
    this->color = color;
}

Te::~Te(){
}

GOISHI Te::getColor(){
    return color;
}

int Te::getX(){
    return x;
}

int Te::getY(){
    return y;
}