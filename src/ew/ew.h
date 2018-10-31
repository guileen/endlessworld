#pragma once
#include "gwindow.h"
#include "factory.h"
#include "./systems/combat.h"
#include "./systems/graphics.h"
#include "./systems/input.h"
#include "./systems/physics.h"
#include "./systems/hpbar.h"

/*
 Window/Sub-Systems
    |
    *
 EventBus
    *
    |
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
    GraphicSystem graphicSystem;
    CombatSystem combatSystem;
public:
    EndlessWorld(int width, int height) : GameWindow("endless_world", width, height, false)
    , graphicSystem{manager, *renderer, width*2, height*2}
    , combatSystem{manager}
    {
        start(renderer);
    }
    ~EndlessWorld() {
        free();
    }

    void start(Renderer *r) {
        EventBus.on(EventType::Quit, [this](){
            quit();
        });
        // add game objects.
        factory::createPlayer(manager, 0, 0);
        factory::createMonster(manager, 3, 5);
        factory::createMonster(manager, 5, 2);
        factory::createMonster(manager, 2, 3);
    }

    void loop() {
        manager.refresh();
        handleInputEvent();
        handleInput(manager);
        update_movement(manager);
        combatSystem.update();
        renderer->clear();
        graphicSystem.update();
        updateHPBar(manager, *renderer);
        renderer->present();
    }

};
