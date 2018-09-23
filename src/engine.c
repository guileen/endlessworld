//
//  engine.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "cutils.h"
#include "engine.h"

SDL_Window* g_window;
SDL_Surface* g_screen;
SDL_GLContext* glContext;

int gn_init(const char* title, int width, int height, bool fullscreen) {
    /* GUI */
//    struct nk_context *ctx;
//    SDL_GLContext glContext;
    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

    //Initialization flag
    int flag=SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS ); /*// - do NOT init SDL on GL ES 2*/
    //Initialize SDL
    if( flag < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Create window
    g_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI );
    if( g_window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 2;
    }
    
    //Get window surface
    g_screen = SDL_GetWindowSurface( g_window );
    return 0;
    
    // glContext = SDL_GL_CreateContext(g_window);
    
    /* OpenGL setup */
    // glViewport(0, 0, width, height);
    
    // ctx = nk_sdl_init(win);
}

int gn_quit() {
    printf("TODO: SDL_FreeSurface(all loaded resources)");
    
    //Destroy window
    SDL_DestroyWindow( g_window );
    g_window = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
    return 0;
}

void gn_update_window() {
    SDL_UpdateWindowSurface( g_window );
}

GSurface* gn_get_screen() {
    return g_screen;
}

GSurface* gn_load_image(const char* path) {
    const char* ext = get_filename_ext(path);
    GSurface* s = NULL;
    if(streql(ext, "bmp")) {
        s = SDL_LoadBMP(path);
        if( s == NULL ) {
            printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        }
    } else {
        printf("gn_load_image: %s not support yet!\n", ext);
    }
    return s;
}
