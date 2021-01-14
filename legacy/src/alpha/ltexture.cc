//
//  ltexture.cpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/24.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "ltexture.h"

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

