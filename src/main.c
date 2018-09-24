//
//  main.cpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "tiledmap.h"
#include "game_res.h"
#include "engine.h"

GSurface* gSplash = NULL;
GSurface* gXOut = NULL;
GSurface* currentSurface;
GSurface* gKeyPressSurfaces[ 5 ];
bool running = true;

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    gXOut = loadImage("res/images/xout.bmp");
    if( gXOut == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "res/images/xout.png", SDL_GetError() );
        success = false;
    }
    for(int i=1;i<=10;i++) loadTileSurface(i);
    return success;
}

int LoadingScreen() {
    //Load splash image
    gSplash = loadImage( "res/images/hello_world.bmp" );
    if( gSplash == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "res/images/hello_world.png", SDL_GetError() );
        return -1;
    }
    SDL_Rect dst = {0, 0, 800, 600};
    //Apply the image
    BlitScaled( gSplash, NULL, gScreen, &dst);
    //Update the surface
    updateWindow();
    
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return -1;
    }
    
    //Wait two seconds
    SDL_Delay( 1000 );
    BlitScaled( gXOut, NULL, gScreen, &dst );
    updateWindow();
    return 0;
}

void MainLoop() {
    //Event handler
    SDL_Event e;
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    currentSurface = gSplash;
                    break;
                default:
                    currentSurface = gXOut;
                    break;
            }
        }
    } //Apply the image
    // Update()
//    GBlitSurface( currentSurface, NULL, gn_get_screen(), NULL );
    // Render
    renderWorld(640, 480, (800 - 640)/2, (600-480)/2 );
    //Update the surface
    updateWindow();
    // TODO fps fix.
    SDL_Delay(30);
}

int main(int argc, const char * argv[]) {

    //Start up SDL and create window
    if(appInit("SDL tutorial", 800, 600, false)) return 1;
    // Enter loading screen
    if(LoadingScreen()) return 1;
    
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(MainLoop, NULL, 0, nk_true);
#else
    while (running) MainLoop();
#endif
    //Free resources and close SDL
    return appQuit();
}
