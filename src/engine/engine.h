//
//  engine.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/27.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef engine_h
#define engine_h

#include "sdl2utils.h"
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
    virtual ~GameScean() {};
    virtual void handleInput()=0;
    virtual void updateFrame()=0;
    virtual void render() {};
};

// work like a singleton.
namespace GameLoop {
    void run(GameScean*);
    float getFPS();
    void quit();
}

#endif /* engine_h */
