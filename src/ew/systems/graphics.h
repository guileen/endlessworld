#include "../components/components.h"
#include "../map_render.h"
#include "../components/graphic_components.h"

class GraphicSystem
{
    Manager &manager;
    Renderer &renderer;
    MapRenderer map;
    Position centerPosition;
    int screenWidth;
    int screenHeight;
    int hUnitPixels = 120;
    int vUnitPixels = 120;

  public:
    GraphicSystem(Manager &mManager, Renderer &mRenderer, int mScreenWidth, int mScreenHeight)
        : manager(mManager), renderer(mRenderer), centerPosition(0, 0), screenWidth(mScreenWidth), screenHeight(mScreenHeight)
    {
        map.initResolution(screenWidth, screenHeight, 60, 60, hUnitPixels, vUnitPixels);
        map.initCenterPosition(0, 0);
    };

    inline void toScreenPoint(Position pos, int &screenX, int &screenY)
    {
        screenX = (pos.x - centerPosition.x) * hUnitPixels + screenWidth / 2;
        screenY = (pos.y - centerPosition.y) * vUnitPixels + screenHeight / 2;
        printf("screenXY %d %d pos %.3f %.3f screenCenter %.3f %.3f\n",
               screenX, screenY, pos.x, pos.y, centerPosition.x, centerPosition.y);
    }

    void update() {
        auto& pos = manager.getPlayer().getComponent<Position>();
        map.updateCenterPosition(pos.x, pos.y);
        centerPosition = pos;
        // render the map
        map.render(&renderer);

        // render entities
        manager.each<Sprite, Position>([&](Entity &e, Sprite &s, Position &p) {
            int &x = s.dstRect.x;
            int &y = s.dstRect.y;
            toScreenPoint(p, x, y);
            printf("e.id %d %.2f %.2f cx %.2f cy %.2f x %d y %d\n", e.getId(), p.x, p.y, centerPosition.x, centerPosition.y, x, y);
            x -= s.dstRect.w/2;
            y -= s.dstRect.h/2;
            // out of screen
            if (x > screenWidth || y > screenHeight || x + s.dstRect.w < 0 || y + s.dstRect.h < 0) return;
            // TODO: if(invisible to player) return;
            renderer.renderTexture(s.texture, &s.srcRect, &s.dstRect);
        });

        // render in game hud.
        manager.each<Health, Position>([](Entity& e, Health& h, Position &p) {

        });
    }
};
