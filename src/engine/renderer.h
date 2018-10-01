//
//  renderer.hpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/28.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef renderer_h
#define renderer_h
#include "sdl2utils.h"

typedef SDL_Texture Texture;

class Renderer {
private:
    SDL_Renderer* rdr;
public:
    Renderer(SDL_Renderer* sdl_renderer) {
        rdr = sdl_renderer;
    }
    void clear() {
        SDL_RenderClear(rdr);
    }
    void present() {
        SDL_RenderPresent(rdr);
    }
    void renderTexture(Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
        SDL_RenderCopy(rdr, texture, srcrect, dstrect);
    }
    void renderText(const char*);
};

class GameWindow {
private:
    SDL_Window* intWindow;
    Renderer* renderer;
public:
    GameWindow(const char* title, int width, int height, bool fullscreen) {
        appInit(title, width, height, fullscreen);
        // TODO: refactor appInit/appQuit.
        intWindow = gWindow;
        renderer = new Renderer(gRenderer);
    }
    ~GameWindow() {
        free(renderer);
        appQuit();
    }
    inline Renderer* getRenderer(){
        return renderer;
    };
};

#endif /* renderer_h */
