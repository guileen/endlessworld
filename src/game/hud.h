#ifndef hud_h
#define hud_h

#include "engine.h"

/* 
   Render a Horizontal Percentage Bar 
   Drains left to right normally, if width is negative it will drain right to left. 
   Percent is clamped 0.0f - 1.0f 
*/ 
void RenderHPBar(SDL_Renderer* renderer, int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);

/* 
   Render a Vertical Percentage Bar 
   Drains top to bottom normally, if height is negative it will drain bottom to top 
   Percent is clamped 0.0f - 1.0f 
*/ 
void RenderVPBar(SDL_Renderer* renderer, int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);

/* 

   color - Returns an SDL_Color with the appropriate values 

*/ 
SDL_Color new_sdl_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

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
        RenderHPBar(renderer->_getSDLRenderer(), screenX, screenY, w, h, (float)(*current)/(*max), fgColor, bgColor);
    }
};

#endif