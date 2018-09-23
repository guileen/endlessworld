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

#define USE_SDL
#include "engine_base.h"

#ifdef USE_SDL
// sdl2 staff
#endif

#ifdef __cplusplus
// support C++
extern "C" {
#endif
    // game windows
    int gn_init(const char* title, int width, int height, bool fullscreen);
    int gn_quit();
    void gn_update_window();
    GSurface* gn_get_screen();
    // resources
    GSurface* gn_load_image(const char* path);
    // 
#ifdef USE_SDL
    SDL_Window* gn_get_window();
#endif
#ifdef __cplusplus
}
#endif

#endif /* engine_h */
