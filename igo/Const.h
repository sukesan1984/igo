//
//  Const.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#ifndef igo_Const_h
#define igo_Const_h

enum GOISHI {
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};

enum Const {
    BAN_SIZE = 9
};

enum GAMEMODE{
    PLAY = 1,
    CHECK_SHI = 2
};

struct Jinchi {
   enum Value {
        NONE  = 0,
        WHITE = 1,
        BLACK  = 2,
        BLACK_STONE = 3,//黒石が置かれている。
        WHITE_STONE = 4,//白石が置かれている。
        DAME = 5,
    };
};
#endif
