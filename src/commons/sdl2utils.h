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

#ifndef sdl2utils_h
#define sdl2utils_h
#include <stdbool.h>
#include "cutils.h"

// 控制宏，用于选择不同的底层引擎
#define USE_SDL

// -------------------------
//      SDL2 相关代码
// -------------------------

#ifdef USE_SDL
// sdl staff
#ifdef __APPLE__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#define FONT_DEFAULT "/Library/Fonts/Arial.ttf"
#else

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


#endif /* __APPLE__ */

typedef SDL_Rect GRect;
typedef SDL_Surface GSurface;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_GLContext* glContext;
//extern SDL_Surface* gScreen;
extern SDL_Haptic* gControllerHaptic;


#ifdef USE_SDL_SURFACE
#define Blit(t,sr,dr)       SDL_BlitSurface(t, sr, gScreent, dr)
#define BlitScaled(t,sr,dr) SDL_BlitScaled(t, sr, gScreen, dr)
#define UpdateScreen()      SDL_UpdateWindowSurface(gWindow)
#else
#define Blit(t,sr,dr)       SDL_RenderCopy(gRenderer, t, sr, dr)
#define BlitScaled(t,sr,dr) SDL_RenderCopy(gRenderer, t, sr, dr)
#define UpdateScreen()      SDL_RenderPresent(gRenderer)
#endif

#endif /* USE_SDL */
// -----------------------------------------
//             Global variables
// -----------------------------------------


#ifdef __cplusplus
// support C++
extern "C" {
#endif

    // game windows
    int appInit(const char* title, int width, int height, bool fullscreen);
    int appQuit();
    // resources
    GSurface* loadImage(const char* path);
    SDL_Texture* loadTexture(const char* path);
    SDL_Texture* textureFromText(const char* textureText, SDL_Color textColor, TTF_Font *font, int* w, int* h);
#ifdef __cplusplus
}
#endif

#endif /* sdl2utils_h */
