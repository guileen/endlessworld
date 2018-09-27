//
//  tiledmap.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/23.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "tiledmap.h"

const int WORLD_WIDTH=4;
const int WORLD_HEIGHT=4;
const int TILE_WIDTH=60;
const int TILE_HEIGHT=60;


char world[WORLD_WIDTH][WORLD_HEIGHT] = {0};

bool generated = false;

SDL_Texture* testTexture;
void generateMap() {
    for(int x=0; x<WORLD_WIDTH; x++) {
        for(int y=0; y<WORLD_HEIGHT; y++) {
            world[x][y] = randint(10)+1;
        }
    }
    generated = true;
    
    testTexture = loadTexture("res/images/hello_world.png");
}

void renderWorld(int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset_x, int offset_y) {
    // TODO: remove 随机生成地图
    if(!generated) generateMap();

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    
    //Top left corner viewport
    SDL_Rect topLeftViewport;
    topLeftViewport.x = 0;
    topLeftViewport.y = 0;
    topLeftViewport.w = SCREEN_WIDTH;
    topLeftViewport.h = SCREEN_HEIGHT;
    SDL_RenderSetViewport( gRenderer, &topLeftViewport );
    /*
    //Render red filled quad
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( gRenderer, &fillRect );
    
    //Render green outlined quad
    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect( gRenderer, &outlineRect );

    SDL_SetRenderDrawColor( gRenderer, 0xE0, 0xF0, 0x19, 0xAF );
    SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
    {
        SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
    }
    //Draw blue horizontal line
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
    SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
    {
        SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
    }
     */
    
    // 获取可视区域
    // 绘制可视区域
    int centerx = SCREEN_WIDTH/2;
    int centery = SCREEN_HEIGHT/2;
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
            Blit(tileTable[world[x][y]], &srcrect, &destrect);
        }
    }
    

    //Top right viewport
    SDL_Rect topRightViewport;
    topRightViewport.x = SCREEN_WIDTH * 5 / 6;
    topRightViewport.y = 0;
    topRightViewport.w = SCREEN_WIDTH / 6;
    topRightViewport.h = SCREEN_HEIGHT / 6;
    SDL_RenderSetViewport( gRenderer, &topRightViewport );
    SDL_SetTextureColorMod( testTexture, 125, 125, 255 );

    //Render texture to screen
    SDL_RenderCopy( gRenderer, testTexture, NULL, NULL );
    /*
    //Bottom viewport
    SDL_Rect bottomViewport;
    bottomViewport.x = 0;
    bottomViewport.y = SCREEN_HEIGHT / 2;
    bottomViewport.w = SCREEN_WIDTH;
    bottomViewport.h = SCREEN_HEIGHT / 2;
    SDL_RenderSetViewport( gRenderer, &bottomViewport );
    
    //Render texture to screen
    SDL_RenderCopy( gRenderer, testTexture, NULL, NULL );
    */
    
    //Update screen
    UpdateScreen();
}
