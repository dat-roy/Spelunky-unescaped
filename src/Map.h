#ifndef MAP__H_
#define MAP__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "Texture.h"

class Map
{
    //Graphics textures
    Texture gBgTexture;
    //Text textures
    Texture text_01;
    Texture text_02;
    Texture text_03;

public:
    Map();
    ~Map();
    void loadTextures(SDL_Renderer* &gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48);

    void renderBackground(SDL_Renderer* &gRenderer, int x = 0, int y = 0);
    void renderText_01(SDL_Renderer* &gRenderer, int x = 0, int y = 0);
    void renderText_02(SDL_Renderer* &gRenderer, int x = 0, int y = 0);
    void renderText_03(SDL_Renderer* &gRenderer, int x = 0, int y = 0);
};

#endif // MAP__H_
