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
#include "../Texture.h"

class Main_menu
{
    //Graphics textures
    Texture backgroundTexture;
public:
    Main_menu();
    ~Main_menu();
    void loadTextures(SDL_Renderer* gRenderer);

    void renderBackground(SDL_Renderer* gRenderer, int x = 0, int y = 0);
};

#endif // MAIN_MENU__H_

