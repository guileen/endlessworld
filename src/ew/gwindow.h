#pragma once
#include "sdl_renderer.h"

class GameWindow {
private:

    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    // fps counter
    Uint32 lastFrameTick = 0;
    Uint32 lastFPSTick = 0;
    int _countedFrames = 0;
protected:
    SDL_Window* pWindow;
    Renderer* renderer;
    bool running = true;
    // screen
    int screenWidth;
    int screenHeight;
    float FPS;

public:
    virtual void loop() = 0;

public:
    GameWindow(const char* title, int width, int height, bool fullscreen) {
        appInit(title, width, height, fullscreen);
        pWindow = gWindow;
        renderer = new SDLRenderer(gRenderer);
        // TODO: high resolution....
        screenWidth = width * 2;
        screenHeight = height * 2;
        // game init.
    }
    virtual ~GameWindow() {
        appQuit();
        free();
    }
    
    void free() {
        if(renderer) {
            delete(renderer);
            renderer = NULL;
        }
    }

    // methods inherite from SceanManager
    int getScreenWidth() {
        return screenWidth;
    }
    int getScreenHeight() {
        return screenHeight;
    }
    void quit() {
        running = false;
    }

    // Game loop
    inline void updateFrame() {
        Uint32 currentTick = SDL_GetTicks();
        // call virtual method.
        loop();
        // Calc FPS, Cap FPS
        _countedFrames ++;
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

    void runLoop() {
        lastFPSTick = SDL_GetTicks();
        lastFrameTick = SDL_GetTicks();
        while (running) updateFrame();
    }

    float getFPS() {
        return FPS;
    }

};
