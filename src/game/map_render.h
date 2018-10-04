#ifndef map_render_h
#define map_render_h
#include "world_map.h"
#include "engine.h"
#include "game_commons.h"

const int TILES_EACH_ROW=20;
class MapRenderer: public Element {
    // tiles size
    int tileWidth, tileHeight;
    int screenTileWidth, screenTileHeight;
    int screenWidth, screenHeight;
    bool loaded = false;
    Texture *TILES[255];
    // WorldMap about.
    WorldMap map;
    double centerX;
    double centerY;
    SDL_Rect dataRect;
    Uint8 data[WorldMap::REGION_DATA_SIZE];
public:

  void loadTiles() {
      if (loaded) return;
      char buff[255];
      for (int i = 0; i < 255; i++) {
          sprintf(buff, "res/tiles/groud/%d.png\0", i);
          TILES[i] = loadTexture(buff);
      }
      loaded = true;
    }

    MapRenderer() {
        loadTiles();
    };

    void initResolution(int screenWidth, int screenHeight) {
        initResolution(screenWidth, screenHeight, TILES_EACH_ROW, 60, 60);
    }

    void initResolution(int screenWidth, int screenHeight, int tilesEachRow, int tileWidth, int tileHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        this->screenTileWidth = screenWidth / tilesEachRow;
        // 等比缩放
        this->screenTileHeight = screenTileWidth*tileHeight/tileWidth;
        dataRect.w = ceil((float)screenWidth/ screenTileWidth) + 1;
        dataRect.h = ceil((float)screenHeight/screenTileHeight) + 1;
    }

    void initCenterPosition(double x, double y) {
        centerX = x;
        centerY = y;
        dataRect.x = floor(x - screenWidth/2.0/screenTileWidth);
        dataRect.y = floor(y - screenHeight/2.0/screenTileHeight);
        map.initRegions(x, y);
        map.copyRectBlock(dataRect.x, dataRect.y, dataRect.w, dataRect.h, data);
    }

    void updateCenterPosition(double x, double y) {
        centerX = x;
        centerY = y;
        dataRect.x = floor(x - screenWidth/2.0/screenTileWidth);
        dataRect.y = floor(y - screenHeight/2.0/screenTileHeight);
        map.updateCurrentRegion(x, y);
        map.copyRectBlock(dataRect.x, dataRect.y, dataRect.w, dataRect.h, data);
    }

    void render(Renderer* renderer) {
        double left = centerX - screenWidth/2.0/screenTileWidth;
        double top = centerY - screenHeight/2.0/screenTileHeight;
        int screenLeft = (floor(left) - left) * screenTileWidth;
        int screenTop = (floor(top) - top) * screenTileHeight;
        printf("left %.2f top %.2f screenLeft %d screenTop %d\n", left, top ,screenLeft, screenTop);

        SDL_Rect srcRect = {0, 0, tileWidth, tileHeight};
        SDL_Rect dstRect = {screenLeft, screenTop, screenTileWidth, screenTileHeight};
        for(int x=0;x<dataRect.w;x++) {
            for(int y=0;y<dataRect.h;y++) {
                // renderTile(renderer, x, y, data[y*rect.w+x]);
                dstRect.x = screenLeft + x * screenTileWidth;
                dstRect.y = screenTop + y * screenTileHeight;
                renderer->renderTexture(TILES[data[y*dataRect.w + x]], &srcRect, &dstRect);
            }
        }
    }

    void updateFrame() {

    }
};
#endif
