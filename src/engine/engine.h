//
//  engine.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/27.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef engine_h
#define engine_h

#include "renderer.h"
#include <vector>

class GameScean;

class Element {
public:
    int x=0, y=0, w=0, h=0, anchorX=0, anchorY=0;
    Element* parent;
    bool visible = true;
    virtual void updateFrame() {};
    virtual void render(Renderer*)=0;
};

class Sprite:public Element {
    Texture* texture;
    SDL_Rect clip;
    int frame;
public:
    Sprite(Texture* _texture, int _w, int _h) {
        texture = _texture;
        w = _w;
        h = _h;
        clip.x=0;
        clip.y=0;
        clip.w=_w;
        clip.h=_h;
    }
    ~Sprite() {}
    void updateFrame() {};
    void render(Renderer* renderer) {
        // TODO 获取正确坐标
        SDL_Rect dst = {x, y, w, h};
        renderer->renderTexture(texture, &clip, &dst);
    }
};

class Text: public Element{
    const char* text;
    // text effects
};

class ComposedElement:public Element {
    std::vector<Element*> children;
public:
    void addElement(Element* element) {
        children.push_back(element);
    }
    void render(Renderer* renderer) {
        if(visible)
        for(auto& ele:children) {
            ele->render(renderer);
        }
    }
};

class GameScean {
private:
    Renderer* renderer;
    ComposedElement root;
public:
    GameScean(Renderer* _renderer) {
        renderer = _renderer;
    }
    virtual ~GameScean() {};
    virtual void handleInput()=0;
    virtual void updateFrame()=0;
    void addElement(Element* element) {
        root.addElement(element);
    }
    void render() {
        renderer->clear();
        root.render(renderer);
        renderer->present();
    };
};

// work like a singleton.
namespace GameLoop {
    void run(GameScean*);
    float getFPS();
    void quit();
}

#endif /* engine_h */
