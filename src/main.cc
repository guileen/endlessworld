//
//  main.cpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "tiledmap.h"
#include <time.h>
#include "game.h"

SDL_Texture* gSplash = NULL;
SDL_Texture* gXOut = NULL;

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
    SDL_Delay( 0 );
    BlitScaled( gXOut, NULL, NULL );
    UpdateScreen();
    SDL_Delay( 0 );
    return 0;
}

int main(int argc, const char * argv[]) {
    srand((int)time(NULL));   // should only be called once
    //Start up SDL and create window
    if(appInit("SDL tutorial", 800, 600, false)) return 1;
    // Enter loading screen
    if(LoadingScreen()) return 1;

    GameScean mainScean(gRenderer);
    
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(GameApp::loopFrame, NULL, 0, true);
#else
    GameLoop::run(&mainScean);
#endif
    
    //Free resources and close SDL
    return appQuit();
}
