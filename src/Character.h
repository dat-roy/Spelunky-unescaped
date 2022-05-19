#ifndef CHARACTER__H_
#define CHARACTER__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

#include "Global.h"
#include "Texture.h"
#include "TextureClips.h"

class Character
{
    SDL_Point pos;
    bool is_forward;

    std::map<CharacterAction, Texture> actionTexture =
    {
        { DYING, Texture() },
        { STANDING, Texture() },
        { WALKING, Texture() },
        { LYING, Texture() },
        { CRAWLING, Texture() },
        { THROWING, Texture() },
        { JUMPING, Texture() }
    };

    std::map<CharacterAction, TextureClips> textureClips =
    {
        { DYING, TextureClips(1) },
        { STANDING, TextureClips(1) },
        { WALKING, TextureClips(9) },
        { LYING, TextureClips(1) },
        { CRAWLING, TextureClips(7) },
        { THROWING, TextureClips(7) },
        { JUMPING, TextureClips(12) }
    };

public:
    CharacterAction action;

    //Constructors & Destructors
    Character();
    Character(SDL_Point pos, bool is_forward = true);
    ~Character();

    //Getter
    SDL_Point getPos();
    bool isForward();

    //Load textures
    void loadTextures(SDL_Renderer* gRenderer);

    void handleEvent(SDL_Event& event);
    void move(int dx, int dy);

    //Render graphics
    void renderAction(SDL_Renderer* gRenderer);
};

#endif // CHARACTER__H_
