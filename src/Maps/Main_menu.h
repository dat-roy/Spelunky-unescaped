#ifndef MAIN_MENU__H_
#define MAIN_MENU__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "Button.h"

class Main_menu
{
    //Graphics textures
    Texture backgroundTexture;
public:
    Main_menu();
    ~Main_menu();

    void renderBackground(SDL_Renderer* gRenderer, int x = 0, int y = 0);

    void display(SDL_Renderer* gRenderer, GameState& gameState);
};

#endif // MAIN_MENU__H_

