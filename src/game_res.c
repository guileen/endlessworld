//
//  game_res.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "game_res.h"

const int MAX_RESOURCES=1000;

GSurface* gLoadedResources[MAX_RESOURCES];
SDL_Texture* tileTable[32];
