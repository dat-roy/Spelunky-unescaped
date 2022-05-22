#ifndef LEVEL_1__H_
#define LEVEL_1__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "Map.h"
#include "../Entities/Character.h"
#include "../Entities/Snake.h"

class Level_1
{
public:
    Level_1();
    ~Level_1();

    void display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48);
};


#endif // LEVEL_1__H_
