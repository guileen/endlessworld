#pragma once
#include <stdint.h>
#include "../factory.h"

using ActionType=uint32_t;

struct ActionParams {
    ActionType actionType;
    uint32_t actionId;
    EID targetID;
    Position targetPosition;
};

void castAction(Entity& e, const ActionParams& params) {

};

void castMeeleAttack(Entity& e, const ActionParams& params) {
    auto& ma = e.getComponent<MeeleAttack>();
    if(!ma.attacking) {
        ma.attacking = true;
        ma.frame = 0;
        ma.targetId = params.targetID;
    }
};