//
//  main.cpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

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
    
    //Load splash image
    gSplash = gn_load_image( "res/images/hello_world.bmp" );
    if( gSplash == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "res/images/hello_world.bmp", SDL_GetError() );
        success = false;
    }
    
    gXOut = gn_load_image("res/images/xout.bmp");
    if( gXOut == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "res/images/xout.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

int LoadingScreen() {
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return -1;
    }
    //Apply the image
    GBlitSurface( gSplash, NULL, gn_get_screen(), NULL );
    //Update the surface
    gn_update_window();
    //Wait two seconds
    SDL_Delay( 2000 );
    GBlitSurface( gXOut, NULL, gn_get_screen(), NULL );
    //Update the surface
    gn_update_window();
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
    // Render
    GBlitSurface( currentSurface, NULL, gn_get_screen(), NULL );
    
    //Update the surface
    gn_update_window();
}

int main(int argc, const char * argv[]) {

    //Start up SDL and create window
    if(gn_init("SDL tutorial", 640, 480, false)) return 1;
    // Enter loading screen
    if(LoadingScreen()) return 1;
    
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(MainLoop, NULL, 0, nk_true);
#else
    while (running) MainLoop();
#endif
    //Free resources and close SDL
    return gn_quit();
}
