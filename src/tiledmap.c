//
//  tiledmap.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/23.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "tiledmap.h"

#include "engine.h"
#include "game_res.h"
#include "cutils.h"

const int WORLD_WIDTH=4;
const int WORLD_HEIGHT=4;
const int TILE_WIDTH=60;
const int TILE_HEIGHT=60;

char world[WORLD_WIDTH][WORLD_HEIGHT] = {0};

bool generated = false;

void generateMap() {
    for(int x=0; x<WORLD_WIDTH; x++) {
        for(int y=0; y<WORLD_HEIGHT; y++) {
            world[x][y] = random(10)+1;
        }
    }
    generated = true;
}

void renderWorld(int screen_width, int screen_height, int offset_x, int offset_y) {
    // TODO: remove 随机生成地图
    if(!generated) generateMap();
    
    // 获取可视区域
    // 绘制可视区域
    int centerx = screen_width/2;
    int centery = screen_height/2;
    int tileTotalWidth = WORLD_WIDTH * TILE_WIDTH;
    int tileTotalHeight = WORLD_HEIGHT * TILE_HEIGHT;
    int world_left = centerx - tileTotalWidth / 2;
    int world_top = centery - tileTotalHeight / 2;
    
    GRect srcrect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    GRect destrect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    for(int x=0;x<4;x++) {
        for(int y=0;y<4;y++) {
            // 绘制 x,y 位置
            destrect.x = offset_x + world_left + x * TILE_WIDTH;
            destrect.y = offset_y + world_top + y * TILE_HEIGHT;
            Blit(tileTable[world[x][y]], &srcrect,
                         gScreen, &destrect);
        }
    }
}
