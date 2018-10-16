#ifndef hud_h
#define hud_h

#include "engine.h"

/* 

   color - Returns an SDL_Color with the appropriate values 

*/ 
inline SDL_Color new_sdl_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { 
   SDL_Color col = {r,g,b,a}; 
   return col; 
} 

class HealthBar : public UI::Panel {
  public:
    int *current;
    int *max;
    SDL_Color fgColor;
    SDL_Color bgColor;
    HealthBar() {
        bgColor = new_sdl_color(0x88, 0x88, 0x88, 0xff);
        fgColor = new_sdl_color(0x00, 0xdd, 0x33, 0xff);
    };
    void draw(Renderer* renderer) {
        float Percent =  (float) (*current) / (*max);
        Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
        Rect bgrect = {screenX, screenY, w, h};
        renderer->renderRect(&bgrect, bgColor);

        int pw = (int)((float)w * Percent);
        SDL_Rect fgrect = {screenX, screenY, pw, h};
        renderer->renderRect(&fgrect, fgColor);
    }
};

#endif