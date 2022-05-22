#ifndef SNAKE__H_
#define SNAKE__H_

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

class Snake
{
    SDL_Point pos;
    SDL_Point initPos;
    bool is_forward;
    int WIDTH = 95;
    int HEIGHT = 95;

    Texture snakeTexture;

    std::map<ActionTypes, TextureClips> textureClips =
    {
        { CRAWLING, TextureClips(11) },
        { ATTACKING, TextureClips(7) }
    };

public:
    ActionTypes action;

    //Constructors & Destructors
    Snake();
    Snake(SDL_Point pos, bool is_forward = true);
    ~Snake();

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

#endif //SNAKE__H_
