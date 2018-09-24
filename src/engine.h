//
//  engine.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//
//  Game Logic Layer
//  (GN) C Game Engine Layer <- 我们在这
//  Cross platform abstract layer (SDL/GLFW)

//  这个文件定义了基本的引擎接口，对引擎进行隐藏，不暴露任何底层的（SDL／OpenGL／GLFW） 的信息，在必要的时候可以对底层的引擎进行替换，这样可以更方便以后进行引擎的移植。

// 使用G前缀

#ifndef engine_h
#define engine_h
#include <stdbool.h>

#define USE_SDL

#ifdef USE_SDL
// sdl staff
#ifdef __APPLE__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#else

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#endif /* __APPLE__ */

// Graphics
typedef SDL_Surface GSurface;
typedef SDL_Rect GRect;
#define Blit SDL_BlitSurface
#define BlitScaled SDL_BlitScaled

#endif /* USE_SDL */

extern SDL_Window* gWindow;
extern SDL_Surface* gScreen;
extern SDL_GLContext* glContext;

#ifdef __cplusplus
// support C++
extern "C" {
#endif

    // game windows
    int appInit(const char* title, int width, int height, bool fullscreen);
    int appQuit();
    static inline void updateWindow() {
        SDL_UpdateWindowSurface( gWindow );
    }

    // resources
    GSurface* loadImage(const char* path);
    
#ifdef __cplusplus
}
#endif

#endif /* engine_h */
