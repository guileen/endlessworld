//
//  gameobject.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/24.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef gameobject_h
#define gameobject_h
#include "engine.h"

typedef struct {
    GRect rect;
    int anchorX, anchorY;
    GSurface* texture;
} Sprite;



void drawSprit(Sprite*);

#endif /* gameobject_h */
