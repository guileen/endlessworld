#pragma once
#include "config.h"

class Renderer {
public:
    virtual void clear(){};
    virtual void present(){};
    virtual void renderTexture(Texture* texture, const Rect* srcrect, const Rect* dstrect)=0;
    virtual void renderText(const char*)=0;
    virtual void renderRect(Rect* rect, Color color)=0;
    void renderProgressBar(float Percent, Rect rect, Color& bgColor, Color& fgColor) {
        Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
        renderRect(&rect, bgColor);
        rect.w = (int)((float)rect.w * Percent);
        renderRect(&rect, fgColor);
    }
};
