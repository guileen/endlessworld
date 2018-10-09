#include "hud.h"

/* 
   Render a Horizontal Percentage Bar 
   Drains left to right normally, if width is negative it will drain right to left. 
   Percent is clamped 0.0f - 1.0f 
*/ 
void RenderHPBar(SDL_Renderer* renderer, int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) { 
   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent; 
   SDL_Color old; 
   SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a); 
   SDL_Rect bgrect = { x, y, w, h }; 
   SDL_SetRenderDrawColor(renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a); 
   SDL_RenderFillRect(renderer, &bgrect); 
   SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a); 
   int pw = (int)((float)w * Percent); 
   int px = x;// + (w - pw); 
   SDL_Rect fgrect = { px, y, pw, h }; 
   SDL_RenderFillRect(renderer, &fgrect); 
   SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a); 
} 

/* 
   Render a Vertical Percentage Bar 
   Drains top to bottom normally, if height is negative it will drain bottom to top 
   Percent is clamped 0.0f - 1.0f 
*/ 
void RenderVPBar(SDL_Renderer* renderer, int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) { 
   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent; 
   SDL_Color old; 
   SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a); 
   SDL_Rect bgrect = { x, y, w, h }; 
   SDL_SetRenderDrawColor(renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a); 
   SDL_RenderFillRect(renderer, &bgrect); 
   SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a); 
   int ph = (int)((float)h * Percent); 
   int py = y + (h - ph); 
   SDL_Rect fgrect = { x, py, w, ph }; 
   SDL_RenderFillRect(renderer, &fgrect); 
   SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a); 
}

/* 

   color - Returns an SDL_Color with the appropriate values 

*/ 
SDL_Color new_sdl_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { 
   SDL_Color col = {r,g,b,a}; 
   return col; 
} 