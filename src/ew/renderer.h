#pragma once
#include "config.h"

class Renderer {
public:
    virtual void clear(){};
    virtual void present(){};
    virtual void renderTexture(Texture* texture, const Rect* srcrect, const Rect* dstrect)=0;
    virtual void renderText(const char*)=0;
    virtual void renderRect(Rect* rect, Color color)=0;
};
