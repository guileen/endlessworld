#pragma once
#include "../factory.h"
#include "../../ecs/event_bus.h"

void handleInput(Manager& mgr) {
    //Set texture based on current keystate
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    const double speed = 0.025;
    auto& player = mgr.getPlayer();
    auto& v = player.getComponent<Velocity>();
    v.dx = v.dy = 0;
    if( currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[SDL_SCANCODE_W] ) {
        printf("up key down\n");
        v.dy = -speed;
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] || currentKeyStates[SDL_SCANCODE_S] ) {
        v.dy = speed;
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] || currentKeyStates[SDL_SCANCODE_A]) {
        printf("left key down\n");
        v.dx = -speed;
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ]  || currentKeyStates[SDL_SCANCODE_D]) {
        printf("right key down\n");
        v.dx = speed;
    }
}

void handleInputEvent() {
    //Event handler
    SDL_Event e;
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT ) {
            EventBus.emit(EWEvents::Quit);
        }
        Uint32 type = e.type;
        if (type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                {
                    EventBus.emit(EWEvents::ActionAttack);
                    break;
                }
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
}
