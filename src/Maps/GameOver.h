#ifndef GAMEOVER__H_
#define GAMEOVER__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "Map.h"

class GameOver
{
public:
    GameOver();
    ~GameOver();

    void display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48);
};


#endif // GAMEOVER__H_



