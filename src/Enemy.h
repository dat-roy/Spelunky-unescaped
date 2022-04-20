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
#include "LTexture.h"

const int SNAKE_FRAME_TOTAL = 11;

class Enemy
{
    const int MAX_BLOOD = 1000;
    int posX, posY;
    int blood;
    bool is_forward;

    LTexture snakeTexture;
    SDL_Rect snakeClips[SNAKE_FRAME_TOTAL];
    int current_snake_frame;
public:

    //Constructors & Destructors
    Enemy();
    Enemy(int _posX, int _posY, bool _is_forward = true);
    ~Enemy();

    //Load textures
    void loadTextures(SDL_Renderer* &gRenderer);

    void move(int dx, int dy);

    //Render graphics
    void renderSnake(SDL_Renderer* &gRenderer);
};

#endif // ENEMY__H_
