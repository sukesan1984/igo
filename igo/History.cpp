//
//  History.cpp
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#include "History.h"


void History::pushTe(Te *te){
    this->addObject((CCObject*) te);
}



Te* History::getTe(int tekazu){
    if(this->count() < tekazu){
        return NULL;
    }
    
    return (Te*) this->objectAtIndex(tekazu - 1);
}

Te* History::getLast(){
    if(this->count() == 0){
        return NULL;
    }
    
    return (Te*) this->lastObject();
}

Te* History::getBeforeLast(){
    if(this->count() == 1){
        return NULL;
    }
    return (Te*) this->objectAtIndex(this->count() - 2);
}

void History::pushPass(){
    this->addObject(Te::createPass());
}
