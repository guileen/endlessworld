#pragma once
#include "../ecs/ecs.h"

struct Item {

};

struct Equipments {
    static constexpr int HEAD=0;
    static constexpr int BODY=1;
    static constexpr int HAND=2;
    static constexpr int BAGSLOT0=9;
    static constexpr int BAGSLOT1=10;
    static constexpr int BAGSLOT2=11;
    static constexpr int BAGSLOT3=12;
    Item slots[13];
};