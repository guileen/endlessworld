#pragma once
#include "../factory.h"
#include "../renderer.h"

void updateHPBar(Manager &m, Renderer &r) {
    SDL_Color bgColor = {0x88, 0x88, 0x88, 0xff};
    SDL_Color fgColor = {0x00, 0xdd, 0x33, 0xff};
    int w = 60, h = 10;
    m.each<Health, Sprite>([&](Entity& e, Health& health, Sprite& sprite) {
        float Percent =  (float) health.hitPoint / health.maxHitPoint;
        Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
        int x = sprite.dstRect.x + sprite.dstRect.w / 2 - w / 2;
        int y = sprite.dstRect.y - 10;
        Rect bgrect = {x, y, w, h};
        r.renderRect(&bgrect, bgColor);

        int pw = (int)((float)w * Percent);
        SDL_Rect fgrect = {x, y, pw, h};
        r.renderRect(&fgrect, fgColor);
    });
}