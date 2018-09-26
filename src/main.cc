//
//  main.cpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "tiledmap.h"
#include <time.h>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDL_Texture* gSplash = NULL;
SDL_Texture* gXOut = NULL;

// fps counter
Uint32 lastFrameTick = 0;
Uint32 lastFPSTick = 0;
int _countedFrames = 0;
float currentFPS;

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

// return true for continue, false for quit
bool MainLoop() {
    //Event handler
    SDL_Event e;
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            return false;
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
        } else if( e.type == SDL_JOYAXISMOTION ) {
            // JoyStick support
//            UpdateJoyStickStateByEvent(e, &xDir, &yDir, 8000);
        } else if( e.type == SDL_JOYBUTTONDOWN ) {
            //Joystick button press
            //Play rumble at 75% strenght for 500 milliseconds
            if( gControllerHaptic && SDL_HapticRumblePlay( gControllerHaptic, 0.75, 500 ) != 0 ) {
                printf( "Warning: Unable to play rumble! %s\n", SDL_GetError() );
            }
        }
    } //Apply the image
    //Set texture based on current keystate
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
        printf("up key down\n");
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
        printf("down key down\n");
    }
    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
        printf("left key down\n");
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
        printf("right key down\n");
    }
    else {
    }
    // Update()

    // Render
    renderWorld(800*2, 600*2, (800 - 640)/2, (600-480)/2 );
    // Calc FPS, Cap FPS
    _countedFrames ++;
    Uint32 currentTick = SDL_GetTicks();
    Uint32 frameTick = currentTick - lastFrameTick;
    if(currentTick-lastFPSTick > 500) {
        currentFPS = _countedFrames * 1000.0 / (currentTick-lastFPSTick) ;
        _countedFrames = 0;
        lastFPSTick = currentTick;
        printf("fps: %.2f\n", currentFPS);
    }
    if(frameTick < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME-frameTick);
    }
    lastFrameTick = currentTick;
    return true;
}

int main(int argc, const char * argv[]) {
    srand((int)time(NULL));   // should only be called once
    //Start up SDL and create window
    if(appInit("SDL tutorial", 800, 600, false)) return 1;
    // Enter loading screen
    if(LoadingScreen()) return 1;
    lastFPSTick = SDL_GetTicks();
    lastFrameTick = SDL_GetTicks();
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(MainLoop, NULL, 0, nk_true);
#else
    while(MainLoop());
#endif
    //Free resources and close SDL
    return appQuit();
}
