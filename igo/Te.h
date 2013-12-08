//
//  Te.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#ifndef __igo__Te__
#define __igo__Te__

#include <iostream>
#include "Const.h"
#include <cassert>
//手を管理するクラス

class Te {
    int x;
    int y;
    GOISHI color;
public:
    int getX();
    int getY();
    GOISHI getColor();
    
    Te(int x, int y, GOISHI color);
    ~Te();
};

#endif /* defined(__igo__Te__) */
