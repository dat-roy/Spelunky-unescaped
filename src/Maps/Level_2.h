#ifndef LEVEL_2__H_
#define LEVEL_2__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "Map.h"
#include "../Entities/Character.h"
#include "../Entities/Snake.h"
#include "../Entities/Bomb.h"

class Level_2
{
public:
    Level_2();
    ~Level_2();

    void display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48);
};


#endif // LEVEL_2__H_

