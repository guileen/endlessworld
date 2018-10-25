#pragma once
#include "../../ecs/ecs.h"
using namespace ecs;
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
