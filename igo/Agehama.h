//
//  Agehama.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#ifndef __igo__Agehama__
#define __igo__Agehama__

#include <iostream>
#include <cassert>

class Agehama {
    int num;
public:
    void increase(int num);
    int get();
    Agehama();
    ~Agehama();
};

#endif /* defined(__igo__Agehama__) */
