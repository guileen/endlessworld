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
#include <vector>

class Sprite {
    int x,y,w,h;
protected:
    void handleEvent();
    void updateFrame();
    void render();
};

class ComposedSprite {
    std::vector<Sprite> children;
protected:
    void addSprite(Sprite sprite);
};

class GameScean {
private:
    ComposedSprite* rootNode;
    SDL_Renderer* renderer;
public:
    GameScean(SDL_Renderer* _renderer) {
        renderer = _renderer;
    }
    void handleInput();
    void updateFrame();
    void render();
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

// work like a singleton.
namespace GameLoop {
    void run(GameScean*);
    float getFPS();
    void quit();
}
#endif /* game_h */
