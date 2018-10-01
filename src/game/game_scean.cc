//
//  game_scean.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/27.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "game.h"
#include "tiledmap.h"


void MainScean::init() {
    Texture* texture = loadTexture("res/tiles/groud/1.png");
    Texture* texture2 = loadTexture("res/tiles/groud/5.png");
    Sprite* sprite = new Sprite(texture, 60, 60);
    player = new Sprite(texture2, 60, 60);
    sprite->x = 100;
    sprite->y = 200;
    addElement(sprite);
    addElement(player);
}

void MainScean::handleInput() {
    //Event handler
    SDL_Event e;
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT ) {
            GameLoop::quit();
        }
        Uint32 type = e.type;
        if (type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    printf("up pressed\n");
                    break;
                default:
                    break;
            }
        } else if ( type == SDL_MOUSEMOTION || type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEBUTTONUP || type == SDL_MOUSEWHEEL){
            //            int x, y;
            //            SDL_GetMouseState( &x, &y );
            //            handleMouseEvent(e, x, y);
        } else if( type == SDL_JOYAXISMOTION ) {
            // JoyStick support
            //            UpdateJoyStickStateByEvent(e, &xDir, &yDir, 8000);
        } else if( type == SDL_JOYBUTTONDOWN ) {
            //Joystick button press
            //Play rumble at 75% strenght for 500 milliseconds
            if( gControllerHaptic && SDL_HapticRumblePlay( gControllerHaptic, 0.75, 500 ) != 0 ) {
                printf( "Warning: Unable to play rumble! %s\n", SDL_GetError() );
            }
        }
        
    } //Apply the image
    //Set texture based on current keystate
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    const int speed = 2;
    if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[SDL_SCANCODE_W] ) {
        printf("up key down\n");
        player->y-=speed;
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[SDL_SCANCODE_S] ) {
        printf("down key down\n");
        player->y+=speed;
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] || currentKeyStates[SDL_SCANCODE_A]) {
        printf("left key down\n");
        player->x-=speed;
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ]  || currentKeyStates[SDL_SCANCODE_D]) {
        printf("right key down\n");
        player->x+=speed;
    }
}

void MainScean::updateFrame() {
    
}

void MainScean::render() {
//    renderWorld(800*2, 600*2, (800 - 640)/2, (600-480)/2 );
    
}
