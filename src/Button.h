#ifndef BUTTON__H_
#define BUTTON__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "Texture.h"

class Button {
    SDL_Point buttonPos;
    Texture buttonTexture;
    SDL_Rect srect, drect;

    bool selected = false;
public:
    Button();

    void handleEvent(SDL_Event& event);
    void loadTextures(SDL_Renderer* gRenderer);
    void renderButton(SDL_Renderer* gRenderer);

};

#endif // BUTTON__H_
