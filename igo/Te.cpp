//
//  Te.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#include "Te.h"
bool Te::init(){
    return true;
}

Te* Te::createWithPositionAndColor(int x, int y, GOISHI color){
   	Te * pRet = new Te(x, y, color);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

Te* Te::createPass(){
    Te* pRet = new Te();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

bool Te::isPass(){
    return this->pass;
}

Te::Te(int x, int y, GOISHI color){
    assert(x >= 0 && x < BAN_SIZE);
    assert(y >= 0 && y < BAN_SIZE);
    this->x = x;
    this->y = y;
    this->color = color;
    this->removedNum = 0;
    this->pass = false;
}

Te::Te(){
    this->x = -1;
    this->y = -1;
    this->color = NONE;
    this->removedNum = 0;
    this->pass = true;
}

Te::~Te(){
}

int Te::getX(){
    return x;
}

int Te::getY(){
    return y;
}

GOISHI Te::getColor(){
    return color;
}

void Te::setRemovedNum(int removedNum){
    this->removedNum = removedNum;
    
}

int Te::getRemovedNum(){
    return this->removedNum;
}