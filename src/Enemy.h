#ifndef ENEMY__H_
#define ENEMY__H_

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
#include <map>

class Enemy
{
    SDL_Point pos;
    bool is_forward;

    Texture snakeTexture;

    std::map<CharacterAction, TextureClips> textureClips =
    {
        { CRAWLING, TextureClips(11) },
        { ATTACKING, TextureClips(7) }
    };

public:
    CharacterAction action;

    //Constructors & Destructors
    Enemy();
    Enemy(SDL_Point pos, bool is_forward = true);
    ~Enemy();

    //Getters
    SDL_Point getPos();

    //Setters
    void setFirstPosition(SDL_Point pos, bool is_forward = true);

    //Load textures
    void loadTextures(SDL_Renderer* gRenderer);

    void move(int dx, int dy);

    //Render graphics
    void renderAction(SDL_Renderer* gRenderer);
};

#endif // ENEMY__H_
