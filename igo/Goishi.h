//
//  Goishi.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#ifndef __igo__Goishi__
#define __igo__Goishi__

#include <iostream>
#include "cocos2d.h"
#include "Const.h"

using namespace cocos2d;

class Goishi : public CCSprite{
    GOISHI color;
    CCSprite* batsu;
    CCSprite* jinchi;
    bool dead;
public:
    static Goishi* create();
    void setImage(GOISHI color);
    void show(GOISHI color);//colorの色を表示する。
    void hide();
    void showState(State::Value state);
    void showJinchi(Jinchi::Value jinchiState);
    Goishi();
    ~Goishi();
};

#endif /* defined(__igo__Goishi__) */