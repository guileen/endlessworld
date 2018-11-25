#pragma once

#include "sdl2utils.h"
#include "graphic_interfaces.h"

class GameWindow : public Renderer, public SceanManager{
private:
    SDL_Window* pWindow;
    SDL_Renderer* renderer;
    bool running = true;
    // screen
    int screenWidth;
    int screenHeight;

    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    // fps counter
    Uint32 lastFrameTick = 0;
    Uint32 lastFPSTick = 0;
    int _countedFrames = 0;
    float FPS;

    // disable default constructors.
    GameWindow(){};
  public:
    GameWindow(const char* title, int width, int height, bool fullscreen) {
        appInit(title, width, height, fullscreen);
        pWindow = gWindow;
        renderer = gRenderer;
        // TODO: high resolution....
        screenWidth = width * 2;
        screenHeight = height * 2;
    }
    ~GameWindow() {
        appQuit();
    }

    SDL_Renderer* _getSDLRenderer() {
        return renderer;
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

    // methods inherite from Renderer
    void clear() {
        SDL_RenderClear(renderer);
    }
    void present() {
        SDL_RenderPresent(renderer);
    }
    void renderTexture(Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
        SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    }
    void renderRect(Rect* rect, Color c) {
        // no need to preserve color.
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer, rect);
    }
    void renderText(const char*) {}

    // Game loop
    inline void updateFrame() {
        Uint32 currentTick = SDL_GetTicks();
        scean->handleInput();
        // Update()
        scean->updateFrame(currentTick);
        // Render
        clear();
        scean->render(this);
        present();
        
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