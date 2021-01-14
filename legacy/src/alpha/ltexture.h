//
//  ltexture.hpp
//  endlessworld
//
//  Created by 林 桂 on 18/9/24.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef ltexture_h
#define ltexture_h

#include <stdio.h>
#include "engine.h"

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile(const char* path );
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif /* ltexture_h */
