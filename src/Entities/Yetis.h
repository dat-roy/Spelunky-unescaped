#ifndef YETIS__H_
#define YETIS__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <map>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "../Tools/TextureClips.h"

class Yetis
{
    SDL_Point pos;
    SDL_Point initPos;
    bool is_forward;
    int WIDTH = 166;
    int HEIGHT = 166;

    Texture yetisTexture;

    std::map<ActionTypes, TextureClips> textureClips =
    {
        { WALKING, TextureClips(8) },
        { ROARING, TextureClips(6) }
    };

public:
    ActionTypes action;

    //Constructors & Destructors
    Yetis();
    Yetis(SDL_Point pos, bool is_forward = true);
    ~Yetis();

    //Getters
    SDL_Point getPos();

    //Setters
    void setFirstPosition(SDL_Point pos, bool is_forward = true);

    //Load textures
    void loadTextures(SDL_Renderer* gRenderer, std::string path);

    void move(int dx, int dy);

    bool meet(SDL_Rect character_rect);

    //Render graphics
    void renderAction(SDL_Renderer* gRenderer);
};

#endif // YETIS__H_
