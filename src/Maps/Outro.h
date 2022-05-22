#ifndef OUTRO__H_
#define OUTRO__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "Map.h"

class Outro
{
public:
    Outro();
    ~Outro();

    void display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48);
};


#endif // OUTRO__H_


