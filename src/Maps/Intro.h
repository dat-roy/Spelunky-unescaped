#ifndef INTRO__H_
#define INTRO__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "Map.h"

class Intro
{
public:
    Intro();
    ~Intro();
    void display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48);

};
#endif // INTRO__H_

