//
//  engine.c
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#include "sdl2utils.h"

SDL_Window* gWindow;
SDL_Surface* gScreen;
TTF_Font *gFont = NULL;
SDL_Renderer* gRenderer;
SDL_GLContext* glContext;
// GameController 1 handler, just for demo
SDL_Joystick* gGameController = NULL;
SDL_Haptic* gControllerHaptic = NULL;

int appInit(const char* title, int width, int height, bool fullscreen) {
    /* GUI */
//    struct nk_context *ctx;
//    SDL_GLContext glContext;
    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

    //Initialization flag
    int flag=SDL_Init( SDL_INIT_EVERYTHING ); /*// - do NOT init SDL on GL ES 2*/
    //Initialize SDL
    if( flag < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Create window
    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 2;
    }
    
    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 3;
    }
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    // glContext = SDL_GL_CreateContext(gWindow);
    
    /* OpenGL setup */
    // glViewport(0, 0, width, height);
    
    // ctx = nk_sdl_init(win);
    
    /*
    //Get window surface
    gScreen = SDL_GetWindowSurface( gWindow );
    if (gScreen == NULL) {
        printf( "WindowSurface could not be get! SDL Error: %s\n", SDL_GetError() );
        return 5;
    }
     */
    //Check for joysticks
    if( SDL_NumJoysticks() >= 1 ) {
        //Load joystick
        gGameController = SDL_JoystickOpen( 0 );
        if( gGameController == NULL ) {
            printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
        } else {
            //Get controller haptic device
            gControllerHaptic = SDL_HapticOpenFromJoystick( gGameController );
            if( gControllerHaptic == NULL ) {
                printf( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
            } else {
                //Get initialize rumble
                if( SDL_HapticRumbleInit( gControllerHaptic ) < 0 ) {
                    printf( "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() );
                }
            }
        }

    }
    // initialize sub-system.
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 10;
    }
    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return 20;
    }
    //Open the font
    gFont = TTF_OpenFont( FONT_DEFAULT, 32 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    return 0;
}

int appQuit() {
    printf("TODO: FreeSurface(all loaded resources)");
    if(gGameController) {
        SDL_JoystickClose( gGameController );
        gGameController = NULL;
        if(gControllerHaptic) {
            SDL_HapticClose( gControllerHaptic );
            gControllerHaptic = NULL;
        }
    }
    
    SDL_DestroyRenderer( gRenderer );
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

GSurface* loadImage(const char* path) {
    const char* ext = get_filename_ext(path);
    SDL_Surface* loadedSurface = NULL;
    if(streql(ext, "bmp")) {
        loadedSurface = SDL_LoadBMP(path);
        if( loadedSurface == NULL ) {
            printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        }
    } else if (streql(ext, "png")) {
        loadedSurface = IMG_Load(path);
        if( loadedSurface == NULL ) {
            printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        }
    } else {
        printf("loadImage: %s,  %s not support yet!\n", path, ext);
    }
    return loadedSurface;
    /*
    //Convert surface to screen format
    SDL_Surface* optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreen->format, 0);
    if( optimizedSurface == NULL )
    {
        printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        return loadedSurface;
    }
    
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    return optimizedSurface;
    */
}

SDL_Texture* loadTexture(const char* path) {
    SDL_Surface* loadedSurface = loadImage(path);
    //Color key image
//    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    //Create texture from surface pixels
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
    }
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    return newTexture;
}

SDL_Texture* textureFromText(const char* textureText, SDL_Color textColor, TTF_Font *font, int* w, int* h) {
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font ? font : gFont, textureText, textColor );
    if( textSurface == NULL ) {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        return NULL;
    }

    //Create texture from surface pixels
    SDL_Texture* texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
    if( texture == NULL ) {
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }

    //Get image dimensions
    if(w && h) {
        *w = textSurface->w;
        *h = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
    
    //Return success
    return texture;
}

// const int JOYSTICK_DEAD_ZONE = 8000;
// SDL converts its position into a number between -32768 to 32767.
void UpdateJoyStickStateByEvent(SDL_Event* e, int* xDir, int* yDir, int JOYSTICK_DEAD_ZONE) {
    if(e->type != SDL_JOYAXISMOTION) return;
    //Motion on controller 0
    if( e->jaxis.which == 0 ) {
        if( e->jaxis.axis == 0 ) {
            //X axis motion
            if( e->jaxis.value < - JOYSTICK_DEAD_ZONE ) {
                //Left of dead zone
                *xDir = -1;
            } else if( e->jaxis.value > JOYSTICK_DEAD_ZONE ) {
                //Right of dead zone
                *xDir =  1;
            }
            else {
                *xDir = 0;
            }
        } else if( e->jaxis.axis == 1 ) {
            //Y axis motion
            if( e->jaxis.value < -JOYSTICK_DEAD_ZONE ) {
                //Below of dead zone
                *yDir = -1;
            } else if( e->jaxis.value > JOYSTICK_DEAD_ZONE ) {
                //Above of dead zone
                *yDir =  1;
            } else {
                *yDir = 0;
            }
        }
    }
}
