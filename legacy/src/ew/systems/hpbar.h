#pragma once
#include "../factory.h"
#include "../renderer.h"

void updateHPBar(Manager &m, Renderer &r) {
    SDL_Color bgColor = {0x88, 0x88, 0x88, 0xff};
    SDL_Color fgColor = {0x00, 0xdd, 0x33, 0xff};
    SDL_Color attackBgColor = {0x33, 0x33, 0x33, 0x88};
    SDL_Color attackFgColor = {0xcc, 0xcc, 0xcc, 0xff};
    SDL_Color attackAfterFgColor = {0x33, 0xcc, 0x33, 0xff};
    int w = 60, h = 10;
    m.each<Health, Sprite>([&](Entity& e, Health& health, Sprite& sprite) {
        // render HP
        float Percent =  (float) health.hitPoint / health.maxHitPoint;
        Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
        int x = sprite.dstRect.x + sprite.dstRect.w / 2 - w / 2;
        int y = sprite.dstRect.y - 10;
        Rect rect = {x, y, w, h};
        r.renderProgressBar(Percent, rect, bgColor, fgColor);

        // render attack cooldown
        if (e.hasComponent<MeeleAttack>()) {
            MeeleAttack& ma = e.getComponent<MeeleAttack>();
            rect.y += 10;
            if(ma.frame < ma.hitFrame) {
                r.renderProgressBar((float) ma.frame/ma.frames, rect, attackBgColor, attackFgColor);
            } else {
                r.renderProgressBar((float) ma.frame/ma.frames, rect, attackBgColor, attackAfterFgColor);
            }
        }
    });
}
