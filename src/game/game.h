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
#include "map_render.h"
#include "game_object.h"

class MainScean: public GameScean {
    Player* player;
    MapRenderer map;
public:
    MainScean(Renderer* r, int w, int h): GameScean(r){
        init(w, h);
    }
    void init(int w, int h);
    void updateFrame();
    void handleInput();
    void renderScean(Renderer* renderer);
};



#endif /* game_h */
