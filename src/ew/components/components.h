#pragma once
#include "../../ecs/ecs.h"
#include <stdint.h>
using namespace ecs;

struct Position : Component {
    double x;
    double y;
    Position(double mx, double my) {x = mx; y=my;}
};

struct Velocity : Component {
    double dx=0.f;
    double dy=0.f;
};

struct Health : Component {
    int hitPoint;
    int maxHitPoint;
    Health(int hp) : maxHitPoint(hp), hitPoint(hp) {}
};
