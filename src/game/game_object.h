//
//  game_object.h
//  endlessworld
//
//  Created by 林 桂 on 18/10/4.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef game_object_h
#define game_object_h
#include "engine.h"
#include "hud.h"
#include "game_commons.h"

class GameScean;
class GameObject: public Sprite {
protected:
    GameScean* scean;
    double moveSpeed;
    double maxMoveSpeed;
    double angle=0;
public:
    Position pos;
    GameObject(){}

    GameObject(GameScean* scean, Texture* tx, double x, double y, int w, int h) {
        init(scean, tx, x, y, w, h);
    }

    void init(GameScean* scean, Texture* tx, double x, double y, int w, int h) {
        this->scean = scean;
        pos.x = x;
        pos.y = y;
        SDL_Rect r = {0, 0, w, h};
        Sprite::init(tx, 0, 0, &r);
    }

    void updateFrame(uint32_t tick); 
    void render(Renderer*);
};

enum GOState {
    GO_MOVING,
    GO_FIGHTING,
};

enum EAIState {
    AI_STATE_MOVING=0,
    AI_STATE_LOOKAROUND=1,
    AI_STATE_CHASING,
    AI_STATE_CHASING_BACK,
    AI_STATE_GOSSIP,
};

enum EAIType {
    AI_TYPE_NONE=0,
    AI_TYPE_WANDER,
};

typedef struct {
    EAIType type;
    EAIState state;
    Position aroundPos;
    Position targetPos;
    uint32_t endTick;
} AIState;

class Character: public GameObject {
protected:
    GOState state;
    AIState aiState;
    int healthPoint;
    int maxHealthPoint;
    int powerPoint;
public:
    HealthBar healthBar;
    Character(GameScean* scean, int id, double x, double y) {
        char buff[255];
        sprintf(buff, "res/character/%d.png\0", id);
        Texture *tx = loadTexture(buff);
        if(tx == NULL) {
            printf("load texture fail %s", SDL_GetError());
        }
        init(scean, tx, x, y, 32, 32);
        if(id == 0) {
            aiState.type = AI_TYPE_NONE;
        } else {
            aiState.type = AI_TYPE_WANDER;
            aiState.state = AI_STATE_LOOKAROUND;
            aiState.aroundPos = pos;
            aiState.endTick = 0;
        }
        healthPoint = 50;
        maxHealthPoint = 100;
        healthBar.align = ALIGN_TOP | ALIGN_MIDDLE;
        healthBar.y = -10;
        healthBar.w = w;
        healthBar.h = 10;
        healthBar.parent = this;
        healthBar.current = &healthPoint;
        healthBar.max = &maxHealthPoint;
    }
    void updateFrame(uint32_t tick); 
    void draw(Renderer* renderer) {
        GameObject::draw(renderer);
        healthBar.render(renderer);
    }
};

class NPC: public Character {

};

class Player: public Character {
public:
    Player(GameScean* scean, double x, double y) : Character(scean, 0, x, y) {
    }
};
#endif /* game_object_h */
