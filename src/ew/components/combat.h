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
    int defense=0;
    Health(int hp) : maxHitPoint(hp), hitPoint(hp) {}
};

struct MeeleAttack : Component {
    bool attacking;
    EID targetId;
    int frames;
    int hitFrame;
    int frame;
    int attackSpeed;
    int attackPower;
};

struct Bullet {
    int attackPower;
    int range;
    int speed;
    bool traceTarget = true;
};

struct MissleAttack : Component {
    int frames;
    int hitFrame;
    int attackSpeed;
    int minRange;
    int maxRange;
    Bullet bullet;
};

struct Cooldown {
    uint8_t actionType;
    uint16_t actionId;
    uint32_t startTime;
    uint32_t endTime;
};

struct Cooldowns : Component {
    Cooldown global;
    std::vector<Cooldown> list;
};

struct Spell {
    uint16_t id;
};

struct Spells : Component {
    std::vector<Spell> list;
};