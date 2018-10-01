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

void test(int x, int y) {
    int cx, cy;
    World::getRegionCenterPos(x,y,&cx,&cy);
    // printf("x %d y %d cx %d cy %d\n", x, y, cx, cy);
}

void test2(int x, int y, World* world, int dx, int dy, int dw, int dh) {
    world->updateCurrentRegion(x,y);
    world->debugPrint();
    Uint8 dst[9];
    world->copyRectBlock(dx, dy, dw, dh, dst);
    for(int y=0;y<dh;y++) {
        for(int x=0;x<dw;x++) {
            printf("%02x ", dst[y*dw+x]);
        }
        printf("\n");
    }
    printf("-------------\n");
}

int main(int argc, const char * argv[]) {
    for(int i=-16;i<16;i++) {
        test(i, i);
    }

    World world;
    world.initRegions(0,0);
    test2(0, 0, &world, -1,-1,3,3);
    test2(0, 0, &world, 0,0,3,3);
    test2(4, 0, &world, 6, 1, 3, 3);
    test2(4, 4, &world, 0,0,3,2);
    return 0;

    /*
    test(0,0);
    test(0,1);
    test(511,0);
    test(512,0);
    test(513,0);
    test(511,-511);
    test(-511,-511);
    test(512+randint(1024),512+randint(1024));
    test(-512-randint(1024),-512-randint(1024));
    test(-1024-512-randint(1024),1024+512+randint(1024));
    return 0;
     */

//    srand((int)time(NULL));   // should only be called once
    //Start up SDL and create window
    GameWindow window("GameWindow", 800, 600, false);
    // Enter loading screen
    if(LoadingScreen()) return 1;

    MainScean mainScean(window.getRenderer());
    
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(GameApp::loopFrame, NULL, 0, true);
#else
    GameLoop::run(dynamic_cast<GameScean*>(&mainScean));
#endif
    
    // Free resources
    // ~GameWindow() auto released on stack.
}
