#pragma once
#include "../../ecs/ecs.h"
#include "../config.h"

using namespace ecs;

struct Sprite : Component {
    Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
};
