//
//  History.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#ifndef __igo__History__
#define __igo__History__

//一手目からの履歴を保存する。
#include <iostream>
#include "cocos2d.h"
#include "Te.h"

using namespace cocos2d;

class History: public CCArray{
public:
    void pushTe(Te* te);
    Te* getTe(int tekazu);
    Te* getLast();
    Te* getBeforeLast();//2個前
    CREATE_FUNC(History);
};

#endif /* defined(__igo__History__) */