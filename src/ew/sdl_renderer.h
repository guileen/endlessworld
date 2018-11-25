#include "renderer.h"

class SDLRenderer: public Renderer {
    SDL_Renderer* renderer;
public:
    SDLRenderer(SDL_Renderer* mRenderer): renderer(mRenderer) {};
    // methods inherite from Renderer
    void clear() {
        SDL_RenderClear(renderer);
    }
    void present() {
        SDL_RenderPresent(renderer);
    }
    void renderTexture(Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
        SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    }
    void renderRect(Rect* rect, Color c) {
        // no need to preserve color.
#ifdef __EMSCRIPTEN__
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
#else
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
#endif
        SDL_RenderFillRect(renderer, rect);
    }
    void renderText(const char*) {}
};