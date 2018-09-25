//
//  engine.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "engine.h"

SDL_Window* gWindow;
SDL_Surface* gScreen;
SDL_Renderer* gRenderer;
SDL_GLContext* glContext;

int appInit(const char* title, int width, int height, bool fullscreen) {
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
    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 2;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 3;
    }
    
    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 4;
    }
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    // glContext = SDL_GL_CreateContext(gWindow);
    
    /* OpenGL setup */
    // glViewport(0, 0, width, height);
    
    // ctx = nk_sdl_init(win);
    
    /*
    //Get window surface
    gScreen = SDL_GetWindowSurface( gWindow );
    if (gScreen == NULL) {
        printf( "WindowSurface could not be get! SDL Error: %s\n", SDL_GetError() );
        return 5;
    }
     */
    
    return 0;
}

int appQuit() {
    printf("TODO: FreeSurface(all loaded resources)");
    SDL_DestroyRenderer( gRenderer );

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    return 0;
}

GSurface* loadImage(const char* path) {
    const char* ext = get_filename_ext(path);
    SDL_Surface* loadedSurface = NULL;
    if(streql(ext, "bmp")) {
        loadedSurface = SDL_LoadBMP(path);
        if( loadedSurface == NULL ) {
            printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        }
    } else if (streql(ext, "png")) {
        loadedSurface = IMG_Load(path);
        if( loadedSurface == NULL ) {
            printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        }
    } else {
        printf("loadImage: %s,  %s not support yet!\n", path, ext);
    }
    return loadedSurface;
    /*
    //Convert surface to screen format
    SDL_Surface* optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreen->format, 0);
    if( optimizedSurface == NULL )
    {
        printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        return loadedSurface;
    }
    
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    return optimizedSurface;
    */
}

SDL_Texture* loadTexture(const char* path) {
    SDL_Surface* loadedSurface = loadImage(path);
    //Color key image
//    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    //Create texture from surface pixels
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
    }
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    return newTexture;
}
