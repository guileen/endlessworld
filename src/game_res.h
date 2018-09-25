//
//  game_res.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef game_res_h
#define game_res_h
#include "engine.h"

extern const int MAX_RESOURCES;

extern GSurface* gLoadedResources[];
extern SDL_Texture* tileTable[];

void loadResource();

inline GSurface* getSurface(int index) {
    return gLoadedResources[index];
}

// get resource from cache by index, if not exists load via path.
// if index < 0, no cache.
static inline GSurface* loadSurface(int index, const char* path) {
    return (gLoadedResources[index]) ? gLoadedResources[index] :
        (gLoadedResources[index] = loadImage(path));
}

static inline SDL_Texture* loadTileSurface(int tileId) {
    char buff[255];
    sprintf(buff, "res/tiles/groud/%d.png", tileId);
    SDL_Texture** tile = tileTable + tileId; // same as tileTable[tileId]
    return *tile ? *tile : (*tile = loadTexture(buff));
}

#endif /* game_res_h */
