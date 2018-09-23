//
//  engine_base.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//
//  这个文件定义了基本的引擎接口，对引擎进行隐藏，不暴露任何底层的（SDL／OpenGL／GLFW） 的信息，在必要的时候可以对底层的引擎进行替换，这样可以更方便以后进行引擎的移植。

#ifndef engine_base_h
#define engine_base_h

#include <stdio.h>
#include <stdbool.h>

#ifdef USE_SDL

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif /* __APPLE__ */
// 使用通用的名称 G ，以后若迁移其他渲染框架，将使用 GSurface 进行封装。
typedef SDL_Surface GSurface;
typedef SDL_Rect GRect;
inline void GBlitSurface(GSurface * src, const GRect * srcrect, GSurface * dst, GRect * dstrect) {
    SDL_BlitSurface(src, srcrect, dst, dstrect);
}
#endif /* USE_SDL */

#ifdef __cplusplus
extern "C" {
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* engine_base_h */
