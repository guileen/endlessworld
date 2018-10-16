#ifndef game_scean_h
#define game_scean_h
#include "game_object.h"
#include "map_render.h"
#include <vector>

class GameScean: public Scean {
    SceanManager* sceanManager;
    std::vector<Character*> mobs;
    MapRenderer map;
    Position screenCenter;
    int screenWidth;
    int screenHeight;
    int hUnitPixels; // 水平1.0对应的像素
    int vUnitPixels; // 垂直1.0对应的像素
public:
    Player* player;
    void load(SceanManager* manager) {
        init(manager->getScreenWidth(), manager->getScreenHeight());
        sceanManager = manager;
    }
    void unload() {
    }
    void positionToScreen(Position pos, int* screenX, int* screenY) {
        *screenX = (pos.x - screenCenter.x) * hUnitPixels + screenWidth/2;
        *screenY = (pos.y - screenCenter.y) * vUnitPixels + screenHeight/2;
        printf("screenXY %d %d pos %.3f %.3f screenCenter %.3f %.3f\n",
            *screenX, *screenY, pos.x, pos.y, screenCenter.x, screenCenter.y);
    }
    void init(int w, int h);
    void addMob(int id, double x, double y) {
        mobs.push_back(new Character(this, id, x, y));
    }
    void updateFrame(uint32_t tick);
    void handleInput();
    void render(Renderer* renderer);
};

#endif
