//
//  game_app.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/27.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "game.h"

// work like a singleton.
namespace GameLoop {
    namespace {
        // local access
        GameScean* scean;
        bool running = true;

        const int SCREEN_FPS = 60;
        const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

        // fps counter
        Uint32 lastFrameTick = 0;
        Uint32 lastFPSTick = 0;
        int _countedFrames = 0;
        float FPS;
    }
    
    inline void updateFrame() {
        scean->handleInput();
        // Update()
        scean->updateFrame();
        // Render
        scean->render();
        
        // Calc FPS, Cap FPS
        _countedFrames ++;
        Uint32 currentTick = SDL_GetTicks();
        Uint32 frameTick = currentTick - lastFrameTick;
        if(currentTick-lastFPSTick > 500) {
            FPS = _countedFrames * 1000.0 / (currentTick-lastFPSTick) ;
            _countedFrames = 0;
            lastFPSTick = currentTick;
            printf("fps: %.2f\n", FPS);
        }
        if(frameTick < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME-frameTick);
        }
        lastFrameTick = currentTick;
    }
    
}

void GameLoop::run(GameScean* _scean) {
    scean = _scean;
    lastFPSTick = SDL_GetTicks();
    lastFrameTick = SDL_GetTicks();
    while (running) updateFrame();
}

float GameLoop::getFPS() {
    return FPS;
}

void GameLoop::quit() {
    running = false;
}
