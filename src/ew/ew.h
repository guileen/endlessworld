#pragma once
#include "gwindow.h"
#include "factory.h"
#include "./systems/graphics.h"
#include "./systems/input.h"
#include "./systems/physics.h"
#include "./systems/hpbar.h"

/*
 Systems
    |
    `- ecs::Manager
            |
            |----- Entity (SceanGroup)
            |           |
            |           |------ GUIComponent
            |           `------ SceanComponent
            |----- Entity (PlayerGroup)
            `----- Entity (Any)
                    |
                    `----- Component
*/
class EndlessWorld: public GameWindow {
    ecs::Manager manager;
    GraphicSystem* graphicSystem;
public:
    EndlessWorld(int width, int height) : GameWindow("endless_world", width, height, false) {
        start(renderer);
    }
    ~EndlessWorld() {
        free();
    }

    void start(Renderer *r) {
        graphicSystem = new GraphicSystem(manager, *r, 1600, 1200);
        // add game objects.
        factory::createPlayer(manager, 0, 0);
        factory::createMonster(manager, 3, 5);
        factory::createMonster(manager, 5, 2);
        factory::createMonster(manager, 2, 3);
    }

    void exit() {
        if(graphicSystem) delete(graphicSystem);
    }

    void loop() {
        manager.refresh();
        handleEvent();
        handleInput(manager);
        update_movement(manager);
        renderer->clear();
        graphicSystem->update();
        updateHPBar(manager, *renderer);
        renderer->present();
    }

    void handleEvent() {
        //Event handler
        SDL_Event e;
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit();
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
    }
};
