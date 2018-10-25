#pragma once
#include "../ecs/ecs.h"
#include "./components/components.h"
#include "./components/graphic_components.h"
#include "../commons/sdl2utils.h"

using namespace ecs;

namespace factory {

    Entity& createWithData(Manager& mgr, void* data) {
        auto &e = mgr.addEntity();
        return e;
    }
    
    template<typename ...T>
    Texture* getTexture(const char* fmt, T... args) {
        char buff[255];
        sprintf(buff, fmt, args...);
        return loadTexture(buff);
    }

    Texture* getTexture(const char* type, int id) {
        return getTexture("res/%s/%d.png", type, id);
    }

    Sprite& addSprite(Entity& e, const char* type, int id) {
        Sprite& c = e.addComponent<Sprite>();
        c.texture = getTexture(type, 1);
        c.srcRect.x = c.srcRect.y = 0;
        c.srcRect.w = c.srcRect.h = 32;
        c.dstRect.w = c.dstRect.h = 64;
        return c;
    }

    Entity& createPlayer(Manager &mgr, double x, double y) {
        Entity& e = mgr.addEntity();
        e.addComponent<Position>(x, y);
        e.addComponent<Velocity>();
        e.addComponent<Health>(100);
        addSprite(e, "character", 0);
        mgr.setPlayer(&e);
        return e;
    }
    
    Entity& createMonster(Manager &mgr, double x, double y) {
        Entity& e = mgr.addEntity();
        e.addComponent<Position>(x, y);
        e.addComponent<Velocity>();
        e.addComponent<Health>(100);
        addSprite(e, "character", 1);
        return e;
    }

} // namespace factory
