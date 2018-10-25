#pragma once
#include "../components/components.h"

using namespace ecs;

void update_movement(Manager& mgr) {
    mgr.each<Velocity, Position>([](Entity& e, Velocity& v, Position& p) {
        p.x += v.dx;
        p.y += v.dy;
    });
}
