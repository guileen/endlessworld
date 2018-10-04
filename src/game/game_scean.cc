//
//  game_scean.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/27.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "game.h"
#include "world_map.h"

void MainScean::init(int w, int h) {
    // Texture* texture = loadTexture("res/tiles/groud/1.png");
    // Sprite* sprite = new Sprite(texture, 60, 60);
    // sprite->x = 100;
    // sprite->y = 200;
    // addElement(sprite);
    Texture* texture2 = loadTexture("res/tiles/groud/5.png");
    player = new Player();
    SDL_Rect r = {0,0,60,60};
    player->init(texture2, w/2, h/2, &r);
    map.initResolution(w, h);
    map.initCenterPosition(0, 0);
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
    const double speed = 0.025;
    if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[SDL_SCANCODE_W] ) {
        printf("up key down\n");
        player->pos.y-=speed;
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[SDL_SCANCODE_S] ) {
        printf("down key down %.3f\n", player->pos.y);
        player->pos.y+=speed;
        printf("down key down2 %.3f\n", player->pos.y);
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] || currentKeyStates[SDL_SCANCODE_A]) {
        printf("left key down\n");
        player->pos.x-=speed;
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ]  || currentKeyStates[SDL_SCANCODE_D]) {
        printf("right key down\n");
        player->pos.x+=speed;
    }
}

void MainScean::updateFrame() {
    printf("update Center Position %.2f %.2f\n", player->pos.x, player->pos.y);
    map.updateCenterPosition(player->pos.x, player->pos.y);
}

void MainScean::renderScean(Renderer* renderer) {
    map.render(renderer);
    player->render(renderer);
}
