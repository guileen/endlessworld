//
//  game_object.h
//  endlessworld
//
//  Created by 林 桂 on 18/10/4.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef game_object_h
#define game_object_h
#include "engine.h"
#include "game_commons.h"

class GameObject: public Sprite {
    int healthPoint;
    int powerPoint;
public:
    void move();
    void attack();
};

class Character: public GameObject {
    double moveSpeed;
    double maxMoveSpeed;
    double angle=0;
public:
    Position pos;
    void updateFrame() {
        
    }
};

class Player: public Character {
};
#endif /* game_object_h */
