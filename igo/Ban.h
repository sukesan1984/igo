//
//  Ban.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#ifndef __igo__Ban__
#define __igo__Ban__

#include <iostream>
#include "cocos2d.h"
#include "Const.h"
#include "Goishi.h"
#include "Candidate.h"
using namespace cocos2d;

class Ban : public CCSprite {
    int turn; //何手目か
    CCDictionary* banmen;
public:
    static Ban* create(const char *pszFileName);
    // 置く候補を立てる。
    // 候補があれば候補の位置に石を置く。
    // 座標に石（黒 or 白)を置く。置けたら:true, 置けなかったら:false
    bool putGoishi(int x, int y, GOISHI goishi);
    // 候補を表示する。
    bool showCandidate(int x, int y);
    
    void onTouchStart(CCTouch* touch);
    void onTouchMove(CCTouch* touch);
    
    CCPoint getPos(int x, int y);
    CCPoint getTouchedPos(CCPoint touchedLocation);
    Ban();
    ~Ban();
};

#endif /* defined(__igo__Ban__) */