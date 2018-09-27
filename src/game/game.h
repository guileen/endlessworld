//
//  game.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/27.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef game_h
#define game_h
#include "engine.h"

class MainScean: public GameScean {
public:
    MainScean(SDL_Renderer* r):GameScean(r){}
    void render();
    void updateFrame();
    void handleInput();
};

class GameObject: Sprite {
    int healthPoint;
    int powerPoint;
public:
    void move();
    void attack();
};

class Character:GameObject {
    
};

class Player:Character {
    
};

#endif /* game_h */
