#pragma once
#include <vector>
#include <stdlib.h>
#include "graphic_interfaces.h"

// 元素相对于父元素的锚点位置, 子元素将采用和父元素同样的定位点
// 比如：当align 为 ALIGN_LEFT 时，x 表示 元素左侧相对于父元素左侧的距离。
// 当 align 为 ALIGN_MIDDLE 时，x 表示 元素中轴相对于父元素中轴的距离。
// 当 align 为 ALIGN_BOTTOM 时，y 表示 元素底边相对于父元素底边的距离。
const uint8_t ALIGN_HORIZONTAL = 0x0f;
const uint8_t ALIGN_VERTICAL = 0xf0;
const uint8_t ALIGN_TOPLEFT = 0x00;
const uint8_t ALIGN_CENTER = 0x11;
const uint8_t ALIGN_LEFT = 0x00;
const uint8_t ALIGN_MIDDLE = 0x01;
const uint8_t ALIGN_RIGHT = 0x02;
const uint8_t ALIGN_TOP = 0x00;
const uint8_t ALIGN_VMIDDLE = 0x10;
const uint8_t ALIGN_BOTTOM = 0x20;

class Element {
protected:
    int screenX=0, screenY=0;
    void updateScreenPos() {
        int offX, offY;
        int pw = parent? parent->w : 0;
        int ph = parent? parent->h : 0;
        switch(align & ALIGN_HORIZONTAL) {
            case ALIGN_MIDDLE:
            offX = (pw - w)/2;
            printf("Align middle %d-%d / 2 =%d\n", pw, w, offX);
            break;
            case ALIGN_RIGHT:
            offX = pw - w;
            break;
            default:
            offX = 0;
        }
        switch(align & ALIGN_VERTICAL) {
            case ALIGN_VMIDDLE:
            offY = (ph - h)/2;
            break;
            case ALIGN_BOTTOM:
            offY = ph - h;
            break;
            default:
            offY = 0;
        }
        screenX = (parent ? parent->screenX + x : x) + offX;
        screenY = (parent ? parent->screenY + y : y) + offY;
    }
    virtual void draw(Renderer* r){};
public:
    uint8_t align; // 左 中 右 上 中 下, 相对定位 left
    // 左上角相对于父元素左上角定位。
    int x=0, y=0, w=0, h=0;
    Element* parent=NULL;
    bool visible = true;
    virtual void updateFrame(uint32_t tick) {};
    virtual void render(Renderer* r) {
        if(!visible) return;
        updateScreenPos();
        draw(r);
    }
};

class Sprite:public Element {
    Texture* texture;
    SDL_Rect clip;
    int frame;
public:
    ~Sprite() {}
    Sprite(){}
    void init(Texture* _texture, int _w, int _h) {
        texture = _texture;
        w = _w;
        h = _h;
        clip.x=0;
        clip.y=0;
        clip.w=_w;
        clip.h=_h;
    }
    void init(Texture* _texture, int x, int y, SDL_Rect* clip) {
        texture = _texture;
        this->x = x;
        this->y = y;
        this->w = clip->w;
        this->h = clip->h;
        this->clip = *clip;
    }
    void updateFrame(uint32_t tick) {};
    void draw(Renderer* renderer) {
        // TODO 获取正确坐标
        SDL_Rect dst = {screenX, screenY, w, h};
        renderer->renderTexture(texture, &clip, &dst);
    }
};

class ComposedElement:public Element {
    std::vector<Element*> children;
public:
    void addElement(Element* element) {
        element->parent = this;
        children.push_back(element);
    }
    void draw(Renderer* renderer) {
        for(auto& ele:children) {
            ele->render(renderer);
        }
    }
};

// ---------------
//       UI
// ---------------
// 一个极简的UI系统，主要解决如下几个问题
// 1. 基本绘图组件的抽象，矩形，圆形，边框颜色，粗细，填充色
// 2. 9宫格背景绘制
// 3. 垂直／水平 滚动面板，拖拽手势
// 4. 事件传递与点击检测
// 5. 文字显示，字体，中文，加粗，边框加粗，阴影，颜色。
// 6. 输入框
// 7. 窗口生命周期，（显示／更新－数据绑定／关闭）

namespace UI {

// 每个元素都采用相对定位，其父元素位置将决定其子元素的位置
class RectView: public Element {
    // shadow offset, color, blur
public:
    void draw(Renderer* r) {

    }
};

class Image: public RectView {

};

class Text: public RectView {
    const char* text;
    // text effects
};

class Panel: public RectView {
    std::vector<Element*> children;
    // vscroll | hscroll
    // vscrollbar | hscrollbar
    // scrollbar style
public:
    void addElement(Element* element) {
        element->parent = this;
        children.push_back(element);
    }
    void draw(Renderer* r) {
        RectView::draw(r);
        for(auto& ele:children) {
            ele->render(r);
        }
    }
};

}