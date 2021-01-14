#pragma once

// types
#include "sdl2utils.h"
typedef SDL_Texture Texture;
typedef SDL_Rect Rect;
typedef SDL_Color Color;

class Renderer {
public:
    virtual void clear(){};
    virtual void present(){};
    virtual void renderTexture(Texture* texture, const Rect* srcrect, const Rect* dstrect)=0;
    virtual void renderText(const char*)=0;
    virtual void renderRect(Rect* rect, Color color)=0;
};

class SceanManager;

class Scean {
public:
    virtual void load(SceanManager*)=0;
    virtual void unload()=0;
    virtual void handleInput()=0;
    virtual void updateFrame(uint32_t tick)=0;
    virtual void render(Renderer*)=0;
};

class SceanManager {
protected:
    Scean* scean = NULL;
public:
    virtual int getScreenWidth()=0;
    virtual int getScreenHeight()=0;
    void changeScean(Scean* s) {
        if(scean != NULL) scean->unload();
        scean = s;
        if(s!=NULL) s->load(this);
    }
    virtual void quit()=0;
};
