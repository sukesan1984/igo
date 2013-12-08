//
//  Agehama.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#include "Agehama.h"

void Agehama::increase(int num){
    assert(num >= 0);
    this->num += num;
}

int Agehama::get(){
    return num;
}

Agehama::Agehama(){
    num = 0;
}

Agehama::~Agehama(){
}