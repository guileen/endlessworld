//
//  main.cpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "tiledmap.h"
#include <time.h>

SDL_Texture* gSplash = NULL;
SDL_Texture* gXOut = NULL;
bool running = true;

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    gXOut = loadTexture("res/images/xout.bmp");
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
    gSplash = loadTexture( "res/images/hello_world.bmp" );
    if( gSplash == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "res/images/hello_world.png", SDL_GetError() );
        return -1;
    }
    

    
    //Clear screen
    SDL_RenderClear( gRenderer );
    
    UpdateScreen();
    //Apply the image
    BlitScaled( gSplash, NULL, NULL);
    SDL_Color textColor = { 255, 255, 255 };
    GRect dstRect = {200, 300};
    SDL_Texture* txt = textureFromText("Hello world", textColor, NULL, &dstRect.w, &dstRect.h);
    Blit(txt, NULL, &dstRect);
    //Update the surface
    UpdateScreen();
    
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return -1;
    }
    
    //Wait two seconds
    SDL_Delay( 10000 );
    BlitScaled( gXOut, NULL, NULL );
    UpdateScreen();
    SDL_Delay( 1000 );
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
                    printf("up pressed\n");
                    break;
                default:
                    break;
            }
        } else if ( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEWHEEL){
//            int x, y;
//            SDL_GetMouseState( &x, &y );
//            handleMouseEvent(e, x, y);
        }
    } //Apply the image
    // Update()

    // Render
    renderWorld(800*2, 600*2, (800 - 640)/2, (600-480)/2 );
    // TODO fps fix.
    SDL_Delay(30);
}

int main(int argc, const char * argv[]) {
    srand((int)time(NULL));   // should only be called once
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
