//
//  game_object.c
//  endlessworld
//
//  Created by 林 桂 on 18/10/4.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "game_object.h"
#include "game_scean.h"

void GameObject::updateFrame(uint32_t tick) {
}

void GameObject::render(Renderer* r) {
    // world Coordinate to screen Coordinate.
    scean->positionToScreen(pos, &x, &y);
    Sprite::render(r);
}

void Character::updateFrame(uint32_t tick) {
    if(isAttacking) {
        printf("is Attacking\n");
        if(++currentFrame == attackHitFrame) {
            // do hit.
            target->onHit(damage);
        } else if(currentFrame>=attackFrames) {
            currentFrame = 0;
            isAttacking = false;
        }
        return;
    }
    if(aiState.type == AI_TYPE_NONE) {

    }
    else if(aiState.type == AI_TYPE_WANDER) {
        if(aiState.state == AI_STATE_LEAVE_COMBAT) {
            double dx = aiState.targetPos.x - pos.x;
            double dy = aiState.targetPos.y - pos.y;
            double dr = sqrt(dx * dx + dy * dy);
            if(dr >= 0.02) {
                pos.x += 0.02 * dx / dr;
                pos.y += 0.02 * dy / dr;
            }
            else {
                aiState.state = AI_STATE_LOOKAROUND;
                aiState.endTick = tick + 0;
            }
        }
        else if(aiState.state == AI_STATE_COMBAT) {
            if(abs(scean->player->pos.x - pos.x) > 2 || abs(scean->player->pos.y - pos.y) > 2) {
                // Too far go back
                aiState.state = AI_STATE_LEAVE_COMBAT;
            } else {
                // Try to get the enemy.
                double dx = scean->player->pos.x - pos.x;
                double dy = scean->player->pos.y - pos.y;
                double dr = sqrt(dx * dx + dy * dy);
                if(dr >= 0.2) {
                    pos.x += 0.02 * dx / dr;
                    pos.y += 0.02 * dy / dr;
                }
                else if (aiState.globalCooldownTick <= tick) {
                    this->attack(target);
                }
            }
        } else {
            if(abs(scean->player->pos.x - pos.x) < 1 && abs(scean->player->pos.y - pos.y) < 1) {
            // try to chasing player
                aiState.state = AI_STATE_COMBAT;
                target = scean->player;
            } else if(aiState.state == AI_STATE_MOVING) {
                double dx = aiState.targetPos.x - pos.x;
                double dy = aiState.targetPos.y - pos.y;
                double dr = sqrt(dx * dx + dy * dy);
                if(dr >= 0.01) {
                    pos.x += 0.01 * dx / dr;
                    pos.y += 0.01 * dy / dr;
                }
                else {
                    aiState.state = AI_STATE_LOOKAROUND;
                    aiState.endTick = tick + 0;
                }
            } else if(aiState.state == AI_STATE_LOOKAROUND) {
                if(aiState.endTick <= tick) {
                    aiState.state = AI_STATE_MOVING;
                    aiState.targetPos.x = aiState.aroundPos.x + (randint(200)-100) / 50.0;
                    aiState.targetPos.y = aiState.aroundPos.y + (randint(200)-100) / 50.0;
                }
            }
        }
    }
}
