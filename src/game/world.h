//
//  world.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/30.
//  Copyright © 2018年 林 桂. All rights reserved.
//
// 世界地图相关
// 1024*1024 个区域，每个区域 1024*1024个方格。
// 玩家在当前区域，则渲染当前区域，及相邻区域

#ifndef world_h
#define world_h

#include <assert.h>
#include <stdio.h>
#include "cutils.h"
#include "well512_random.h"

typedef uint8_t Uint8;

const int _rsize = 4;
const int REGION_WIDTH=_rsize;
const int REGION_HEIGHT=_rsize;
const int REGION_HALF_WIDTH = REGION_WIDTH/2;
const int REGION_HALF_HEIGHT = REGION_HEIGHT/2;
const int REGION_SWITCH_STEPS = REGION_WIDTH/2 + REGION_WIDTH/4;
const int REGION_DATA_EXTRA_LENGTH = 0;
const size_t REGION_DATA_SIZE = REGION_WIDTH * REGION_HEIGHT + REGION_DATA_EXTRA_LENGTH;

class World {
    // 需要加载左上，上，右上，左中，中，右中，下左，下中，下右，9个区域到内存中
    // 当从一个区域进入另一个区域1/4的深度(256)后（避免在边界移动，频繁发生切换，见下文），
    // 即将中心区域切换到另一个区域，其中6个区域信息仍然可用，不必重新加载
    // 另3个区域信息需要重新加载。
    // 为了避免重复申请内存，这9个区域的内存布局是不变的，仅做指针的替换操作。
    // 9MB memory.
    Uint8* page; // malloc 9*(1024*1024+100)
    Uint8* regions[9]; // TL,T,TR,ML,M,MR,BL,B,BR. regions[4] is middle, regions[0] is top left, regions[8] is bottom right.
    Uint8* currentRegion;
    int centerRegionX=0, centerRegionY=0; // regions[4] 中心点

public:
    World() {
        page = (Uint8*) malloc(9*REGION_DATA_SIZE);
        for(int i=0;i<9;i++) {
            regions[i] = page + i*REGION_DATA_SIZE;
        }
        currentRegion = regions[4];
    }
    ~World() {
        free(page);
    }
    
    void initRegions(int x, int y) {
        for(int i=0;i<9;i++) {
            regions[i] = page + i*REGION_DATA_SIZE;
        }
        currentRegion = regions[4];
        loadRegion(regions[0], x - REGION_WIDTH, y - REGION_HEIGHT);
        loadRegion(regions[1], x, y - REGION_HEIGHT);
        loadRegion(regions[2], x + REGION_WIDTH, y - REGION_HEIGHT);
        loadRegion(regions[3], x - REGION_WIDTH, y);
        loadRegion(regions[4], x, y);
        loadRegion(regions[5], x + REGION_WIDTH, y);
        loadRegion(regions[6], x - REGION_WIDTH, y + REGION_HEIGHT);
        loadRegion(regions[7], x, y + REGION_HEIGHT);
        loadRegion(regions[8], x + REGION_WIDTH, y + REGION_HEIGHT);
        currentRegion = regions[4];
        // int regionXIndex = (x + (x>0?REGION_HALF_WIDTH:-REGION_HALF_WIDTH)) / REGION_WIDTH;
        // int regionYIndex = (y + (y>0?REGION_HALF_HEIGHT:-REGION_HALF_HEIGHT)) / REGION_HEIGHT;
        // printf("xIndex %d yIndex %d\n", regionXIndex, regionYIndex);
        getRegionCenterPos(x, y, &centerRegionX, &centerRegionY);
    }

    // 移动到新位置后，检查并更新内存
    void updateCurrentRegion(int x, int y) {
        int regionX = x - centerRegionX;
        int regionY = y - centerRegionY;
        if(regionX>REGION_SWITCH_STEPS) {
            // switch with right
            Uint8 *t;
            t = regions[0];
            regions[0] = regions[1];
            regions[1] = regions[2];
            regions[2] = t;
            t = regions[3];
            regions[3] = regions[4];
            currentRegion = regions[4] = regions[5];
            regions[5] = t;
            t = regions[6];
            regions[6] = regions[7];
            regions[7] = regions[8];
            regions[8] = t;
            // this could be parrallel.
            loadRegion(regions[2], x + REGION_WIDTH, y - REGION_HEIGHT); // top right.
            loadRegion(regions[5], x + REGION_WIDTH, y);        // right.
            loadRegion(regions[8], x + REGION_WIDTH, y + REGION_HEIGHT); // bottom right.
            centerRegionX += REGION_WIDTH;
        } else if(regionX<-REGION_SWITCH_STEPS) {
            // switch with left
            Uint8 *t;
            t = regions[2];
            regions[2] = regions[1];
            regions[1] = regions[0];
            regions[0] = t;
            t = regions[5];
            regions[5] = regions[4];
            currentRegion = regions[4] = regions[3];
            regions[3] = t;
            t = regions[8];
            regions[8] = regions[7];
            regions[7] = regions[6];
            regions[6] = t;
            // this could be parrallel.
            loadRegion(regions[0], x - REGION_WIDTH, y - REGION_HEIGHT); // top left.
            loadRegion(regions[3], x - REGION_WIDTH, y);        // left.
            loadRegion(regions[6], x - REGION_WIDTH, y + REGION_HEIGHT); // bottom left.
            centerRegionX -= REGION_WIDTH;
        } else if (regionY>REGION_SWITCH_STEPS) {
            // switch with top
            Uint8 *t;
            t = regions[6];
            regions[6] = regions[3];
            regions[3] = regions[0];
            regions[0] = t;
            t = regions[7];
            regions[7] = regions[4];
            currentRegion = regions[4] = regions[1];
            regions[1] = t;
            t = regions[8];
            regions[8] = regions[5];
            regions[5] = regions[2];
            regions[2] = t;
            // this could be parrallel.
            loadRegion(regions[0], x - REGION_WIDTH, y - REGION_HEIGHT); // top left.
            loadRegion(regions[1], x, y - REGION_HEIGHT);        // top.
            loadRegion(regions[2], x + REGION_WIDTH, y - REGION_HEIGHT); // top right.
            centerRegionY -= REGION_HEIGHT;
        } else if (regionY<-REGION_SWITCH_STEPS) {
            // switch with down
            Uint8 *t;
            t = regions[0];
            regions[0] = regions[3];
            regions[3] = regions[6];
            regions[6] = t;
            t = regions[1];
            regions[1] = regions[4];
            currentRegion = regions[4] = regions[7];
            regions[7] = t;
            t = regions[2];
            regions[2] = regions[5];
            regions[5] = regions[8];
            regions[8] = t;
            // this could be parrallel.
            loadRegion(regions[6], x - REGION_WIDTH, y + REGION_HEIGHT); // bottom left.
            loadRegion(regions[7], x, y + REGION_HEIGHT);        // bottom.
            loadRegion(regions[8], x + REGION_WIDTH, y + REGION_HEIGHT); // bottom right.
            centerRegionY += REGION_HEIGHT;
        }
    }
    
    void loadRegion(Uint8* data, int x, int y) {
        uint32_t n, id = getRegionId(x, y);
        printf("loadRegion %d %d id %d\n", x, y, id);
        Well512 ws;
        well512_init(&ws, id);
        for(int x=0;x<REGION_WIDTH;x++) {
            for(int y=0;y<REGION_HEIGHT;y++) {
                n = well512_genU32(&ws);
                data[y*REGION_WIDTH+x] = n & 0xff;
            }
        }
    }

    // 将 left, top, w, h 围成的区域数据复制到 dst 中
    void copyRectBlock(int left, int top, int width, int height, Uint8* dst) {
        printf("copyRectBlock %d %d %d %d\n", left, top, width, height);
        assert(width<REGION_WIDTH);
        assert(height<REGION_HEIGHT);
        // 性能优化，不必每次都getRegionBlock, 对于大块连续区域，可以把一整个区域内的数据都先复制过来。
        // 获取左上起始区域，并获取区域右下位置。
        int srcBottom=centerRegionY-REGION_HALF_HEIGHT - 1; // center region top - 1
        int srcRight=centerRegionX-REGION_HALF_WIDTH - 1;
        int h=height, w=width;
        int index=0, topLeftIndex=0;
        // find the src_region and edge.
        if(top>srcBottom) {
            if(top<=srcBottom+REGION_HEIGHT) {
                index += 3; // regions[3]
                srcBottom += REGION_HEIGHT;
            }else{ // top <= srcBottom+region_height*2 . always true.
                index += 6; // regions[6]
                srcBottom += 2*REGION_HEIGHT;
            }
        // } else if(t<centerRegionY-REGION_HALF_HEIGHT-REGION_HEIGHT) {
        //     return NULL;
        }
        if(left>srcRight) {
            if(left<=srcRight+REGION_WIDTH) {
                index += 1; // regions[1 4 7]
                srcRight += REGION_WIDTH;
            }else{ // left <= srcRight+region_width*2. always true.
                index += 2; // regions[2 5 8]
                srcRight += 2*REGION_WIDTH;
            }
        // }else if(l<centerRegionX-REGION_HALF_WIDTH-REGION_WIDTH) {
        //     return NULL;
        }
        topLeftIndex = index;
        int leftW = width, leftHeight = height;
        // 最多需要复制4块区域, 待复制区域与当前psrc交集的宽高
        int t = (top+REGION_HALF_HEIGHT) % REGION_HEIGHT;
        int l = (left+REGION_HALF_WIDTH) % REGION_WIDTH;
        int dl=0, dt=0;
        printf("top %d t %d h %d\n", top, t, h);
        h = MIN(srcBottom - top + 1, h);
        w = MIN(srcRight - left + 1, w);
        do {
            do {
                // 复制交集区域
                for(int yi=0; yi<h; yi++) {
                    for(int xi=0; xi<w; xi++) {
                        int di = (dt+yi)*width+xi+dl;
                        int si = (t+yi)*REGION_WIDTH+l+xi;
                        printf("di %d si %d index %d xi %d yi %d l %d t %d dl %d dt %d\n", di, si, index, xi, yi, l, t, dl, dt);
                        printf("value %02x\n", regions[index][si]);
                        dst[di] = regions[index][(t+yi)*REGION_WIDTH+l+xi];
                    }
                }
                // 向右一格区域 +1
                index += 1;
                l = 0;
                dl+=w;
                leftW -= w;
                w = leftW;
            } while(w>0);
            // 重置横向参数
            dl=0;
            dt+=h;
            leftW = width;
            w = MIN(srcRight - left + 1, width);
            // 更新下一个坐标
            index = topLeftIndex+3; // 垂直向下区域 +3
            t = 0;
            l = (left + REGION_HALF_WIDTH) % REGION_WIDTH;
            leftHeight -= h;
            h = leftHeight;
        } while(h>0);
    }

    Uint8* getRegionBlock(int x, int y) {
        Uint8** pregion = regions;
        int l = centerRegionX-REGION_HALF_WIDTH;
        int t = centerRegionY-REGION_HALF_HEIGHT;
        if(y>=t) {
            if(y<t+REGION_HEIGHT) {
                pregion += 3;
            }else{
                pregion += 6;
            }
        } else if(y<t-REGION_HEIGHT) {
            return NULL;
        }
        if(x>=l) {
            if(x<l+REGION_WIDTH) {
                pregion += 1;
            }else{
                pregion += 2;
            }
        }else if(x<l-REGION_WIDTH) {
            return NULL;
        }
        return *pregion;
    }

    static uint32_t getRegionId(int x, int y) {
        // [-1536, -512) [-512,512) index 0, [512,1024+512) index 1.
        // +512 = [-1024, 0) [0, 1024) [1024, 2048)
        int regionXIndex, regionYIndex;
        getRegionIndex(x, y, &regionXIndex, &regionYIndex);
        uint32_t regionId = (abs(regionXIndex) << 17) | (abs(regionYIndex)<<1) ;
        if(regionXIndex<0) {
            regionId |= 0x00010000;
        }
        if(regionYIndex<0) {
            regionId |= 1;
        }
        return regionId;
    }

    static void getRegionIndex(int x, int y, int *xi, int *yi) {
        int fixX = x+REGION_HALF_WIDTH;
        int fixY = y + REGION_HALF_HEIGHT;
        if(fixX<0) {
            fixX -= REGION_WIDTH-1;
        }
        if(fixY<0) {
            fixY -= REGION_HEIGHT-1;
        }
        *xi = fixX/REGION_WIDTH;
        *yi = fixY/REGION_HEIGHT;
    }

    static void getRegionCenterPos(int x, int y, int *centerX, int *centerY) {
        int regionXIndex, regionYIndex;
        getRegionIndex(x, y, &regionXIndex, &regionYIndex);
        *centerX = regionXIndex * REGION_WIDTH;
        *centerY = regionYIndex * REGION_HEIGHT;
    }
    
    void debugPrint() {
        for(int y=0;y<REGION_HEIGHT*3;y++) {
            for(int x=0;x<REGION_WIDTH*3;x++) {
                int rindex = 3*(y/REGION_HEIGHT) + x/REGION_WIDTH;
                // printf("%02x ", rindex);
                Uint8* r = regions[rindex];
                printf("%02x ", r[(y%REGION_HEIGHT)*REGION_WIDTH+x%REGION_WIDTH]);
                if((x+1)%REGION_WIDTH==0 && x/REGION_WIDTH<3){
                    printf(" | ");
                }
            }
            printf("\n");
            if((y+1)%REGION_HEIGHT==0 && y/REGION_HEIGHT<3){
                for(int i=0;i<REGION_WIDTH*9+6;i++) printf("-");
                printf("\n");
            }
        }
    }
};

#endif /* world_h */
