#ifndef TILE__H_
#define TILE__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "Texture.h"
#include "TextureClips.h"
#include "Character.h"

class Tile
{
    SDL_Rect box;
    int type;

public:
    Tile(int x, int y, int type);

    int getType();

    //Get the collision box
    SDL_Rect getBox();

    void render(SDL_Rect& camera);
};

#endif // TILE__H_
